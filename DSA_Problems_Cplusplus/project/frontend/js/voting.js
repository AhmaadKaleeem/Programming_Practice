// ==================== VOTING.JS - Separate Voting Pages ====================

let voterData = null;
let selectedCandidate = null;

// ==================== INITIALIZE MNA VOTING ====================
window.initializeMNAVoting = async function() {
    console.log('🗳️ MNA Voting Page Initialized');
    
    // Protect page
    if (! AuthService.protectPage('voter')) {
        return;
    }
    
    voterData = AuthService.getVoterData();
    
    if (!voterData) {
        showAlert('Voter data not found', 'error');
        setTimeout(() => window.location.href = 'voter-dashboard.html', 2000);
        return;
    }
    
    updateVoterInfo();
    await checkVotingEligibility('MNA');
    await loadMNACandidatesPage();
};

// ==================== INITIALIZE MPA VOTING ====================
window.initializeMPAVoting = async function() {
    console.log('🗳️ MPA Voting Page Initialized');
    
    // Protect page
    if (!AuthService.protectPage('voter')) {
        return;
    }
    
    voterData = AuthService.getVoterData();
    
    if (!voterData) {
        showAlert('Voter data not found', 'error');
        setTimeout(() => window.location.href = 'voter-dashboard.html', 2000);
        return;
    }
    
    updateVoterInfo();
    await checkVotingEligibility('MPA');
    await loadMPACandidatesPage();
};

// ==================== UPDATE VOTER INFO ====================
function updateVoterInfo() {
    document.getElementById('voter-name-display').textContent = voterData.name;
    document.getElementById('voter-cnic-display').textContent = formatCNIC(voterData.cnic);
    
    if (document.getElementById('voter-constituency-display')) {
        document.getElementById('voter-constituency-display').textContent = `NA-${voterData.naSeat}`;
    }
    
    if (document.getElementById('voter-province-display')) {
        document.getElementById('voter-province-display').textContent = voterData.province;
    }
    
    if (document.getElementById('voter-pa-display')) {
        const provinceInfo = getProvinceFromNA(voterData.naSeat);
        document.getElementById('voter-pa-display').textContent = voterData.province === 'Islamabad' ? 'N/A' : `${provinceInfo?.code}-${voterData.paSeat}`;
    }
}

// ==================== CHECK VOTING ELIGIBILITY ====================
async function checkVotingEligibility(type) {
    const statusDiv = document.getElementById(`${type.toLowerCase()}-voting-status`);
    
    // Check if already voted
    if ((type === 'MNA' && voterData.hasVotedMNA) || (type === 'MPA' && voterData.hasVotedMPA)) {
        statusDiv.className = 'voting-status-alert already-voted';
        statusDiv.innerHTML = `
            <i class="fas fa-check-circle" style="font-size: 3rem; color: #ffc107; margin-bottom: 1rem;"></i>
            <h3 style="color: #ffc107;">You have already voted for ${type}</h3>
            <p>Thank you for participating in the election! </p>
            <div style="margin-top: 1rem;">
                <a href="voter-dashboard.html" class="btn btn-secondary">Back to Dashboard</a>
            </div>
        `;
        disableVoting();
        return false;
    }
    
    // Check if Islamabad for MPA
    if (type === 'MPA' && voterData.province === 'Islamabad') {
        statusDiv.className = 'voting-status-alert closed';
        statusDiv.innerHTML = `
            <i class="fas fa-info-circle" style="font-size: 3rem; color: #2196f3; margin-bottom: 1rem;"></i>
            <h3 style="color: #2196f3;">Provincial Voting Not Applicable</h3>
            <p>Islamabad residents vote for National Assembly only</p>
            <div style="margin-top: 1rem;">
                <a href="voter-dashboard.html" class="btn btn-secondary">Back to Dashboard</a>
            </div>
        `;
        disableVoting();
        return false;
    }
    
    // Check voting time
    const votingStatus = isVotingOpen();
    if (!votingStatus.open) {
        statusDiv.className = 'voting-status-alert closed';
        statusDiv.innerHTML = `
            <i class="fas fa-times-circle" style="font-size: 3rem; color: #dc3545; margin-bottom: 1rem;"></i>
            <h3 style="color: #dc3545;">Voting is Currently Closed</h3>
            <p>Voting hours: ${formatTime(CONFIG.ELECTION.votingHours.startHour)} - ${formatTime(CONFIG.ELECTION.votingHours.endHour)}</p>
            <p>Election Date: ${formatElectionDate()}</p>
        `;
        disableVoting();
        return false;
    }
    
    statusDiv.className = 'voting-status-alert open';
    statusDiv.innerHTML = `
        <i class="fas fa-check-circle" style="font-size: 3rem; color: #28a745; margin-bottom: 1rem;"></i>
        <h3 style="color: #28a745;">✓ Voting is Open</h3>
        <p>Select your preferred candidate and cast your vote</p>
    `;
    
    return true;
}

