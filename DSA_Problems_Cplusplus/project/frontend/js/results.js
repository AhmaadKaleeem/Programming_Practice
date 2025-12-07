// ==================== RESULTS.JS - Election Results Display ====================

let currentResultsTab = 'all-votes';
let resultsData = null;

console.log('🎬 Results.js loaded');

// ==================== HELPER FUNCTIONS ====================
// Get NA seat number with fallback for backward compatibility
function getNASeat(candidate) {
    return candidate.naSeat || candidate.constituency || 0;
}

// Get PA seat number with fallback for backward compatibility
function getPASeat(candidate) {
    return candidate.paSeat || candidate.provisionalPP || candidate.provisional_pp || 0;
}

// ==================== INITIALIZE RESULTS PAGE ====================
function initializeResultsPage() {
    console.log('📊 Results Page Initialized');
    
    try {
        // Check if API is available
        if (typeof API === 'undefined') {
            console.error('❌ API not loaded');
            showNoResults();
            return;
        }
        
        // Check if CONFIG is available
        if (typeof CONFIG === 'undefined') {
            console.error('❌ CONFIG not loaded');
            showNoResults();
            return;
        }
        
        console.log('✅ Dependencies loaded');
        
        // Setup tab switching
        setupTabSwitching();
        
        // Load results immediately
        loadResultsData();
        
        // Auto-refresh every 10 seconds
        setInterval(loadResultsData, 10000);
        
    } catch (error) {
        console.error('❌ Error initializing results:', error);
        showNoResults();
    }
}

// ==================== SETUP TAB SWITCHING ====================
function setupTabSwitching() {
    const tabBtns = document.querySelectorAll('.results-tabs .tab-btn');
    
    if (! tabBtns || tabBtns.length === 0) {
        console.warn('⚠️ Tab buttons not found');
        return;
    }
    
    tabBtns.forEach((btn, index) => {
        btn.addEventListener('click', () => {
            const tab = index === 0 ? 'all-votes' : 'winners';
            switchResultsTab(tab);
        });
    });
    
    console.log('✅ Tab switching setup complete');
}

// ==================== REFRESH RESULTS ====================
window.refreshResults = function() {
    console.log('🔄 Refreshing results...');
    showLoader('Refreshing results...');
    loadResultsData();
};

// ==================== SWITCH RESULTS TAB ====================
window.switchResultsTab = function(tab) {
    console.log('📑 Switching to tab:', tab);
    currentResultsTab = tab;
    
    // Update tab buttons
    const tabBtns = document.querySelectorAll('.results-tabs .tab-btn');
    tabBtns.forEach(btn => btn.classList.remove('active'));
    
    if (tab === 'all-votes') {
        tabBtns[0]?.classList.add('active');
    } else {
        tabBtns[1]?.classList.add('active');
    }
    
    // Show/hide sections
    document.querySelectorAll('.results-section').forEach(section => {
        section.classList.remove('active');
    });
    
    const targetSection = document.getElementById(`${tab}-section`);
    if (targetSection) {
        targetSection.classList.add('active');
    }
    
    // Load appropriate data
    if (tab === 'all-votes') {
        displayAllVotes();
    } else if (tab === 'winners') {
        displayWinners();
    }
};

// ==================== LOAD RESULTS DATA ====================
async function loadResultsData() {
    console.log('📥 Loading results data...');
    
    try {
        const response = await API.call(CONFIG.API.ENDPOINTS.GET_RESULTS);
        
        console.log('📦 Results response:', response);
        
        hideLoader();
        
        if (response.success && response.data) {
            resultsData = response.data;
            
            console.log('✅ Results loaded:', {
                mna: resultsData.mna?.length || 0,
                mpa: resultsData.mpa?.length || 0
            });
            
            // Display based on current tab
            if (currentResultsTab === 'all-votes') {
                displayAllVotes();
            } else {
                displayWinners();
            }
        } else {
            console.warn('⚠️ No results data available');
            showNoResults();
        }
    } catch (error) {
        console.error('❌ Error loading results:', error);
        hideLoader();
        showNoResults();
    }
}

