// ==================== CONFIGURATION FOR C++ BACKEND CONNECTION ====================

const CONFIG = {
    // API Configuration
    API: {
        BASE_URL: 'http://localhost:8080/api',
        ENDPOINTS: {
            // Voter endpoints
            REGISTER_VOTER: '/voter/register',
            LOGIN_VOTER: '/voter/login',
            GET_VOTER_PROFILE: '/voter/profile',
            VOTER_MENU: '/voter/menu',
            
            // Voting endpoints
            CAST_VOTE_MNA: '/vote/mna',
            CAST_VOTE_MPA: '/vote/mpa',
            GET_MNA_CANDIDATES: '/candidates/mna',
            GET_MPA_CANDIDATES: '/candidates/mpa',
            CHECK_VOTE_STATUS: '/voter/vote-status',
            
            // Admin endpoints
            LOGIN_ADMIN: '/admin/login',
            ADD_MNA_CANDIDATE: '/admin/candidate/mna',
            ADD_MPA_CANDIDATE: '/admin/candidate/mpa',
            GET_ALL_MNA: '/admin/candidates/mna',
            GET_ALL_MPA: '/admin/candidates/mpa',
            GET_ADMIN_STATS: '/admin/stats',
            TALLY_RESULTS: '/admin/tally',
            VERIFY_LEDGER: '/admin/ledger/verify',
            VIEW_LEDGER: '/admin/ledger/view',
            
            // Public endpoints
            GET_RESULTS: '/results',
            GET_VOTING_STATUS: '/voting/status',
            GET_ALL_VOTES: '/votes/all',
            GET_WINNERS: '/winners',
            
            // Constituency endpoints
            GET_NA_NAMES: '/constituencies/na-names',
            GET_PA_NAMES: '/constituencies/pa-names'
        },
        TIMEOUT: 10000,
        USE_MOCK: false
    },
    
    // Election Configuration
    ELECTION: {
        year: 2025,
        month: 12,
        day: 7,
        votingHours: {
            startHour: 5,
            endHour: 17
        }
    },
    
    // Constituency Data
    CONSTITUENCIES: {
        Punjab: { naStart: 49, naEnd: 189, paSeats: 297, code: 'PP' },
        Sindh: { naStart: 190, naEnd: 250, paSeats: 130, code: 'PS' },
        KPK: { naStart: 1, naEnd: 45, paSeats: 115, code: 'PK' },
        Balochistan: { naStart: 251, naEnd: 266, paSeats: 51, code: 'PB' },
        Islamabad: { naStart: 46, naEnd: 48, paSeats: 0, code: 'I' }
    },
    
    // Validation Rules
    VALIDATION: {
        CNIC_LENGTH: 13,
        MIN_AGE: 18,
        MIN_PASSWORD_LENGTH: 1,
        NA_MIN: 1,
        NA_MAX: 266
    },
    
    // UI Configuration
    UI: {
        TIME_FORMAT: { hour: '2-digit', minute: '2-digit', second: '2-digit', hour12: true }
    }
};

// ==================== CONSTITUENCY MAPPING ====================
function generateConstituencyMapping() {
    const mapping = {};
    
    // KPK: NA 1-45 → PK 1-115
    let pkCounter = 1;
    for (let na = 1; na <= 45; na++) {
        const paSeats = [];
        if (pkCounter <= 115) paSeats.push(pkCounter++);
        if (pkCounter <= 115) paSeats.push(pkCounter++);
        if (na % 2 === 0 && pkCounter <= 115) paSeats.push(pkCounter++);
        mapping[na] = { pa: paSeats, province: 'KPK', code: 'PK' };
    }
    
    // Islamabad: NA 46-48 (No PA)
    for (let na = 46; na <= 48; na++) {
        mapping[na] = { pa: [], province: 'Islamabad', code: 'I' };
    }
    
    // Punjab: NA 49-189 → PP 1-297
    let ppCounter = 1;
    for (let na = 49; na <= 189; na++) {
        const paSeats = [];
        if (ppCounter <= 297) paSeats.push(ppCounter++);
        if (ppCounter <= 297) paSeats.push(ppCounter++);
        mapping[na] = { pa: paSeats, province: 'Punjab', code: 'PP' };
    }
    
    // Sindh: NA 190-250 → PS 1-130
    let psCounter = 1;
    for (let na = 190; na <= 250; na++) {
        const paSeats = [];
        if (psCounter <= 130) paSeats.push(psCounter++);
        if (psCounter <= 130) paSeats.push(psCounter++);
        mapping[na] = { pa: paSeats, province: 'Sindh', code: 'PS' };
    }
    
    // Balochistan: NA 251-266 → PB 1-51
    let pbCounter = 1;
    for (let na = 251; na <= 266; na++) {
        const paSeats = [];
        if (pbCounter <= 51) paSeats.push(pbCounter++);
        if (pbCounter <= 51) paSeats.push(pbCounter++);
        if (pbCounter <= 51) paSeats.push(pbCounter++);
        mapping[na] = { pa: paSeats, province: 'Balochistan', code: 'PB' };
    }
    
    return mapping;
}

const CONSTITUENCY_MAPPING = generateConstituencyMapping();

function getPASeatsForNA(naSeat) {
    return CONSTITUENCY_MAPPING[naSeat] || null;
}

