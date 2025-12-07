// ==================== API SERVICE FOR C++ BACKEND ====================

class APIService {
    constructor() {
        this.baseURL = CONFIG.API.BASE_URL;
        this.timeout = CONFIG.API.TIMEOUT;
        this.useMock = CONFIG.API.USE_MOCK;
    }
    
    // Generic API call
    async call(endpoint, method = 'GET', data = null) {
        if (this.useMock) {
            return await this.mockAPI(endpoint, method, data);
        }
        
        const url = `${this.baseURL}${endpoint}`;
        
        const options = {
            method: method,
            headers: { 'Content-Type': 'application/json' }
        };
        
        // Add auth token if exists
        const token = AuthService.getToken();
        if (token) {
            options.headers['Authorization'] = `Bearer ${token}`;
        }
        
        // Add body for POST/PUT
        if (data && (method === 'POST' || method === 'PUT')) {
            options.body = JSON.stringify(data);
        }
        
        try {
            const controller = new AbortController();
            const timeoutId = setTimeout(() => controller.abort(), this.timeout);
            
            options.signal = controller.signal;
            const response = await fetch(url, options);
            clearTimeout(timeoutId);
            
            if (!response.ok) {
                const error = await response.json();
                throw new Error(error.message || 'API request failed');
            }
            
            return await response.json();
        } catch (error) {
            if (error.name === 'AbortError') {
                throw new Error('Request timeout');
            }
            throw error;
        }
    }
    
    
    async mockAPI(endpoint, method, data) {
        await new Promise(resolve => setTimeout(resolve, 500));
        
        // Register Voter (matches Election::add_voter())
        if (endpoint === CONFIG.API.ENDPOINTS.REGISTER_VOTER && method === 'POST') {
            return this.mockRegisterVoter(data);
        }
        
        // Login Voter (matches VoterManager::authenticate_voter())
        if (endpoint === CONFIG.API.ENDPOINTS.LOGIN_VOTER && method === 'POST') {
            return this.mockLoginVoter(data);
        }
        
        // Get Voter Profile
        if (endpoint === CONFIG.API.ENDPOINTS.GET_VOTER_PROFILE) {
            return this.mockGetVoterProfile();
        }
        
        // Check Vote Status (matches has_voter_voted_mna/mpa())
        if (endpoint === CONFIG.API.ENDPOINTS.CHECK_VOTE_STATUS) {
            return this.mockCheckVoteStatus();
        }
        
        // Get MNA Candidates (matches Election::display_mna())
        if (endpoint.startsWith(CONFIG.API.ENDPOINTS.GET_MNA_CANDIDATES)) {
            const params = new URLSearchParams(endpoint.split('?')[1]);
            return this.mockGetMNACandidates(params.get('naSeat'));
        }
        
        // Get MPA Candidates (matches Election::display_mpa())
        if (endpoint.startsWith(CONFIG.API.ENDPOINTS.GET_MPA_CANDIDATES)) {
            const params = new URLSearchParams(endpoint.split('?')[1]);
            return this.mockGetMPACandidates(params.get('province'), params.get('paSeat'));
        }
        
        // Cast Vote MNA (matches Election::cast_mna_vote())
        if (endpoint === CONFIG.API.ENDPOINTS.CAST_VOTE_MNA && method === 'POST') {
            return this.mockCastVote('MNA', data);
        }
        
        // Cast Vote MPA (matches Election::cast_mpa_vote())
        if (endpoint === CONFIG.API.ENDPOINTS.CAST_VOTE_MPA && method === 'POST') {
            return this.mockCastVote('MPA', data);
        }
        
        // Admin Login (matches Admin::authenticate_admin())
        if (endpoint === CONFIG.API.ENDPOINTS.LOGIN_ADMIN && method === 'POST') {
            return this.mockLoginAdmin(data);
        }
        
        // Add MNA Candidate (matches Election::add_mna_candidate())
        if (endpoint === CONFIG.API.ENDPOINTS.ADD_MNA_CANDIDATE && method === 'POST') {
            return this.mockAddMNACandidate(data);
        }
        
        // Add MPA Candidate (matches Election::add_mpa_candidate())
        if (endpoint === CONFIG.API.ENDPOINTS.ADD_MPA_CANDIDATE && method === 'POST') {
            return this.mockAddMPACandidate(data);
        }
        
        // Get All MNA Candidates
        if (endpoint === CONFIG.API.ENDPOINTS.GET_ALL_MNA) {
            return this.mockGetAllMNA();
        }
        
        // Get All MPA Candidates
        if (endpoint === CONFIG.API.ENDPOINTS.GET_ALL_MPA) {
            return this.mockGetAllMPA();
        }
        
        // Get Voting Status (matches is_voting_time())
        if (endpoint === CONFIG.API.ENDPOINTS.GET_VOTING_STATUS) {
            return this.mockGetVotingStatus();
        }
        
        // Get Results (matches Election::display_all_votes())
        if (endpoint === CONFIG.API.ENDPOINTS.GET_RESULTS) {
            return this.mockGetResults();
        }
        
        // Get Winners (matches Election::display_winners_till_now())
        if (endpoint === CONFIG.API.ENDPOINTS.GET_WINNERS) {
            return this.mockGetWinners();
        }
        
        // Verify Ledger (matches Ledger::verify_ledger())
        if (endpoint === CONFIG.API.ENDPOINTS.VERIFY_LEDGER) {
            return this.mockVerifyLedger();
        }
        
        // View Ledger (matches Ledger::display_ledger())
        if (endpoint === CONFIG.API.ENDPOINTS.VIEW_LEDGER) {
            return this.mockViewLedger();
        }
        
        throw new Error('Mock endpoint not implemented');
    }
    