// ==================== LOAD MNA CANDIDATES PAGE ====================
async function loadMNACandidatesPage() {
    const container = document.getElementById('mna-candidates-list');
    
    try {
        container.innerHTML = '<div class="loading"><i class="fas fa-spinner fa-spin"></i><p>Loading candidates...</p></div>';
        
        const response = await API.call(`${CONFIG.API.ENDPOINTS.GET_MNA_CANDIDATES}?naSeat=${voterData.naSeat}`);
        
        if (response.success && response.data.length > 0) {
            displayVotingCandidates(response.data, 'mna', container);
        } else {
            container.innerHTML = `
                <div class="no-candidates">
                    <i class="fas fa-inbox" style="font-size: 3rem; color: var(--text-muted); margin-bottom: 1rem;"></i>
                    <h3>No Candidates Available</h3>
                    <p>No candidates registered for NA-${voterData.naSeat} yet</p>
                    <a href="voter-dashboard.html" class="btn btn-secondary" style="margin-top: 1rem;">Back to Dashboard</a>
                </div>
            `;
            disableVoting();
        }
    } catch (error) {
        container.innerHTML = `
            <div class="error-message show">
                <i class="fas fa-exclamation-circle"></i>
                <p>Error loading candidates: ${error.message}</p>
                <a href="voter-dashboard.html" class="btn btn-secondary" style="margin-top: 1rem;">Back to Dashboard</a>
            </div>
        `;
        disableVoting();
    }
}

// ==================== LOAD MPA CANDIDATES PAGE ====================
async function loadMPACandidatesPage() {
    const container = document.getElementById('mpa-candidates-list');
    
    try {
        container.innerHTML = '<div class="loading"><i class="fas fa-spinner fa-spin"></i><p>Loading candidates...</p></div>';
        
        const response = await API.call(`${CONFIG.API.ENDPOINTS.GET_MPA_CANDIDATES}?province=${voterData.province}&paSeat=${voterData.paSeat}`);
        
        if (response.success && response.data.length > 0) {
            displayVotingCandidates(response.data, 'mpa', container);
        } else {
            const provinceInfo = getProvinceFromNA(voterData.naSeat);
            container.innerHTML = `
                <div class="no-candidates">
                    <i class="fas fa-inbox" style="font-size: 3rem; color: var(--text-muted); margin-bottom: 1rem;"></i>
                    <h3>No Candidates Available</h3>
                    <p>No candidates registered for ${provinceInfo?.code}-${voterData.paSeat} yet</p>
                    <a href="voter-dashboard.html" class="btn btn-secondary" style="margin-top: 1rem;">Back to Dashboard</a>
                </div>
            `;
            disableVoting();
        }
    } catch (error) {
        container.innerHTML = `
            <div class="error-message show">
                <i class="fas fa-exclamation-circle"></i>
                <p>Error loading candidates: ${error.message}</p>
                <a href="voter-dashboard.html" class="btn btn-secondary" style="margin-top: 1rem;">Back to Dashboard</a>
            </div>
        `;
        disableVoting();
    }
}

