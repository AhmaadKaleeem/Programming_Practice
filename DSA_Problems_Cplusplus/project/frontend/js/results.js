let currentResultsTab = 'all-votes';
let resultsData = null;

console.log('🎬 Results.js loaded');

function initializeResultsPage() {
    console.log('📊 Results Page Initialized');
    
    try {
        if (typeof API === 'undefined') {
            console.error('❌ API not loaded');
            showNoResults();
            return;
        }
        
        if (typeof CONFIG === 'undefined') {
            console.error('❌ CONFIG not loaded');
            showNoResults();
            return;
        }
        
        console.log('✅ Dependencies loaded');
        
        setupTabSwitching();
        loadResultsData();
        setInterval(loadResultsData, 10000);
        
    } catch (error) {
        console.error('❌ Error initializing results:', error);
        showNoResults();
    }
}

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

window.refreshResults = function() {
    console.log('🔄 Refreshing results...');
    showLoader('Refreshing results...');
    loadResultsData();
};

window.switchResultsTab = function(tab) {
    console.log('📑 Switching to tab:', tab);
    currentResultsTab = tab;
    
    const tabBtns = document.querySelectorAll('.results-tabs .tab-btn');
    tabBtns.forEach(btn => btn.classList.remove('active'));
    
    if (tab === 'all-votes') {
        tabBtns[0]?.classList.add('active');
    } else {
        tabBtns[1]?.classList.add('active');
    }
    
    document.querySelectorAll('.results-section').forEach(section => {
        section.classList.remove('active');
    });
    
    const targetSection = document.getElementById(`${tab}-section`);
    if (targetSection) {
        targetSection.classList.add('active');
    }
    
    if (tab === 'all-votes') {
        displayAllVotes();
    } else if (tab === 'winners') {
        displayWinners();
    }
};

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
    
    const mnaCandidates = resultsData.mna || [];
    const mpaCandidates = resultsData.mpa || [];
    
    console.log('📋 Candidates:', {
        mna: mnaCandidates.length,
        mpa: mpaCandidates.length
    });
    
    if (mnaCandidates.length > 0) {
        const mnaSorted = [...mnaCandidates].sort((a, b) => {
            const aConst = a.constituency_na || a.naSeat || 0;
            const bConst = b.constituency_na || b.naSeat || 0;
            if (aConst === bConst) {
                return (b.votes || 0) - (a.votes || 0);
            }
            return aConst - bConst;
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
    
    if (mpaCandidates.length > 0) {
        const mpaSorted = [...mpaCandidates].sort((a, b) => {
            const aProv = a.province || '';
            const bProv = b.province || '';
            const aSeat = a.provisional_pp || a.paSeat || 0;
            const bSeat = b.provisional_pp || b.paSeat || 0;
            
            if (aProv === bProv && aSeat === bSeat) {
                return (b.votes || 0) - (a.votes || 0);
            }
            if (aProv === bProv) {
                return aSeat - bSeat;
            }
            return aProv.localeCompare(bProv);
        });
        
        mpaContainer.innerHTML = displayResultsGrid(mpaSorted, 'mpa');
    } else {
        mpaContainer.innerHTML = `
            <div class="no-results">
                <i class="fas fa-inbox"></i>
                <h3>No MPA Candidates</h3>
                <p>No MPA candidates have been registered yet</p>
                <p style="margin-top: 1rem;"><a href="login.html?admin=true" class="btn btn-primary">Add Candidates (Admin)</a></p>
            </div>
        `;
    }
    
    console.log('✅ All votes displayed');
}

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
                let areaName = candidate.area || candidate.na_area || candidate.p_area || '';
                
                if (type === 'mna') {
                    const naSeat = candidate.constituency_na || candidate.naSeat || 'N/A';
                    constituencyDisplay = `NA-${naSeat}`;
                } else {
                    const paSeat = candidate.provisional_pp || candidate.paSeat || 'N/A';
                    const province = candidate.province || '';
                    const provinceCode = province ?  province.charAt(0) : 'P';
                    constituencyDisplay = `${provinceCode}${province.substring(1, 2) || ''}-${paSeat}`;
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
                                ${areaName ? `
                                <span class="result-detail">
                                    <i class="fas fa-location-dot"></i>
                                    ${areaName}
                                </span>
                                ` : ''}
                                ${type === 'mpa' && candidate.province ? `
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

function displayWinners() {
    console.log('🏆 Displaying winners...');
    
    const mnaContainer = document.getElementById('mna-winners-container');
    const mpaContainer = document.getElementById('mpa-winners-container');
    
    if (!mnaContainer || ! mpaContainer) {
        console.error('❌ Winners containers not found');
        return;
    }
    
    if (!resultsData) {
        console.warn('⚠️ No results data for winners');
        showNoResults();
        return;
    }
    
    const mnaWinners = calculateWinners(resultsData.mna || [], 'mna');
    const mpaWinners = calculateWinnersByProvinceAndSeat(resultsData.mpa || []);
    
    console.log('🏆 Winners:', {
        mna: mnaWinners.length,
        mpa: mpaWinners.length
    });
    
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

function calculateWinners(candidates, type) {
    if (!candidates || candidates.length === 0) return [];
    
    const grouped = {};
    
    candidates.forEach(candidate => {
        const key = type === 'mna' 
            ? (candidate.constituency_na || candidate.naSeat || 0)
            : `${candidate.province || ''}-${candidate.provisional_pp || candidate.paSeat || 0}`;
        
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

function calculateWinnersByProvinceAndSeat(candidates) {
    if (!candidates || candidates.length === 0) return [];
    
    const grouped = {};
    
    candidates.forEach(candidate => {
        const paSeat = candidate.provisional_pp || candidate.paSeat || 0;
        const key = `${candidate.province || ''}-${paSeat}`;
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
                let areaName = candidate.area || candidate.na_area || candidate.p_area || '';
                
                if (type === 'mna') {
                    const naSeat = candidate.constituency_na || candidate.naSeat || 'N/A';
                    constituencyDisplay = `NA-${naSeat}`;
                } else {
                    const paSeat = candidate.provisional_pp || candidate.paSeat || 'N/A';
                    const province = candidate.province || '';
                    const provinceCode = province ? province.charAt(0) : 'P';
                    constituencyDisplay = `${provinceCode}${province.substring(1, 2) || ''}-${paSeat}`;
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
                                ${areaName ? `
                                <span class="result-detail">
                                    <i class="fas fa-location-dot"></i>
                                    ${areaName}
                                </span>
                                ` : ''}
                                ${type === 'mpa' && candidate.province ? `
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

if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initializeResultsPage);
} else {
    initializeResultsPage();
}

console.log('✅ Results.js fully loaded');