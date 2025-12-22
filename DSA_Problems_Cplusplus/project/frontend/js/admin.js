// ==================== ADMIN.JS - Admin Panel ====================

let currentAdminSection = 'overview';
let NA_NAMES = {};
let PA_NAMES = {};

async function loadNANames() {
    try {
        const response = await fetch(`${CONFIG.API.BASE_URL}/constituencies/na-names`);
        const data = await response.json();
        if (data.success) {
            NA_NAMES = data.data;
            console.log('✅ Loaded', Object.keys(NA_NAMES).length, 'NA names');
            return true;
        }
    } catch (error) {
        console.error('❌ Error loading NA names:', error);
    }
    return false;
}

async function loadPANames(province) {
    try {
        const response = await fetch(`${CONFIG.API.BASE_URL}/constituencies/pa-names? province=${province}`);
        const data = await response.json();
        if (data.success) {
            PA_NAMES = data.data;
            console.log('✅ Loaded', Object.keys(PA_NAMES).length, `${province} PA names`);
            return true;
        }
    } catch (error) {
        console.error('❌ Error loading PA names:', error);
    }
    return false;
}

async function populateMNADropdown() {
    const select = document.getElementById('mna-constituency');
    if (!select) return;
    
    await loadNANames();
    
    select.innerHTML = '<option value="">Select NA Constituency</option>';
    
    const groups = {
        'KPK': { start: 1, end: 45, label: 'Khyber Pakhtunkhwa' },
        'Islamabad': { start: 46, end: 48, label: 'Islamabad Capital Territory' },
        'Punjab': { start: 49, end: 189, label: 'Punjab' },
        'Sindh': { start: 190, end: 250, label: 'Sindh' },
        'Balochistan': { start: 251, end: 266, label: 'Balochistan' }
    };
    
    for (const [key, group] of Object.entries(groups)) {
        const optgroup = document.createElement('optgroup');
        optgroup.label = group.label;
        
        for (let i = group.start; i <= group.end; i++) {
            const option = document.createElement('option');
            option.value = i;
            const areaName = NA_NAMES[i] || '';
            option.textContent = areaName ?  `NA-${i} | ${areaName}` : `NA-${i}`;
            optgroup.appendChild(option);
        }
        
        select.appendChild(optgroup);
    }
}

async function populateMPADropdown() {
    const provinceSelect = document.getElementById('mpa-province');
    const seatSelect = document.getElementById('mpa-seat');
    
    if (!provinceSelect || !seatSelect) return;
    
    provinceSelect.addEventListener('change', async (e) => {
        const province = e.target.value;
        if (! province) {
            seatSelect.innerHTML = '<option value="">Select Province First</option>';
            return;
        }
        
        await loadPANames(province);
        
        seatSelect.innerHTML = '<option value="">Select PA Constituency</option>';
        
        const maxSeats = {
            'Punjab': 297,
            'Sindh': 130,
            'KPK': 115,
            'Balochistan': 51
        };
        
        const max = maxSeats[province] || 0;
        const code = CONFIG.CONSTITUENCIES[province]?.code || 'P';
        
        for (let i = 1; i <= max; i++) {
            const option = document.createElement('option');
            option.value = i;
            const areaName = PA_NAMES[i] || '';
            option.textContent = areaName ?  `${code}-${i} | ${areaName}` : `${code}-${i}`;
            seatSelect.appendChild(option);
        }
    });
}
// ==================== INITIALIZE ADMIN PANEL ====================
function initializeAdminPanel() {
    console.log('Admin Panel Initialized');
    
    if (!AuthService.protectPage('admin')) {
        return;
    }
    
    const adminName = AuthService.getCurrentUser()?.username || 'Admin';
    document.getElementById('admin-name').textContent = adminName;
    
    loadOverviewStats();
    initializeAdminMenu();
    setupAdminForms();
    
    populateMNADropdown();
    populateMPADropdown();
}

// ==================== INITIALIZE ADMIN MENU ====================
function initializeAdminMenu() {
    const menuItems = document.querySelectorAll('.menu-item');
    
    menuItems.forEach(item => {
        item.addEventListener('click', (e) => {
            e.preventDefault();
            
            // Update active state
            menuItems.forEach(mi => mi.classList.remove('active'));
            item.classList.add('active');
            
            // Get section
            const href = item.getAttribute('href');
            const section = href.replace('#', '');
            
            showAdminSection(section);
        });
    });
}

