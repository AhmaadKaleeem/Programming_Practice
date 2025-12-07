// ==================== VOTER.JS - Voter Dashboard ====================

let voterData = null;
let currentSection = 'profile';

// ==================== INITIALIZE VOTER DASHBOARD ====================
function initializeVoterDashboard() {
    console.log('👤 Voter Dashboard Initialized');
    
    // Protect page - only voters can access
    if (!AuthService.protectPage('voter')) {
        return;
    }
    
    // Load voter data
    loadVoterProfile();
    
    // Initialize menu
    initializeSidebarMenu();
    
    // Load voting status
    updateVotingStatusMini();
    setInterval(updateVotingStatusMini, 1000);
}

// ==================== LOAD VOTER PROFILE ====================
async function loadVoterProfile() {
    try {
        showLoader('Loading profile...');
        
        const voterInfo = AuthService.getVoterData();
        if (!voterInfo) {
            throw new Error('Voter data not found');
        }
        
        voterData = voterInfo;
        
        // Update all UI elements
        updateProfileDisplay();
        updateConstituencyDisplay();
        updateVotingBadges();
        
        hideLoader();
    } catch (error) {
        hideLoader();
        showAlert('Error loading profile: ' + error.message, 'error');
    }
}

// ==================== UPDATE PROFILE DISPLAY ====================
function updateProfileDisplay() {
    if (!voterData) return;
    
    // Sidebar
    document.getElementById('voter-name').textContent = voterData.name;
    document.getElementById('voter-id').textContent = voterData.voterId || 'N/A';
    
    // Welcome banner
    document.getElementById('welcome-name').textContent = voterData.name;
    
    // Profile section
    document.getElementById('profile-name').textContent = voterData.name;
    document.getElementById('profile-cnic').textContent = formatCNIC(voterData.cnic);
    document.getElementById('profile-age').textContent = voterData.age + ' years';
    document.getElementById('profile-voter-id').textContent = voterData.voterId || 'N/A';
    document.getElementById('profile-province').textContent = voterData.province || 'N/A';
    
    // Vote status
    const statusHtml = `
        <span class="status-badge ${voterData.hasVotedMNA ? 'voted' : 'not-voted'}">
            MNA: ${voterData.hasVotedMNA ? '✓ Voted' : '✗ Not Voted'}
        </span>
        <span class="status-badge ${voterData.hasVotedMPA ? 'voted' : 'not-voted'}">
            MPA: ${voterData.hasVotedMPA ?  '✓ Voted' : '✗ Not Voted'}
        </span>
    `;
    document.getElementById('profile-vote-status').innerHTML = statusHtml;
}

// ==================== UPDATE CONSTITUENCY DISPLAY ====================
function updateConstituencyDisplay() {
    if (!voterData) return;
    
    // NA Constituency
    document.getElementById('na-number').textContent = `NA-${voterData.naSeat}`;
    document.getElementById('na-area').textContent = 'National Assembly Constituency';
    
    // PA Constituency
    if (voterData.province === 'Islamabad') {
        document.getElementById('pa-number').textContent = 'N/A';
        document.getElementById('pa-area').textContent = 'Not Applicable (Islamabad)';
    } else {
        const provinceInfo = getProvinceFromNA(voterData.naSeat);
        document.getElementById('pa-number').textContent = `${provinceInfo?.code}-${voterData.paSeat}`;
        document.getElementById('pa-area').textContent = 'Provincial Assembly Constituency';
    }
}

// ==================== UPDATE VOTING BADGES ====================
function updateVotingBadges() {
    if (!voterData) return;
    
    const mnaBadge = document.getElementById('mna-badge');
    const mpaBadge = document.getElementById('mpa-badge');
    
    if (mnaBadge) {
        if (voterData.hasVotedMNA) {
            mnaBadge.textContent = '✓';
            mnaBadge.className = 'badge success';
        } else {
            mnaBadge.textContent = '! ';
            mnaBadge.className = 'badge';
        }
    }
    
    if (mpaBadge) {
        if (voterData.hasVotedMPA) {
            mpaBadge.textContent = '✓';
            mpaBadge.className = 'badge success';
        } else {
            mpaBadge.textContent = '!';
            mpaBadge.className = 'badge';
        }
    }
}

// ==================== UPDATE VOTING STATUS MINI ====================
function updateVotingStatusMini() {
    const statusEl = document.getElementById('voting-status-mini');
    if (!statusEl) return;
    
    const votingStatus = isVotingOpen();
    
    if (votingStatus.open) {
        statusEl.innerHTML = `
            <h4>Voting Status</h4>
            <p class="status status-open">🟢 OPEN</p>
        `;
    } else {
        statusEl.innerHTML = `
            <h4>Voting Status</h4>
            <p class="status status-closed">🔴 CLOSED</p>
        `;
    }
}

// ==================== SIDEBAR MENU ====================
function initializeSidebarMenu() {
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
            
            showSection(section);
        });
    });
}

