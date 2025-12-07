// ==================== ADMIN.JS - Admin Panel ====================

let currentAdminSection = 'overview';
let naAreaNames = {};
let paAreaNames = {};

// ==================== HELPER FUNCTIONS ====================
// Get NA seat number with fallback for backward compatibility
function getNASeat(candidate) {
    return candidate.naSeat || candidate.constituency || 0;
}

// Get PA seat number with fallback for backward compatibility
function getPASeat(candidate) {
    return candidate.paSeat || candidate.provisionalPP || candidate.provisional_pp || 0;
}

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
    
    // Load constituency names
    loadConstituencyNames();
    
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

// ==================== LOAD CONSTITUENCY NAMES ====================
async function loadConstituencyNames() {
    try {
        console.log('📡 Loading constituency names for admin panel...');
        
        // Load NA names using API service
        const naResponse = await API.call(CONFIG.API.ENDPOINTS.GET_NA_NAMES);
        if (naResponse.success) {
            naAreaNames = naResponse.data;
            console.log(`✅ Loaded ${Object.keys(naAreaNames).length} NA constituencies`);
            populateMNAConstituencyDropdown();
        }
    } catch (error) {
        console.error('❌ Error loading constituency names:', error);
        naAreaNames = {};
    }
}

// ==================== POPULATE MNA CONSTITUENCY DROPDOWN ====================
function populateMNAConstituencyDropdown() {
    const mnaConstituencySelect = document.getElementById('mna-constituency');
    if (!mnaConstituencySelect) return;
    
    // Check if already populated
    if (mnaConstituencySelect.options.length > 1) return;
    
    const constituencies = {
        'KPK': { start: 1, end: 45, label: 'Khyber Pakhtunkhwa (NA 1-45)' },
        'Islamabad': { start: 46, end: 48, label: 'Islamabad Capital Territory (NA 46-48)' },
        'Punjab': { start: 49, end: 189, label: 'Punjab (NA 49-189)' },
        'Sindh': { start: 190, end: 250, label: 'Sindh (NA 190-250)' },
        'Balochistan': { start: 251, end: 266, label: 'Balochistan (NA 251-266)' }
    };
    
    // Clear existing options except first one
    mnaConstituencySelect.innerHTML = '<option value="">Select NA Constituency</option>';
    
    for (const [province, range] of Object.entries(constituencies)) {
        const optgroup = document.createElement('optgroup');
        optgroup.label = range.label;
        
        for (let i = range.start; i <= range.end; i++) {
            const option = document.createElement('option');
            option.value = i;
            const areaName = naAreaNames[i] || '';
            option.textContent = areaName ? `NA-${i} | ${areaName}` : `NA-${i}`;
            optgroup.appendChild(option);
        }
        
        mnaConstituencySelect.appendChild(optgroup);
    }
    
    console.log('✅ MNA constituency dropdown populated');
}

// ==================== LOAD PA NAMES FOR PROVINCE ====================
async function loadPANamesForProvince(province) {
    try {
        console.log(`📡 Loading ${province} PA constituency names...`);
        // Use API service with query parameter
        const response = await API.call(`${CONFIG.API.ENDPOINTS.GET_PA_NAMES}?province=${province}`);
        
        if (response.success) {
            paAreaNames = response.data;
            console.log(`✅ Loaded ${Object.keys(paAreaNames).length} ${province} PA constituencies`);
            return true;
        }
        return false;
    } catch (error) {
        console.error('❌ Error loading PA names:', error);
        paAreaNames = {};
        return false;
    }
}

// ==================== POPULATE MPA SEAT DROPDOWN ====================
function populateMPASeatDropdown(province) {
    const mpaSeatSelect = document.getElementById('mpa-seat');
    if (!mpaSeatSelect) return;
    
    const constituencyInfo = CONFIG.CONSTITUENCIES[province];
    if (!constituencyInfo) return;
    
    // Clear existing options
    mpaSeatSelect.innerHTML = '<option value="">Select PA Constituency</option>';
    
    const provinceCode = constituencyInfo.code;
    const maxSeats = constituencyInfo.paSeats;
    
    for (let i = 1; i <= maxSeats; i++) {
        const option = document.createElement('option');
        option.value = i;
        const areaName = paAreaNames[i] || '';
        option.textContent = areaName ? `${provinceCode}-${i} | ${areaName}` : `${provinceCode}-${i}`;
        mpaSeatSelect.appendChild(option);
    }
    
    console.log(`✅ MPA seat dropdown populated with ${maxSeats} options`);
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
    
    // MPA Province change handler
    const mpaProvinceSelect = document.getElementById('mpa-province');
    if (mpaProvinceSelect) {
        mpaProvinceSelect.addEventListener('change', async (e) => {
            const province = e.target.value;
            if (province) {
                await loadPANamesForProvince(province);
                populateMPASeatDropdown(province);
            } else {
                // Clear MPA seat dropdown
                const mpaSeatSelect = document.getElementById('mpa-seat');
                if (mpaSeatSelect) {
                    mpaSeatSelect.innerHTML = '<option value="">Select Province First</option>';
                }
            }
        });
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
                    ${candidates.map((candidate, index) => {
                        let constituency = '';
                        let area = candidate.area || 'N/A';
                        
                        if (type === 'mna') {
                            const naSeat = getNASeat(candidate);
                            constituency = `NA-${naSeat}`;
                        } else {
                            const paSeat = getPASeat(candidate);
                            const provinceCode = getProvinceCode(candidate.province);
                            constituency = `${provinceCode}-${paSeat}`;
                        }
                        
                        return `
                            <tr>
                                <td>${index + 1}</td>
                                <td>${candidate.name}</td>
                                <td>${candidate.symbol}</td>
                                <td>${maskCNIC(candidate.cnic)}</td>
                                <td>${constituency}</td>
                                <td>${area}</td>
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

// ==================== GET PROVINCE CODE ====================
function getProvinceCode(province) {
    const codes = {
        'Punjab': 'PP',
        'Sindh': 'PS',
        'KPK': 'PK',
        'Balochistan': 'PB',
        'Islamabad': 'I'
    };
    return codes[province] || province;
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
                            ${mnaResults.map((candidate, index) => {
                                const naSeat = getNASeat(candidate);
                                return `
                                    <tr ${index === 0 ? 'class="winner"' : ''}>
                                        <td>${index + 1}${index === 0 ? ' 🏆' : ''}</td>
                                        <td>${candidate.name}</td>
                                        <td>${candidate.symbol}</td>
                                        <td>NA-${naSeat}</td>
                                        <td><strong>${candidate.votes || 0}</strong></td>
                                    </tr>
                                `;
                            }).join('')}
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
                            ${mpaResults.map((candidate, index) => {
                                const paSeat = getPASeat(candidate);
                                const provinceCode = getProvinceCode(candidate.province);
                                return `
                                    <tr ${index === 0 ? 'class="winner"' : ''}>
                                        <td>${index + 1}${index === 0 ? ' 🏆' : ''}</td>
                                        <td>${candidate.name}</td>
                                        <td>${candidate.symbol}</td>
                                        <td>${candidate.province}</td>
                                        <td>${provinceCode}-${paSeat}</td>
                                        <td><strong>${candidate.votes || 0}</strong></td>
                                    </tr>
                                `;
                            }).join('')}
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