// ==================== SHOW ADMIN SECTION ====================
window.showAdminSection = function(sectionName) {
    currentAdminSection = sectionName;
    
    // Hide all sections
    document.querySelectorAll('.dashboard-section').forEach(section => {
        section.classList.remove('active');
    });
    
    // Show selected section
    const targetSection = document.getElementById(`${sectionName}-section`);
    if (targetSection) {
        targetSection.classList.add('active');
        
        // Load section data
        switch(sectionName) {
            case 'overview':
                loadOverviewStats();
                break;
            case 'all-mna':
                loadAllMNA();
                break;
            case 'all-mpa':
                loadAllMPA();
                break;
            case 'tally':
                loadResults();
                break;
        }
    }
};

// ==================== LOAD OVERVIEW STATISTICS ====================
async function loadOverviewStats() {
    try {
        showLoader('Loading statistics...');
        
        const response = await API.call(CONFIG.API.ENDPOINTS.GET_ADMIN_STATS);
        
        hideLoader();
        
        if (response.success) {
            document.getElementById('total-voters').textContent = response.data.totalVoters || 0;
            document.getElementById('total-mna-candidates').textContent = response.data.totalMNACandidates || 0;
            document.getElementById('total-mpa-candidates').textContent = response.data.totalMPACandidates || 0;
            document.getElementById('total-votes').textContent = (response.data.mnaVotesCast || 0) + (response.data.mpaVotesCast || 0);
        }
    } catch (error) {
        hideLoader();
        console.error('Error loading overview stats:', error);
    }
}

// ==================== SETUP ADMIN FORMS ====================
function setupAdminForms() {
    // MNA Form
    const mnaForm = document.getElementById('add-mna-form');
    if (mnaForm) {
        mnaForm.addEventListener('submit', handleAddMNA);
    }
    
    // MPA Form
    const mpaForm = document.getElementById('add-mpa-form');
    if (mpaForm) {
        mpaForm.addEventListener('submit', handleAddMPA);
    }
}

// ==================== HANDLE ADD MNA ====================
async function handleAddMNA(e) {
    e.preventDefault();
    
    const formData = {
        name: document.getElementById('mna-name').value.trim(),
        cnic: document.getElementById('mna-cnic').value.trim(),
        symbol: document.getElementById('mna-symbol').value.trim(),
        naSeat: parseInt(document.getElementById('mna-constituency').value)
    };
    
    console.log('📤 Sending MNA candidate:', formData);
    
    // Validate
    if (!formData.name || !formData.cnic || !formData.symbol || !formData.naSeat) {
        showAlert('Please fill all fields', 'error');
        return;
    }
    
    const cnicValidation = validateCNIC(formData.cnic);
    if (! cnicValidation.valid) {
        showAlert(cnicValidation.message, 'error');
        return;
    }
    
    const naValidation = validateNASeat(formData.naSeat);
    if (!naValidation.valid) {
        showAlert(naValidation.message, 'error');
        return;
    }
    
    showLoader('Adding MNA candidate...');
    
    try {
        const response = await API.call(CONFIG.API.ENDPOINTS.ADD_MNA_CANDIDATE, 'POST', formData);
        
        hideLoader();
        
        console.log('MNA Response:', response);
        
        if (response.success) {
            showAlert('MNA Candidate added successfully!', 'success');
            e.target.reset();
            loadOverviewStats();
        } else {
            showAlert(response.message || 'Failed to add candidate', 'error');
        }
    } catch (error) {
        hideLoader();
        console.error('❌ Add MNA error:', error);
        showAlert(error.message || 'Failed to add candidate.Check console for details.', 'error');
    }
}