// ==================== SHOW SECTION ====================
window.showSection = function(sectionName) {
    currentSection = sectionName;
    
    // Hide all sections
    document.querySelectorAll('.dashboard-section').forEach(section => {
        section.classList.remove('active');
    });
    
    // Show selected section
    const targetSection = document.getElementById(`${sectionName}-section`);
    if (targetSection) {
        targetSection.classList.add('active');
        
        // Load section data
        if (sectionName === 'vote-mna') {
            loadMNACandidates();
        } else if (sectionName === 'vote-mpa') {
            loadMPACandidates();
        }
    }
};

// ==================== LOAD MNA CANDIDATES ====================
async function loadMNACandidates() {
    const container = document.getElementById('mna-candidates-container');
    const statusAlert = document.getElementById('mna-voting-status');
    
    if (!container) return;
    
    // Check if already voted
    if (voterData.hasVotedMNA) {
        statusAlert.className = 'voting-status-alert already-voted';
        statusAlert.innerHTML = `
            <i class="fas fa-check-circle" style="font-size: 2rem; margin-bottom: 0.5rem;"></i>
            <h3>You have already voted for MNA</h3>
            <p>Thank you for participating in the election!</p>
        `;
        container.innerHTML = '';
        return;
    }
    
    // Check voting time
    const votingStatus = isVotingOpen();
    if (!votingStatus.open) {
        statusAlert.className = 'voting-status-alert closed';
        statusAlert.innerHTML = `
            <i class="fas fa-times-circle" style="font-size: 2rem; margin-bottom: 0.5rem;"></i>
            <h3>Voting is Currently Closed</h3>
            <p>Voting hours: ${formatTime(CONFIG.ELECTION.votingHours.startHour)} - ${formatTime(CONFIG.ELECTION.votingHours.endHour)}</p>
        `;
        container.innerHTML = '';
        return;
    }
    
    statusAlert.className = 'voting-status-alert open';
    statusAlert.innerHTML = `
        <i class="fas fa-check-circle" style="font-size: 2rem; margin-bottom: 0.5rem;"></i>
        <h3>Voting is Open - Cast Your Vote</h3>
        <p>Select your preferred candidate below</p>
    `;
    
    try {
        container.innerHTML = '<div class="loading"><i class="fas fa-spinner fa-spin"></i><p>Loading candidates...</p></div>';
        
        const response = await API.call(`${CONFIG.API.ENDPOINTS.GET_MNA_CANDIDATES}? naSeat=${voterData.naSeat}`);
        
        if (response.success && response.data.length > 0) {
            displayCandidates(response.data, 'mna', container);
        } else {
            container.innerHTML = `
                <div class="no-candidates">
                    <i class="fas fa-inbox"></i>
                    <h3>No Candidates Available</h3>
                    <p>No candidates registered for NA-${voterData.naSeat} yet</p>
                </div>
            `;
        }
    } catch (error) {
        container.innerHTML = `
            <div class="error-message">
                <i class="fas fa-exclamation-circle"></i>
                <p>Error loading candidates: ${error.message}</p>
            </div>
        `;
    }
}

// ==================== LOAD MPA CANDIDATES ====================
async function loadMPACandidates() {
    const container = document.getElementById('mpa-candidates-container');
    const statusAlert = document.getElementById('mpa-voting-status');
    
    if (!container) return;
    
    // Check if Islamabad
    if (voterData.province === 'Islamabad') {
        statusAlert.className = 'voting-status-alert closed';
        statusAlert.innerHTML = `
            <i class="fas fa-info-circle" style="font-size: 2rem; margin-bottom: 0.5rem;"></i>
            <h3>Provincial Voting Not Applicable</h3>
            <p>Islamabad residents vote for National Assembly only</p>
        `;
        container.innerHTML = '';
        return;
    }
    
    // Check if already voted
    if (voterData.hasVotedMPA) {
        statusAlert.className = 'voting-status-alert already-voted';
        statusAlert.innerHTML = `
            <i class="fas fa-check-circle" style="font-size: 2rem; margin-bottom: 0.5rem;"></i>
            <h3>You have already voted for MPA</h3>
            <p>Thank you for participating in the election!</p>
        `;
        container.innerHTML = '';
        return;
    }
    
    // Check voting time
    const votingStatus = isVotingOpen();
    if (!votingStatus.open) {
        statusAlert.className = 'voting-status-alert closed';
        statusAlert.innerHTML = `
            <i class="fas fa-times-circle" style="font-size: 2rem; margin-bottom: 0.5rem;"></i>
            <h3>Voting is Currently Closed</h3>
            <p>Voting hours: ${formatTime(CONFIG.ELECTION.votingHours.startHour)} - ${formatTime(CONFIG.ELECTION.votingHours.endHour)}</p>
        `;
        container.innerHTML = '';
        return;
    }
    
    statusAlert.className = 'voting-status-alert open';
    statusAlert.innerHTML = `
        <i class="fas fa-check-circle" style="font-size: 2rem; margin-bottom: 0.5rem;"></i>
        <h3>Voting is Open - Cast Your Vote</h3>
        <p>Select your preferred candidate below</p>
    `;
    
    try {
        container.innerHTML = '<div class="loading"><i class="fas fa-spinner fa-spin"></i><p>Loading candidates...</p></div>';
        
        const response = await API.call(`${CONFIG.API.ENDPOINTS.GET_MPA_CANDIDATES}?province=${voterData.province}&paSeat=${voterData.paSeat}`);
        
        if (response.success && response.data.length > 0) {
            displayCandidates(response.data, 'mpa', container);
        } else {
            container.innerHTML = `
                <div class="no-candidates">
                    <i class="fas fa-inbox"></i>
                    <h3>No Candidates Available</h3>
                    <p>No candidates registered for this constituency yet</p>
                </div>
            `;
        }
    } catch (error) {
        container.innerHTML = `
            <div class="error-message">
                <i class="fas fa-exclamation-circle"></i>
                <p>Error loading candidates: ${error.message}</p>
            </div>
        `;
    }
}