    // Mock Implementations
    
    mockRegisterVoter(data) {
        const voters = JSON.parse(localStorage.getItem('voters') || '[]');
        
        // Check if CNIC already exists
        if (voters.find(v => v.cnic === data.cnic)) {
            throw new Error('Error!  CNIC Already Registered');
        }
        
        // Generate Voter ID (matches auto_generate_voter_id())
        const hash = Math.abs(this.simpleHash(data.cnic)) % 100000;
        const voterId = `VTR${hash}`;
        
        const voter = {
            voterId: voterId,
            name: data.name,
            cnic: data.cnic,
            password: data.password,
            age: data.age,
            na: data.naSeat,
            province: data.province,
            provinceName: data.provinceCode,
            provisionalP: data.paSeat || 0,
            hasVotedMNA: false,
            hasVotedMPA: false,
            checkVote: false,
            registeredAt: new Date().toISOString()
        };
        
        voters.push(voter);
        localStorage.setItem('voters', JSON.stringify(voters));
        
        return {
            success: true,
            message: 'Voter Registered Successfully',
            data: { voterId }
        };
    }
    
    mockLoginVoter(data) {
        const voters = JSON.parse(localStorage.getItem('voters') || '[]');
        const voter = voters.find(v => v.cnic === data.cnic && v.password === data.password);
        
        if (!voter) {
            throw new Error('Invalid Credentials');
        }
        
        const token = btoa(JSON.stringify({ cnic: voter.cnic, type: 'voter' }));
        
        return {
            success: true,
            message: 'Login successful',
            data: {
                token,
                voter: {
                    voterId: voter.voterId,
                    name: voter.name,
                    cnic: voter.cnic,
                    age: voter.age,
                    naSeat: voter.na,
                    province: voter.province,
                    paSeat: voter.provisionalP,
                    hasVotedMNA: voter.hasVotedMNA,
                    hasVotedMPA: voter.hasVotedMPA
                }
            }
        };
    }
    
    mockGetVoterProfile() {
        const currentUser = AuthService.getCurrentUser();
        if (!currentUser) throw new Error('Not authenticated');
        
        const voters = JSON.parse(localStorage.getItem('voters') || '[]');
        const voter = voters.find(v => v.cnic === currentUser.cnic);
        
        if (!voter) throw new Error('Voter not found');
        
        return {
            success: true,
            data: voter
        };
    }
    
    mockCheckVoteStatus() {
        const currentUser = AuthService.getCurrentUser();
        if (!currentUser) throw new Error('Not authenticated');
        
        const voters = JSON.parse(localStorage.getItem('voters') || '[]');
        const voter = voters.find(v => v.cnic === currentUser.cnic);
        
        return {
            success: true,
            data: {
                hasVotedMNA: voter?.hasVotedMNA || false,
                hasVotedMPA: voter?.hasVotedMPA || false
            }
        };
    }
    
    mockGetMNACandidates(naSeat) {
        const candidates = JSON.parse(localStorage.getItem('mnaCandidates') || '[]');
        const filtered = candidates.filter(c => c.constituency === parseInt(naSeat));
        
        return {
            success: true,
            data: filtered
        };
    }
    
    mockGetMPACandidates(province, paSeat) {
        const candidates = JSON.parse(localStorage.getItem('mpaCandidates') || '[]');
        const filtered = candidates.filter(c => 
            c.province === province && c.provisionalPP === parseInt(paSeat)
        );
        
        return {
            success: true,
            data: filtered
        };
    }
    