// ==================== DISPLAY VOTING CANDIDATES ====================
function displayVotingCandidates(candidates, type, container) {
    const html = `
        <div class="candidates-grid">
            ${candidates.map((candidate, index) => `
                <label class="candidate-card" for="${type}-candidate-${index}">
                    <input 
                        type="radio" 
                        name="${type}-candidate" 
                        value="${candidate.cnic}" 
                        class="candidate-radio" 
                        id="${type}-candidate-${index}"
                        onchange="handleCandidateSelection('${type}', '${candidate.cnic}')"
                    >
                    <div class="candidate-info">
                        <h3 class="candidate-name">${candidate.name}</h3>
                        <div class="candidate-details">
                            <span class="candidate-detail">
                                <i class="fas fa-flag"></i>
                                Symbol: ${candidate.symbol}
                            </span>
                            <span class="candidate-detail">
                                <i class="fas fa-id-card"></i>
                                CNIC: ${maskCNIC(candidate.cnic)}
                            </span>
                            <span class="candidate-detail">
                                <i class="fas fa-map-marker-alt"></i>
                                ${type === 'mna' ?  `NA-${candidate.constituency}` : `${candidate.provinceName || 'P'}-${candidate.provisionalPP}`}
                            </span>
                        </div>
                    </div>
                </label>
            `).join('')}
        </div>
    `;
    
    container.innerHTML = html;
    
    // Enable vote button functionality
    const voteBtn = document.getElementById(`cast-${type}-vote-btn`);
    if (voteBtn) {
        voteBtn.onclick = () => castVoteFromPage(type);
    }
}

// ==================== HANDLE CANDIDATE SELECTION ====================
window.handleCandidateSelection = function(type, cnic) {
    selectedCandidate = cnic;
    
    // Update UI
    document.querySelectorAll('.candidate-card').forEach(card => {
        card.classList.remove('selected');
    });
    
    event.target.closest('.candidate-card').classList.add('selected');
    
    // Enable vote button
    const voteBtn = document.getElementById(`cast-${type}-vote-btn`);
    if (voteBtn) {
        voteBtn.disabled = false;
    }
};

// ==================== CAST VOTE FROM PAGE ====================
async function castVoteFromPage(type) {
    if (!selectedCandidate) {
        showAlert('Please select a candidate', 'warning');
        return;
    }
    
    const endpoint = type === 'mna' ? CONFIG.API.ENDPOINTS.CAST_VOTE_MNA : CONFIG.API.ENDPOINTS.CAST_VOTE_MPA;
    
    showConfirmDialog(
        `Are you sure you want to vote for this candidate?\n\nThis action cannot be undone! `,
        async () => {
            try {
                showLoader('Casting your vote...');
                
                const response = await API.call(endpoint, 'POST', {
                    candidateCnic: selectedCandidate
                });
                
                hideLoader();
                
                if (response.success) {
                    // Update session
                    if (type === 'mna') {
                        voterData.hasVotedMNA = true;
                    } else {
                        voterData.hasVotedMPA = true;
                    }
                    AuthService.updateVoterData(voterData);
                    
                    // Show success
                    showAlert('✓ Vote cast successfully!  Your vote has been recorded in the blockchain.', 'success');
                    
                    // Redirect to dashboard
                    setTimeout(() => {
                        window.location.href = 'voter-dashboard.html';
                    }, 3000);
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
}

// ==================== DISABLE VOTING ====================
function disableVoting() {
    const voteBtns = document.querySelectorAll('[id^="cast-"][id$="-vote-btn"]');
    voteBtns.forEach(btn => {
        btn.disabled = true;
        btn.style.opacity = '0.5';
        btn.style.cursor = 'not-allowed';
    });
    
    const candidateCards = document.querySelectorAll('.candidate-card');
    candidateCards.forEach(card => {
        card.style.pointerEvents = 'none';
        card.style.opacity = '0.6';
    });
}