// ==================== DISPLAY CANDIDATES ====================
function displayCandidates(candidates, type, container) {
    const html = `
        <div class="candidates-grid">
            ${candidates.map((candidate, index) => `
                <div class="candidate-card" onclick="selectCandidate('${type}', '${candidate.cnic}')">
                    <input type="radio" name="${type}-candidate" value="${candidate.cnic}" class="candidate-radio" id="${type}-${index}">
                    <div class="candidate-info">
                        <h3 class="candidate-name">${candidate.name}</h3>
                        <div class="candidate-details">
                            <span class="candidate-detail">
                                <i class="fas fa-flag"></i>
                                ${candidate.symbol}
                            </span>
                            <span class="candidate-detail">
                                <i class="fas fa-id-card"></i>
                                ${maskCNIC(candidate.cnic)}
                            </span>
                            <span class="candidate-detail">
                                <i class="fas fa-map-marker-alt"></i>
                                ${type === 'mna' ? `NA-${candidate.constituency}` : `${candidate.provinceName || 'P'}-${candidate.provisionalPP}`}
                            </span>
                        </div>
                    </div>
                </div>
            `).join('')}
        </div>
        <div class="vote-button-container">
            <button id="cast-${type}-vote-btn" class="btn btn-primary btn-lg" onclick="castVote('${type}')" disabled>
                <i class="fas fa-check-circle"></i>
                Cast Vote for ${type.toUpperCase()}
            </button>
        </div>
    `;
    
    container.innerHTML = html;
}

// ==================== SELECT CANDIDATE ====================
window.selectCandidate = function(type, cnic) {
    // Unselect all
    document.querySelectorAll(`.candidate-card`).forEach(card => {
        card.classList.remove('selected');
    });
    
    // Select clicked
    event.currentTarget.classList.add('selected');
    
    // Check radio
    const radio = document.getElementById(`${type}-${Array.from(document.querySelectorAll(`input[name="${type}-candidate"]`)).findIndex(r => r.value === cnic)}`);
    if (radio) radio.checked = true;
    
    // Enable vote button
    const voteBtn = document.getElementById(`cast-${type}-vote-btn`);
    if (voteBtn) voteBtn.disabled = false;
};

// ==================== CAST VOTE ====================
window.castVote = async function(type) {
    const selectedRadio = document.querySelector(`input[name="${type}-candidate"]:checked`);
    
    if (!selectedRadio) {
        showAlert('Please select a candidate', 'warning');
        return;
    }
    
    const candidateCnic = selectedRadio.value;
    const endpoint = type === 'mna' ? CONFIG.API.ENDPOINTS.CAST_VOTE_MNA : CONFIG.API.ENDPOINTS.CAST_VOTE_MPA;
    
    // Confirm vote
    showConfirmDialog(
        `Are you sure you want to vote for this candidate? This action cannot be undone.`,
        async () => {
            try {
                showLoader('Casting your vote...');
                
                const response = await API.call(endpoint, 'POST', {
                    candidateCnic: candidateCnic
                });
                
                hideLoader();
                
                if (response.success) {
                    // Update voter data
                    if (type === 'mna') {
                        voterData.hasVotedMNA = true;
                    } else {
                        voterData.hasVotedMPA = true;
                    }
                    
                    AuthService.updateVoterData(voterData);
                    
                    showAlert('Vote cast successfully!  Your vote has been recorded in the blockchain.', 'success');
                    
                    // Reload section
                    setTimeout(() => {
                        if (type === 'mna') {
                            loadMNACandidates();
                        } else {
                            loadMPACandidates();
                        }
                        updateVotingBadges();
                        updateProfileDisplay();
                    }, 2000);
                } else {
                    showAlert(response.message || 'Failed to cast vote', 'error');
                }
            } catch (error) {
                hideLoader();
                showAlert(error.message || 'Failed to cast vote', 'error');
            }
        },
        null
    );
};

// ==================== DOM READY ====================
document.addEventListener('DOMContentLoaded', () => {
    initializeVoterDashboard();
});