    mockCastVote(type, data) {
        const currentUser = AuthService.getCurrentUser();
        const voters = JSON.parse(localStorage.getItem('voters') || '[]');
        const voterIndex = voters.findIndex(v => v.cnic === currentUser.cnic);
        
        if (voterIndex === -1) throw new Error('Voter not found');
        
        const voteField = type === 'MNA' ? 'hasVotedMNA' : 'hasVotedMPA';
        
        if (voters[voterIndex][voteField]) {
            throw new Error(`Voter Already Voted (${type})`);
        }
        
        // Check voting time
        const votingStatus = isVotingOpen();
        if (!votingStatus.open) {
            throw new Error('Voting is CLOSED');
        }
        
        // Record vote
        voters[voterIndex][voteField] = true;
        localStorage.setItem('voters', JSON.stringify(voters));
        
        // Update vote counts
        const votesKey = type === 'MNA' ? 'mnaVotes' : 'mpaVotes';
        const votes = JSON.parse(localStorage.getItem(votesKey) || '{}');
        votes[data.candidateCnic] = (votes[data.candidateCnic] || 0) + 1;
        localStorage.setItem(votesKey, JSON.stringify(votes));
        
        // Add to ledger
        const ledger = JSON.parse(localStorage.getItem('ledger') || '[]');
        const block = {
            index: ledger.length,
            voterCnic: currentUser.cnic,
            candidateCnic: data.candidateCnic,
            voteType: type,
            timestamp: new Date().toISOString(),
            hash: this.generateHash(ledger.length, currentUser.cnic, data.candidateCnic),
            prevHash: ledger.length > 0 ? ledger[ledger.length - 1].hash : '0'
        };
        ledger.push(block);
        localStorage.setItem('ledger', JSON.stringify(ledger));
        
        return {
            success: true,
            message: `${type} vote cast successfully`,
            data: { blockIndex: block.index }
        };
    }
    
    mockLoginAdmin(data) {
        const credentials = CONFIG.ADMIN.credentials;
        
        if (credentials[data.username] === data.password) {
            const token = btoa(JSON.stringify({ username: data.username, type: 'admin' }));
            return {
                success: true,
                message: 'Admin login successful',
                data: { token, admin: { username: data.username } }
            };
        }
        
        throw new Error('Invalid admin credentials');
    }
    
    mockAddMNACandidate(data) {
        const candidates = JSON.parse(localStorage.getItem('mnaCandidates') || '[]');
        
        // Check if candidate already exists
        const exists = candidates.find(c => 
            c.cnic === data.cnic && c.constituency === data.constituency
        );
        
        if (exists) {
            throw new Error('Candidate Already Exists');
        }
        
        const candidate = {
            name: data.name,
            symbol: data.symbol,
            cnic: data.cnic,
            constituency: data.constituency,
            votes: 0
        };
        
        candidates.push(candidate);
        localStorage.setItem('mnaCandidates', JSON.stringify(candidates));
        
        // Initialize vote count
        const votes = JSON.parse(localStorage.getItem('mnaVotes') || '{}');
        votes[data.cnic] = 0;
        localStorage.setItem('mnaVotes', JSON.stringify(votes));
        
        return {
            success: true,
            message: 'MNA Candidate added successfully'
        };
    }
    
    mockAddMPACandidate(data) {
        const candidates = JSON.parse(localStorage.getItem('mpaCandidates') || '[]');
        
        const exists = candidates.find(c => 
            c.cnic === data.cnic && c.provisionalPP === data.provisionalPP
        );
        
        if (exists) {
            throw new Error('Candidate Already Exists');
        }
        
        const candidate = {
            name: data.name,
            symbol: data.symbol,
            cnic: data.cnic,
            province: data.province,
            provinceName: data.provinceName,
            provisionalPP: data.provisionalPP,
            votes: 0
        };
        
        candidates.push(candidate);
        localStorage.setItem('mpaCandidates', JSON.stringify(candidates));
        
        const votes = JSON.parse(localStorage.getItem('mpaVotes') || '{}');
        votes[data.cnic] = 0;
        localStorage.setItem('mpaVotes', JSON.stringify(votes));
        
        return {
            success: true,
            message: 'MPA Candidate added successfully'
        };
    }
    
    mockGetAllMNA() {
        const candidates = JSON.parse(localStorage.getItem('mnaCandidates') || '[]');
        const votes = JSON.parse(localStorage.getItem('mnaVotes') || '{}');
        
        const candidatesWithVotes = candidates.map(c => ({
            ...c,
            votes: votes[c.cnic] || 0
        }));
        
        return {
            success: true,
            data: candidatesWithVotes
        };
    }
    