// ==================== DISPLAY ALL VOTES ====================
function displayAllVotes() {
    console.log('📊 Displaying all votes...');
    
    const mnaContainer = document.getElementById('mna-results-container');
    const mpaContainer = document.getElementById('mpa-results-container');
    
    if (!mnaContainer || !mpaContainer) {
        console.error('❌ Results containers not found');
        return;
    }
    
    if (! resultsData) {
        console.warn('⚠️ No results data to display');
        showNoResults();
        return;
    }
    
    // Get candidates
    const mnaCandidates = resultsData.mna || [];
    const mpaCandidates = resultsData.mpa || [];
    
    console.log('📋 Candidates:', {
        mna: mnaCandidates.length,
        mpa: mpaCandidates.length
    });
    
    // Display MNA results
    if (mnaCandidates.length > 0) {
        // Sort by constituency (backend uses naSeat)
        const mnaSorted = [...mnaCandidates].sort((a, b) => {
            const aConstituency = getNASeat(a);
            const bConstituency = getNASeat(b);
            if (aConstituency === bConstituency) {
                return (b.votes || 0) - (a.votes || 0);
            }
            return aConstituency - bConstituency;
        });
        
        mnaContainer.innerHTML = displayResultsGrid(mnaSorted, 'mna');
    } else {
        mnaContainer.innerHTML = `
            <div class="no-results">
                <i class="fas fa-inbox"></i>
                <h3>No MNA Candidates</h3>
                <p>No MNA candidates have been registered yet</p>
                <p style="margin-top: 1rem;"><a href="login.html? admin=true" class="btn btn-primary">Add Candidates (Admin)</a></p>
            </div>
        `;
    }
    
    // Display MPA results
    if (mpaCandidates.length > 0) {
        // Sort by province and seat (backend uses paSeat)
        const mpaSorted = [...mpaCandidates].sort((a, b) => {
            const aPaSeat = getPASeat(a);
            const bPaSeat = getPASeat(b);
            if (a.province === b.province && aPaSeat === bPaSeat) {
                return (b.votes || 0) - (a.votes || 0);
            }
            if (a.province === b.province) {
                return aPaSeat - bPaSeat;
            }
            return a.province.localeCompare(b.province);
        });
        
        mpaContainer.innerHTML = displayResultsGrid(mpaSorted, 'mpa');
    } else {
        mpaContainer.innerHTML = `
            <div class="no-results">
                <i class="fas fa-inbox"></i>
                <h3>No MPA Candidates</h3>
                <p>No MPA candidates have been registered yet</p>
                <p style="margin-top: 1rem;"><a href="login.html? admin=true" class="btn btn-primary">Add Candidates (Admin)</a></p>
            </div>
        `;
    }
    
    console.log('✅ All votes displayed');
}

// ==================== DISPLAY RESULTS GRID ====================
function displayResultsGrid(candidates, type) {
    if (!candidates || candidates.length === 0) {
        return `
            <div class="no-results">
                <i class="fas fa-inbox"></i>
                <h3>No Results Available</h3>
                <p>No candidates registered yet</p>
            </div>
        `;
    }
    
    return `
        <div class="results-grid">
            ${candidates.map(candidate => {
                let constituencyDisplay = '';
                let areaName = candidate.area || '';
                
                if (type === 'mna') {
                    const naSeat = getNASeat(candidate);
                    constituencyDisplay = `NA-${naSeat}`;
                    if (areaName) {
                        constituencyDisplay += ` | ${areaName}`;
                    }
                } else {
                    const paSeat = getPASeat(candidate);
                    const paCode = candidate.provinceName || candidate.province || 'PA';
                    constituencyDisplay = `${paCode}-${paSeat}`;
                    if (areaName) {
                        constituencyDisplay += ` | ${areaName}`;
                    }
                }
                
                return `
                    <div class="result-item">
                        <div class="result-candidate">
                            <div class="result-candidate-name">${candidate.name}</div>
                            <div class="result-candidate-details">
                                <span class="result-detail">
                                    <i class="fas fa-flag"></i>
                                    ${candidate.symbol}
                                </span>
                                <span class="result-detail">
                                    <i class="fas fa-map-marker-alt"></i>
                                    ${constituencyDisplay}
                                </span>
                                ${type === 'mpa' ? `
                                <span class="result-detail">
                                    <i class="fas fa-map"></i>
                                    ${candidate.province}
                                </span>
                                ` : ''}
                            </div>
                        </div>
                        <div class="result-votes">
                            <div class="result-votes-label">Votes</div>
                            <div class="result-votes-number">${candidate.votes || 0}</div>
                        </div>
                    </div>
                `;
            }).join('')}
        </div>
    `;
}

// ==================== DISPLAY WINNERS ====================
function displayWinners() {
    console.log('🏆 Displaying winners...');
    
    const mnaContainer = document.getElementById('mna-winners-container');
    const mpaContainer = document.getElementById('mpa-winners-container');
    
    if (!mnaContainer || ! mpaContainer) {
        console.error('❌ Winners containers not found');
        return;
    }
    
    if (! resultsData) {
        console.warn('⚠️ No results data for winners');
        showNoResults();
        return;
    }
    
    // Calculate winners
    const mnaWinners = calculateWinners(resultsData.mna || [], 'constituency');
    const mpaWinners = calculateWinnersByProvinceAndSeat(resultsData.mpa || []);
    
    console.log('🏆 Winners:', {
        mna: mnaWinners.length,
        mpa: mpaWinners.length
    });
    
    // Display MNA winners
    if (mnaWinners.length > 0) {
        mnaContainer.innerHTML = displayWinnersGrid(mnaWinners, 'mna');
    } else {
        mnaContainer.innerHTML = `
            <div class="no-results">
                <i class="fas fa-trophy"></i>
                <h3>No Winners Yet</h3>
                <p>No votes have been cast yet to determine winners</p>
            </div>
        `;
    }
    
    // Display MPA winners
    if (mpaWinners.length > 0) {
        mpaContainer.innerHTML = displayWinnersGrid(mpaWinners, 'mpa');
    } else {
        mpaContainer.innerHTML = `
            <div class="no-results">
                <i class="fas fa-trophy"></i>
                <h3>No Winners Yet</h3>
                <p>No votes have been cast yet to determine winners</p>
            </div>
        `;
    }
    
    console.log('✅ Winners displayed');
}