// ==================== HANDLE ADD MPA ====================
async function handleAddMPA(e) {
    e.preventDefault();
    
    const province = document.getElementById('mpa-province').value;
    
    const formData = {
        name: document.getElementById('mpa-name').value.trim(),
        cnic: document.getElementById('mpa-cnic').value.trim(),
        symbol: document.getElementById('mpa-symbol').value.trim(),
        province: province,
        paSeat: parseInt(document.getElementById('mpa-seat').value)
    };
    
    console.log('📤 Sending MPA candidate:', formData);
    
    // Validate
    if (!formData.name || ! formData.cnic || !formData.symbol || !formData.province || !formData.paSeat) {
        showAlert('Please fill all fields', 'error');
        return;
    }
    
    const cnicValidation = validateCNIC(formData.cnic);
    if (!cnicValidation.valid) {
        showAlert(cnicValidation.message, 'error');
        return;
    }
    
    if (! validatePASeat(formData.province, formData.paSeat)) {
        showAlert('Invalid PA seat for selected province', 'error');
        return;
    }
    
    showLoader('Adding MPA candidate...');
    
    try {
        const response = await API.call(CONFIG.API.ENDPOINTS.ADD_MPA_CANDIDATE, 'POST', formData);
        
        hideLoader();
        
        console.log('📥 MPA Response:', response);
        
        if (response.success) {
            showAlert('MPA Candidate added successfully!', 'success');
            e.target.reset();
            loadOverviewStats();
        } else {
            showAlert(response.message || 'Failed to add candidate', 'error');
        }
    } catch (error) {
        hideLoader();
        console.error('❌ Add MPA error:', error);
        showAlert(error.message || 'Failed to add candidate.Check console for details.', 'error');
    }
}

// ==================== LOAD ALL MNA ====================
window.loadAllMNA = async function() {
    const container = document.getElementById('mna-candidates-table');
    if (!container) return;
    
    try {
        showLoader('Loading MNA candidates...');
        
        const response = await API.call(CONFIG.API.ENDPOINTS.GET_ALL_MNA);
        
        hideLoader();
        
        console.log('📥 MNA Candidates Response:', response);
        
        if (response.success && response.data.candidates && response.data.candidates.length > 0) {
            displayCandidatesTable(response.data.candidates, 'mna', container);
        } else {
            container.innerHTML = `
                <div class="table-empty">
                    <i class="fas fa-inbox"></i>
                    <h3>No MNA Candidates</h3>
                    <p>No MNA candidates registered yet</p>
                </div>
            `;
        }
    } catch (error) {
        hideLoader();
        console.error('❌ Load MNA error:', error);
        container.innerHTML = `
            <div class="error-message show">
                <i class="fas fa-exclamation-circle"></i>
                <p>Error loading candidates: ${error.message}</p>
            </div>
        `;
    }
};

// ==================== LOAD ALL MPA ====================
window.loadAllMPA = async function() {
    const container = document.getElementById('mpa-candidates-table');
    if (!container) return;
    
    try {
        showLoader('Loading MPA candidates...');
        
        const response = await API.call(CONFIG.API.ENDPOINTS.GET_ALL_MPA);
        
        hideLoader();
        
        console.log('📥 MPA Candidates Response:', response);
        
        if (response.success && response.data.candidates && response.data.candidates.length > 0) {
            displayCandidatesTable(response.data.candidates, 'mpa', container);
        } else {
            container.innerHTML = `
                <div class="table-empty">
                    <i class="fas fa-inbox"></i>
                    <h3>No MPA Candidates</h3>
                    <p>No MPA candidates registered yet</p>
                </div>
            `;
        }
    } catch (error) {
        hideLoader();
        console.error('❌ Load MPA error:', error);
        container.innerHTML = `
            <div class="error-message show">
                <i class="fas fa-exclamation-circle"></i>
                <p>Error loading candidates: ${error.message}</p>
            </div>
        `;
    }
};
window.viewLedger = async function() {
    console.log('🔗 Loading blockchain ledger...');
    
    try {
        showLoader('Loading blockchain ledger...');
        
        const response = await API.call(CONFIG.API.ENDPOINTS.VIEW_LEDGER);
        
        hideLoader();
        
        console.log('📦 Ledger Response:', response);
        
        if (response.success && response.data. ledger) {
            displayLedger(response.data.ledger);
        } else {
            showAlert('No ledger data available', 'info');
        }
    } catch (error) {
        hideLoader();
        console.error('❌ Error loading ledger:', error);
        showAlert('Error loading ledger: ' + error.message, 'error');
    }
};