    mockGetAllMPA() {
        const candidates = JSON.parse(localStorage.getItem('mpaCandidates') || '[]');
        const votes = JSON.parse(localStorage.getItem('mpaVotes') || '{}');
        
        const candidatesWithVotes = candidates.map(c => ({
            ...c,
            votes: votes[c.cnic] || 0
        }));
        
        return {
            success: true,
            data: candidatesWithVotes
        };
    }
    
    mockGetVotingStatus() {
        return {
            success: true,
            data: {
                electionDate: formatElectionDate(),
                votingStart: formatTime(CONFIG.ELECTION.votingHours.startHour),
                votingEnd: formatTime(CONFIG.ELECTION.votingHours.endHour),
                isOpen: isVotingOpen().open,
                isElectionDay: isElectionDay()
            }
        };
    }
    
    mockGetResults() {
        const mnaVotes = JSON.parse(localStorage.getItem('mnaVotes') || '{}');
        const mpaVotes = JSON.parse(localStorage.getItem('mpaVotes') || '{}');
        const mnaCandidates = JSON.parse(localStorage.getItem('mnaCandidates') || '[]');
        const mpaCandidates = JSON.parse(localStorage.getItem('mpaCandidates') || '[]');
        
        return {
            success: true,
            data: {
                mna: mnaCandidates.map(c => ({ ...c, votes: mnaVotes[c.cnic] || 0 })),
                mpa: mpaCandidates.map(c => ({ ...c, votes: mpaVotes[c.cnic] || 0 }))
            }
        };
    }
    
    mockGetWinners() {
        const results = this.mockGetResults().data;
        
        // Find MNA winners per constituency
        const mnaWinners = [];
        const constituencies = [...new Set(results.mna.map(c => c.constituency))];
        
        constituencies.forEach(constname => {
            const candidates = results.mna.filter(c => c.constituency === constname);
            const winner = candidates.reduce((max, c) => c.votes > max.votes ? c : max, candidates[0]);
            if (winner) mnaWinners.push(winner);
        });
        
        // Find MPA winners per province/seat
        const mpaWinners = [];
        const provinces = [...new Set(results.mpa.map(c => c.province))];
        
        provinces.forEach(prov => {
            const provinceCandiates = results.mpa.filter(c => c.province === prov);
            const seats = [...new Set(provinceCandiates.map(c => c.provisionalPP))];
            
            seats.forEach(seat => {
                const candidates = provinceCandiates.filter(c => c.provisionalPP === seat);
                const winner = candidates.reduce((max, c) => c.votes > max.votes ? c : max, candidates[0]);
                if (winner) mpaWinners.push(winner);
            });
        });
        
        return {
            success: true,
            data: {
                mnaWinners,
                mpaWinners
            }
        };
    }
    
    mockVerifyLedger() {
        const ledger = JSON.parse(localStorage.getItem('ledger') || '[]');
        
        if (ledger.length === 0) {
            return {
                success: true,
                data: {
                    isValid: true,
                    message: 'No Ledger Recorded'
                }
            };
        }
        
        // Verify chain integrity
        for (let i = 1; i < ledger.length; i++) {
            const current = ledger[i];
            const previous = ledger[i - 1];
            
            // Check if previous hash matches
            if (current.prevHash !== previous.hash) {
                return {
                    success: true,
                    data: {
                        isValid: false,
                        message: `Hash Mismatch!  Blockchain link broken between Block ${previous.index} and Block ${current.index}`
                    }
                };
            }
            
            // Verify current hash
            const calculatedHash = this.generateHash(current.index, current.voterCnic, current.candidateCnic);
            if (current.hash !== calculatedHash) {
                return {
                    success: true,
                    data: {
                        isValid: false,
                        message: `Hash Mismatch!  Tampering Detected in Block ${current.index}`
                    }
                };
            }
        }
        
        return {
            success: true,
            data: {
                isValid: true,
                message: 'BLOCKCHAIN VERIFIED SUCCESSFULLY'
            }
        };
    }
    
    mockViewLedger() {
        const ledger = JSON.parse(localStorage.getItem('ledger') || '[]');
        
        return {
            success: true,
            data: ledger
        };
    }
    
    // Helper functions
    
    simpleHash(str) {
        let hash = 0;
        for (let i = 0; i < str.length; i++) {
            const char = str.charCodeAt(i);
            hash = ((hash << 5) - hash) + char;
            hash = hash & hash;
        }
        return hash;
    }
    
    generateHash(index, voterCnic, candidateCnic) {
        const data = `${index}-${voterCnic}-${candidateCnic}-${Date.now()}`;
        return Math.abs(this.simpleHash(data)).toString(16);
    }
}

// Create singleton instance
const API = new APIService();