// ==================== CALCULATE WINNERS ====================
function calculateWinners(candidates, groupBy) {
    if (!candidates || candidates.length === 0) return [];
    
    const grouped = {};
    
    candidates.forEach(candidate => {
        const key = candidate[groupBy];
        if (!grouped[key]) {
            grouped[key] = [];
        }
        grouped[key].push(candidate);
    });
    
    const winners = [];
    Object.values(grouped).forEach(group => {
        const sorted = group.sort((a, b) => (b.votes || 0) - (a.votes || 0));
        if (sorted[0] && sorted[0].votes > 0) {
            winners.push(sorted[0]);
        }
    });
    
    return winners.sort((a, b) => (b.votes || 0) - (a.votes || 0));
}

// ==================== CALCULATE MPA WINNERS ====================
function calculateWinnersByProvinceAndSeat(candidates) {
    if (!candidates || candidates.length === 0) return [];
    
    const grouped = {};
    
    candidates.forEach(candidate => {
        const paSeat = getPASeat(candidate);
        const key = `${candidate.province}-${paSeat}`;
        if (!grouped[key]) {
            grouped[key] = [];
        }
        grouped[key].push(candidate);
    });
    
    const winners = [];
    Object.values(grouped).forEach(group => {
        const sorted = group.sort((a, b) => (b.votes || 0) - (a.votes || 0));
        if (sorted[0] && sorted[0].votes > 0) {
            winners.push(sorted[0]);
        }
    });
    
    return winners.sort((a, b) => (b.votes || 0) - (a.votes || 0));
}

// ==================== DISPLAY WINNERS GRID ====================
function displayWinnersGrid(winners, type) {
    if (!winners || winners.length === 0) {
        return `
            <div class="no-results">
                <i class="fas fa-trophy"></i>
                <h3>No Winners Yet</h3>
                <p>Cast votes to determine winners</p>
            </div>
        `;
    }
    
    return `
        <div class="results-grid">
            ${winners.map((candidate, index) => {
                let constituencyDisplay = '';
                let areaName = candidate.area || '';
                
                if (type === 'mna') {
                    const naSeat = getNASeat(candidate);
                    constituencyDisplay = `NA-${naSeat}`;
                    if (areaName) {
                        constituencyDisplay += ` | ${areaName}`;
                    }
                } else {
                    const paSeat = getPASeat(candidate);
                    const paCode = candidate.provinceName || candidate.province || 'PA';
                    constituencyDisplay = `${paCode}-${paSeat}`;
                    if (areaName) {
                        constituencyDisplay += ` | ${areaName}`;
                    }
                }
                
                return `
                    <div class="result-item winner-item">
                        <div class="result-candidate">
                            <div class="result-candidate-name">
                                ${index < 3 ? (index === 0 ? '🥇 ' : index === 1 ? '🥈 ' : '🥉 ') : ''}
                                ${candidate.name}
                                <span class="winner-badge">
                                    <i class="fas fa-trophy"></i>
                                    Winner
                                </span>
                            </div>
                            <div class="result-candidate-details">
                                <span class="result-detail">
                                    <i class="fas fa-flag"></i>
                                    ${candidate.symbol}
                                </span>
                                <span class="result-detail">
                                    <i class="fas fa-map-marker-alt"></i>
                                    ${constituencyDisplay}
                                </span>
                                ${type === 'mpa' ? `
                                <span class="result-detail">
                                    <i class="fas fa-map"></i>
                                    ${candidate.province}
                                </span>
                                ` : ''}
                            </div>
                        </div>
                        <div class="result-votes">
                            <div class="result-votes-label">Votes</div>
                            <div class="result-votes-number">${candidate.votes || 0}</div>
                        </div>
                    </div>
                `;
            }).join('')}
        </div>
    `;
}

// ==================== SHOW NO RESULTS ====================
function showNoResults() {
    console.log('📭 Showing no results message');
    
    const containers = [
        'mna-results-container',
        'mpa-results-container',
        'mna-winners-container',
        'mpa-winners-container'
    ];
    
    const noResultsHtml = `
        <div class="no-results">
            <i class="fas fa-chart-bar"></i>
            <h3>No Results Available</h3>
            <p>Results will be displayed once candidates are registered</p>
            <p style="margin-top: 1rem;">
                <a href="login.html?admin=true" class="btn btn-primary">
                    <i class="fas fa-user-shield"></i> Admin Login
                </a>
            </p>
        </div>
    `;
    
    containers.forEach(id => {
        const container = document.getElementById(id);
        if (container) {
            container.innerHTML = noResultsHtml;
        }
    });
}

// ==================== DOM READY ====================
if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initializeResultsPage);
} else {
    initializeResultsPage();
}

console.log('✅ Results.js fully loaded');