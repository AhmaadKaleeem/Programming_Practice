// ==================== ADMIN.JS - Admin Panel ====================

let currentAdminSection = 'overview';

// ==================== INITIALIZE ADMIN PANEL ====================
function initializeAdminPanel() {
    console.log('Admin Panel Initialized');
    
    // Protect page - only admins can access
    if (!AuthService.protectPage('admin')) {
        return;
    }
    
    // Update admin name
    const adminName = AuthService.getCurrentUser()?.username || 'Admin';
    document.getElementById('admin-name').textContent = adminName;
    
    // Load overview statistics
    loadOverviewStats();
    
    // Initialize sidebar menu
    initializeAdminMenu();
    
    // Setup form submissions
    setupAdminForms();
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
        showAlert(error.message || 'Failed to add candidate. Check console for details.', 'error');
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
        showAlert(error.message || 'Failed to add candidate. Check console for details.', 'error');
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
                    ${candidates.map((candidate, index) => `
                        <tr>
                            <td>${index + 1}</td>
                            <td>${candidate.name}</td>
                            <td>${candidate.symbol}</td>
                            <td>${maskCNIC(candidate.cnic)}</td>
                            <td>${type === 'mna' ? `NA-${candidate.naSeat}` : `${candidate.province}-${candidate.paSeat}`}</td>
                            <td>${candidate.area || 'N/A'}</td>
                            <td><strong>${candidate.votes || 0}</strong></td>
                        </tr>
                    `).join('')}
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