// ==================== VERIFY LEDGER ====================
window.verifyLedger = async function() {
    console.log('✅ Verifying blockchain ledger...');
    
    try {
        showLoader('Verifying blockchain integrity...');
        
        const response = await API.call(CONFIG. API.ENDPOINTS.VERIFY_LEDGER);
        
        hideLoader();
        
        console.log('📦 Verification Response:', response);
        
        if (response.success) {
            if (response.data.isValid) {
                showAlert('✅ ' + response.data.message, 'success');
            } else {
                showAlert('⚠️ ' + response.data. message, 'error');
            }
        } else {
            showAlert('Error verifying ledger', 'error');
        }
    } catch (error) {
        hideLoader();
        console.error('❌ Error verifying ledger:', error);
        showAlert('Error verifying ledger: ' + error. message, 'error');
    }
};

// ==================== DISPLAY LEDGER ====================
function displayLedger(ledgerBlocks) {
    if (! ledgerBlocks || ledgerBlocks.length === 0) {
        showAlert('Ledger is empty', 'info');
        return;
    }
    
    const html = `
        <div class="modal-overlay" id="ledger-modal" onclick="closeLedgerModal(event)">
            <div class="modal-content ledger-modal" onclick="event.stopPropagation()">
                <div class="modal-header">
                    <h2>🔗 Blockchain Ledger</h2>
                    <button class="modal-close" onclick="closeLedgerModal()">&times;</button>
                </div>
                <div class="modal-body">
                    <div class="ledger-stats">
                        <div class="stat-item">
                            <i class="fas fa-cubes"></i>
                            <div>
                                <span class="stat-label">Total Blocks</span>
                                <span class="stat-value">${ledgerBlocks.length}</span>
                            </div>
                        </div>
                        <div class="stat-item">
                            <i class="fas fa-shield-alt"></i>
                            <div>
                                <span class="stat-label">Status</span>
                                <span class="stat-value" style="color: #28a745;">Secure</span>
                            </div>
                        </div>
                    </div>
                    
                    <div class="ledger-blocks">
                        ${ledgerBlocks.map(block => `
                            <div class="ledger-block">
                                <div class="block-header">
                                    <h3>Block #${block.index}</h3>
                                    <span class="block-type ${block.voteType. toLowerCase()}">${block.voteType}</span>
                                </div>
                                <div class="block-details">
                                    <div class="block-detail">
                                        <i class="fas fa-clock"></i>
                                        <span><strong>Timestamp:</strong> ${block.timestamp}</span>
                                    </div>
                                    <div class="block-detail">
                                        <i class="fas fa-user"></i>
                                        <span><strong>Voter CNIC:</strong> ${maskCNIC(block.voterCnic)}</span>
                                    </div>
                                    <div class="block-detail">
                                        <i class="fas fa-user-tie"></i>
                                        <span><strong>Candidate CNIC:</strong> ${maskCNIC(block.candidateCnic)}</span>
                                    </div>
                                    <div class="block-detail hash-detail">
                                        <i class="fas fa-link"></i>
                                        <span><strong>Previous Hash:</strong> <code>${block.prevHash}</code></span>
                                    </div>
                                    <div class="block-detail hash-detail">
                                        <i class="fas fa-fingerprint"></i>
                                        <span><strong>Current Hash:</strong> <code>${block.currentHash}</code></span>
                                    </div>
                                </div>
                            </div>
                        `).join('')}
                    </div>
                </div>
            </div>
        </div>
    `;
    
    document. body.insertAdjacentHTML('beforeend', html);
    
    setTimeout(() => {
        document.getElementById('ledger-modal').classList.add('show');
    }, 10);
}

// ==================== CLOSE LEDGER MODAL ====================
window.closeLedgerModal = function(event) {
    if (! event || event.target. classList.contains('modal-overlay') || event.target.classList.contains('modal-close')) {
        const modal = document.getElementById('ledger-modal');
        if (modal) {
            modal.classList. remove('show');
            setTimeout(() => modal.remove(), 300);
        }
    }
};