// ==================== UTILITY FUNCTIONS ====================

function getProvinceFromNA(naSeat) {
    const seat = parseInt(naSeat);
    if (seat >= 1 && seat <= 45) return { name: 'KPK', code: 'PK', enum: 2 };
    if (seat >= 46 && seat <= 48) return { name: 'Islamabad', code: 'I', enum: 4 };
    if (seat >= 49 && seat <= 189) return { name: 'Punjab', code: 'PP', enum: 0 };
    if (seat >= 190 && seat <= 250) return { name: 'Sindh', code: 'PS', enum: 1 };
    if (seat >= 251 && seat <= 266) return { name: 'Balochistan', code: 'PB', enum: 3 };
    return null;
}

function isElectionDay() {
    const now = new Date();
    const electionDate = new Date(CONFIG.ELECTION.year, CONFIG.ELECTION.month - 1, CONFIG.ELECTION.day);
    return now.toDateString() === electionDate.toDateString();
}

function isVotingOpen() {
    if (! isElectionDay()) return { open: false, reason: 'not_election_day' };
    const now = new Date();
    const currentHour = now.getHours();
    if (currentHour < CONFIG.ELECTION.votingHours.startHour) return { open: false, reason: 'too_early' };
    if (currentHour >= CONFIG.ELECTION.votingHours.endHour) return { open: false, reason: 'too_late' };
    return { open: true, reason: 'open' };
}

function getTimeUntilElection() {
    const now = new Date();
    const electionDate = new Date(CONFIG.ELECTION.year, CONFIG.ELECTION.month - 1, CONFIG.ELECTION.day, CONFIG.ELECTION.votingHours.startHour, 0, 0);
    const diff = electionDate - now;
    if (diff < 0) return { isPast: true };
    return {
        isPast: false,
        days: Math.floor(diff / (1000 * 60 * 60 * 24)),
        hours: Math.floor((diff % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60)),
        minutes: Math.floor((diff % (1000 * 60 * 60)) / (1000 * 60)),
        seconds: Math.floor((diff % (1000 * 60)) / 1000)
    };
}

function getTimeRemainingInVoting() {
    const now = new Date();
    const endTime = new Date();
    endTime.setHours(CONFIG.ELECTION.votingHours.endHour, 0, 0, 0);
    const diff = endTime - now;
    if (diff < 0) return null;
    return {
        hours: Math.floor(diff / (1000 * 60 * 60)),
        minutes: Math.floor((diff % (1000 * 60 * 60)) / (1000 * 60)),
        seconds: Math.floor((diff % (1000 * 60)) / 1000)
    };
}

function validateCNIC(cnic) {
    const cleaned = cnic.replace(/[\s-]/g, '');
    if (cleaned.length !== CONFIG.VALIDATION.CNIC_LENGTH) {
        return { valid: false, message: 'CNIC must be exactly 13 digits' };
    }
    if (!/^\d{13}$/.test(cleaned)) {
        return { valid: false, message: 'CNIC must contain only digits' };
    }
    return { valid: true, cleaned };
}

function validateAge(age) {
    const ageNum = parseInt(age);
    if (isNaN(ageNum) || ageNum < CONFIG.VALIDATION.MIN_AGE) {
        return { valid: false, message: `You must be at least ${CONFIG.VALIDATION.MIN_AGE} years old` };
    }
    if (ageNum > 120) {
        return { valid: false, message: 'Please enter a valid age' };
    }
    return { valid: true };
}

function validateNASeat(seat) {
    const seatNum = parseInt(seat);
    if (isNaN(seatNum) || seatNum < 1 || seatNum > 266) {
        return { valid: false, message: 'NA seat must be between 1 and 266' };
    }
    return { valid: true };
}

function validatePASeat(province, seat) {
    const seatNum = parseInt(seat);
    switch(province) {
        case 'Punjab': return seatNum >= 1 && seatNum <= 297;
        case 'Sindh': return seatNum >= 1 && seatNum <= 130;
        case 'KPK': return seatNum >= 1 && seatNum <= 115;
        case 'Balochistan': return seatNum >= 1 && seatNum <= 51;
        case 'Islamabad': return true;
        default: return false;
    }
}

function validatePassword(password) {
    if (password.length < CONFIG.VALIDATION.MIN_PASSWORD_LENGTH) {
        return { valid: false, message: 'Password is required' };
    }
    return { valid: true };
}

function formatTime(hour, minute = 0) {
    const period = hour >= 12 ? 'PM' : 'AM';
    const displayHour = hour > 12 ? hour - 12 : (hour === 0 ? 12 : hour);
    const displayMinute = minute.toString().padStart(2, '0');
    return `${displayHour}:${displayMinute} ${period}`;
}

console.log('🗺️ Pakistan EMS Configuration Loaded');
console.log('📡 API Base URL:', CONFIG.API.BASE_URL);
console.log('🗳️ Election Date:', `${CONFIG.ELECTION.year}-${CONFIG.ELECTION.month}-${CONFIG.ELECTION.day}`);
console.log('⏰ Voting Hours:', `${CONFIG.ELECTION.votingHours.startHour}:00 - ${CONFIG.ELECTION.votingHours.endHour}:00`);