// ==================== DISPLAY CANDIDATES TABLE ====================
function displayCandidatesTable(candidates, type, container) {
    const html = `
        <div class="data-table">
            <table>
                <thead>
                    <tr>
                        <th>#</th>
                        <th>Name</th>
                        <th>Symbol</th>
                        <th>CNIC</th>
                        <th>Constituency</th>
                        <th>Area</th>
                        <th>Votes</th>
                    </tr>
                </thead>
                <tbody>
                    ${candidates.map((candidate, index) => {
                        const naSeat = candidate.naSeat || candidate.constituency_na || 'N/A';
                        const paSeat = candidate.paSeat || candidate.provisional_pp || 'N/A';
                        const province = candidate.province || '';
                        const areaName = candidate.area || candidate.na_area || candidate.p_area || 'N/A';
                        
                        return `
                            <tr>
                                <td>${index + 1}</td>
                                <td>${candidate.name}</td>
                                <td>${candidate.symbol}</td>
                                <td>${maskCNIC(candidate.cnic)}</td>
                                <td>${type === 'mna' ? `NA-${naSeat}` : `${province}-${paSeat}`}</td>
                                <td>${areaName}</td>
                                <td><strong>${candidate.votes || 0}</strong></td>
                            </tr>
                        `;
                    }).join('')}
                </tbody>
            </table>
        </div>
    `;
    
    container.innerHTML = html;
}
// ==================== LOAD RESULTS ====================
window.loadResults = async function() {
    const container = document.getElementById('results-container');
    if (!container) return;
    
    try {
        showLoader('Calculating results...');
        
        const response = await API.call(CONFIG.API.ENDPOINTS.GET_RESULTS);
        
        hideLoader();
        
        if (response.success) {
            displayAdminResults(response.data, container);
        } else {
            container.innerHTML = `
                <div class="error-message show">
                    <p>Error loading results</p>
                </div>
            `;
        }
    } catch (error) {
        hideLoader();
        container.innerHTML = `
            <div class="error-message show">
                <p>Error loading results: ${error.message}</p>
            </div>
        `;
    }
};

// ==================== DISPLAY ADMIN RESULTS ====================
function displayAdminResults(data, container) {
    const mnaResults = data.mna || [];
    const mpaResults = data.mpa || [];
    
    // Sort by votes
    mnaResults.sort((a, b) => (b.votes || 0) - (a.votes || 0));
    mpaResults.sort((a, b) => (b.votes || 0) - (a.votes || 0));
    
    const html = `
        <div class="results-card">
            <div class="card-header">
                <h2><i class="fas fa-landmark"></i> MNA Results</h2>
            </div>
            ${mnaResults.length > 0 ? `
                <div class="data-table">
                    <table>
                        <thead>
                            <tr>
                                <th>Rank</th>
                                <th>Name</th>
                                <th>Symbol</th>
                                <th>Constituency</th>
                                <th>Votes</th>
                            </tr>
                        </thead>
                        <tbody>
                            ${mnaResults.map((candidate, index) => `
                                <tr ${index === 0 ? 'class="winner"' : ''}>
                                    <td>${index + 1}${index === 0 ? ' 🏆' : ''}</td>
                                    <td>${candidate.name}</td>
                                    <td>${candidate.symbol}</td>
                                    <td>NA-${candidate.naSeat}</td>
                                    <td><strong>${candidate.votes || 0}</strong></td>
                                </tr>
                            `).join('')}
                        </tbody>
                    </table>
                </div>
            ` : '<p class="table-empty">No votes recorded yet</p>'}
        </div>
        
        <div class="results-card">
            <div class="card-header">
                <h2><i class="fas fa-building"></i> MPA Results</h2>
            </div>
            ${mpaResults.length > 0 ? `
                <div class="data-table">
                    <table>
                        <thead>
                            <tr>
                                <th>Rank</th>
                                <th>Name</th>
                                <th>Symbol</th>
                                <th>Province</th>
                                <th>Constituency</th>
                                <th>Votes</th>
                            </tr>
                        </thead>
                        <tbody>
                            ${mpaResults.map((candidate, index) => `
                                <tr ${index === 0 ? 'class="winner"' : ''}>
                                    <td>${index + 1}${index === 0 ? ' 🏆' : ''}</td>
                                    <td>${candidate.name}</td>
                                    <td>${candidate.symbol}</td>
                                    <td>${candidate.province}</td>
                                    <td>${candidate.province}-${candidate.paSeat}</td>
                                    <td><strong>${candidate.votes || 0}</strong></td>
                                </tr>
                            `).join('')}
                        </tbody>
                    </table>
                </div>
            ` : '<p class="table-empty">No votes recorded yet</p>'}
        </div>
    `;
    
    container.innerHTML = html;
}

// ==================== DOM READY ====================
document.addEventListener('DOMContentLoaded', () => {
    initializeAdminPanel();
});