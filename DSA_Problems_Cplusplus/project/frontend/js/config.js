const CONFIG = {
    API: {
        BASE_URL: 'http://localhost:8080/api',
        ENDPOINTS: {
            REGISTER_VOTER: '/voter/register',
            LOGIN_VOTER: '/voter/login',
            GET_VOTER_PROFILE: '/voter/profile',
            VOTER_MENU: '/voter/menu',
            CAST_VOTE_MNA: '/vote/mna',
            CAST_VOTE_MPA: '/vote/mpa',
            GET_MNA_CANDIDATES: '/candidates/mna',
            GET_MPA_CANDIDATES: '/candidates/mpa',
            CHECK_VOTE_STATUS: '/voter/vote-status',
            LOGIN_ADMIN: '/admin/login',
            ADD_MNA_CANDIDATE: '/admin/candidate/mna',
            ADD_MPA_CANDIDATE: '/admin/candidate/mpa',
            GET_ALL_MNA: '/admin/candidates/mna',
            GET_ALL_MPA: '/admin/candidates/mpa',
            GET_ADMIN_STATS: '/admin/stats',
            TALLY_RESULTS: '/admin/tally',
            VERIFY_LEDGER: '/admin/ledger/verify',
            VIEW_LEDGER: '/admin/ledger/view',
            GET_RESULTS: '/results',
            GET_VOTING_STATUS: '/voting/status',
            GET_ALL_VOTES: '/votes/all',
            GET_WINNERS: '/winners',
            GET_NA_NAMES: '/constituencies/na-names',
            GET_PA_NAMES: '/constituencies/pa-names'
        },
        TIMEOUT: 10000,
        USE_MOCK: false
    },
    
    ELECTION: {
        year: 2025,
        month: 12,
        day: 7,
        votingHours: {
            startHour: 5,
            endHour: 20
        }
    },
    
    CONSTITUENCIES: {
        Punjab: { naStart: 49, naEnd: 189, paSeats: 297, code: 'PP' },
        Sindh: { naStart: 190, naEnd: 250, paSeats: 130, code: 'PS' },
        KPK: { naStart: 1, naEnd: 45, paSeats: 115, code: 'PK' },
        Balochistan: { naStart: 251, naEnd: 266, paSeats: 51, code: 'PB' },
        Islamabad: { naStart: 46, naEnd: 48, paSeats: 0, code: 'I' }
    },
    
    VALIDATION: {
        CNIC_LENGTH: 13,
        MIN_AGE: 18,
        MIN_PASSWORD_LENGTH: 1,
        NA_MIN: 1,
        NA_MAX: 266
    },
    
    UI: {
        TIME_FORMAT: { hour: '2-digit', minute: '2-digit', second: '2-digit', hour12: true }
    }
};

async function loadVotingTimeConfig() {
    try {
        const response = await fetch(`${CONFIG.API.BASE_URL}/voting/status`);
        const data = await response.json();
        if (data.success) {
            CONFIG.ELECTION.year = data.data.year;
            CONFIG.ELECTION.month = data.data.month;
            CONFIG.ELECTION.day = data.data.day;
            CONFIG.ELECTION.votingHours.startHour = data.data.startHour;
            CONFIG.ELECTION.votingHours.endHour = data.data.endHour;
            console.log('✅ Voting time loaded from backend');
        }
    } catch (error) {
        console.error('❌ Error loading voting time:', error);
    }
}

loadVotingTimeConfig();

const NA_TO_PA_MAPPING = {
    1: [1, 2], 2: [3, 4, 5], 3: [6, 7, 8], 4: [9, 10], 5: [11, 12, 13],
    6: [14, 15, 16], 7: [17, 18], 8: [19, 20, 21, 22], 9: [23, 24],
    10: [25, 26, 27], 11: [28, 29, 30], 12: [31, 32, 33], 13: [34, 35],
    14: [36, 37], 15: [38, 39, 40, 41], 16: [42, 43], 17: [44, 45],
    18: [46, 47, 48], 19: [49, 50, 51], 20: [52, 53], 21: [54, 55, 56],
    22: [57, 58], 23: [59, 60, 61], 24: [62, 63, 64], 25: [65, 66],
    26: [67, 68], 27: [69, 70, 71], 28: [72, 73, 74], 29: [75, 76, 77],
    30: [78, 79], 31: [80, 81], 32: [82, 83, 84], 33: [85, 86, 87],
    34: [88, 89], 35: [90, 91, 92], 36: [93, 94], 37: [95, 96],
    38: [97, 98], 39: [99, 100, 101], 40: [102, 103, 104],
    41: [105, 106, 107], 42: [109, 110], 43: [108, 111], 44: [112, 113],
    45: [114, 115], 46: [], 47: [], 48: [],
    49: [1, 2], 50: [3, 4, 5], 51: [6], 52: [7, 8, 9], 53: [10, 11],
    54: [12, 13], 55: [14, 15], 56: [16, 17], 57: [18, 19], 58: [20, 21],
    59: [22, 23], 60: [24, 25], 61: [26], 62: [27, 28], 63: [29, 30],
    64: [31, 32], 65: [33, 34], 66: [35, 36], 67: [37, 38, 39],
    68: [40, 41], 69: [42, 43], 70: [44, 45], 71: [46, 47], 72: [48, 49],
    73: [50, 51], 74: [52, 53], 75: [54, 55], 76: [56, 57, 58],
    77: [59, 60], 78: [61, 62], 79: [63, 64], 80: [65, 66, 67],
    81: [68, 69, 70], 82: [71, 72], 83: [73, 74], 84: [75, 76],
    85: [77, 78], 86: [79, 80], 87: [81, 82], 88: [83, 84], 89: [85, 86],
    90: [87, 88], 91: [89, 90], 92: [91, 92], 93: [93, 94], 94: [95, 96],
    95: [97, 98], 96: [99, 100], 97: [101, 102], 98: [103, 104],
    99: [105, 106], 100: [107, 108], 101: [109, 110, 111],
    102: [112, 113], 103: [114, 115], 104: [116, 117, 118],
    105: [119, 120], 106: [121, 122], 107: [123, 124], 108: [125, 126],
    109: [127, 128], 110: [129, 130, 131], 111: [132, 133], 112: [134, 135],
    113: [136, 137], 114: [138, 139], 115: [140, 141], 116: [142, 143, 144],
    117: [145, 146], 118: [147, 148], 119: [149, 150], 120: [151, 154],
    121: [152, 153], 122: [155, 156, 157], 123: [158, 159], 124: [160, 161],
    125: [162, 163], 126: [164, 165], 127: [166, 167, 168], 128: [169, 170],
    129: [171, 172], 130: [173, 174], 131: [175, 176], 132: [177, 178],
    133: [179, 180], 134: [181, 182, 183, 184], 135: [185, 186],
    136: [187, 188], 137: [189, 190], 138: [191, 192], 139: [193, 194],
    140: [195, 196, 197], 141: [198, 199], 142: [200, 201],
    143: [202, 203, 204], 144: [205, 206], 145: [207, 208], 146: [209, 210],
    147: [211, 212], 148: [213, 214], 149: [215, 216], 150: [217, 218],
    151: [219, 220], 152: [221, 222], 153: [223, 224, 228],
    154: [225, 226], 155: [227, 234], 156: [229, 230], 157: [231, 232],
    158: [233, 234], 159: [235, 236], 160: [237, 238], 161: [239, 240],
    162: [241, 242], 163: [243, 244], 164: [245, 246], 165: [247, 248],
    166: [249, 250], 167: [251, 252], 168: [253, 254], 169: [255, 256],
    170: [257, 258], 171: [259, 260], 172: [261, 262], 173: [263, 264],
    174: [265, 266, 267], 175: [268, 269], 176: [270, 271],
    177: [272, 273], 178: [274, 275], 179: [276, 277, 278],
    180: [279, 280, 281], 181: [282, 283], 182: [284, 285],
    183: [286, 287], 184: [288, 289], 185: [290, 291], 186: [292, 293],
    187: [294, 295], 188: [296], 189: [297],
    190: [1, 2, 3], 191: [4, 5], 192: [6, 7, 8, 9], 193: [10, 11, 12],
    194: [13, 14], 195: [15, 16, 17], 196: [18, 19], 197: [20, 21],
    198: [22, 23], 199: [24, 25], 200: [26, 27], 201: [28, 29, 30],
    202: [31, 32, 33], 203: [34, 35], 204: [36, 37], 205: [38, 39],
    206: [40, 41], 207: [42, 43], 208: [44, 45], 209: [46, 47, 48],
    210: [49, 50, 51], 211: [52, 53], 212: [54, 55], 213: [56, 57],
    214: [58, 59], 215: [60, 61], 216: [62, 63], 217: [64, 65],
    218: [66, 67], 219: [68, 69], 220: [70, 71, 72], 221: [73, 74],
    222: [75, 76], 223: [77, 78, 79], 224: [80, 81], 225: [82, 83],
    226: [84, 85, 86], 227: [87, 88, 89], 228: [90, 91], 229: [92, 93],
    230: [94, 95], 231: [96, 97], 232: [98, 99], 233: [100, 101],
    234: [102, 103, 104], 235: [105, 106], 236: [107, 108],
    237: [109, 110], 238: [111, 112], 239: [113, 114], 240: [115, 116],
    241: [117, 118], 242: [119, 120], 243: [121, 122], 244: [123, 124],
    245: [125, 126], 246: [127, 128], 247: [129, 130], 248: [131, 132],
    249: [133, 134], 250: [135, 136],
    251: [1, 2, 3], 252: [4, 5, 6, 7], 253: [8, 9, 10], 254: [11, 12, 13],
    255: [14, 15, 16], 256: [17, 18, 19], 257: [20, 21, 22],
    258: [23, 24, 25], 259: [26, 27, 28], 260: [29, 30, 31, 32, 33],
    261: [34, 35, 36], 262: [37, 38, 39], 263: [40, 41, 42],
    264: [43, 44, 45], 265: [46, 47, 48, 49], 266: [50, 51]
};

const CONSTITUENCY_MAPPING = {};
for (const [na, paSeats] of Object.entries(NA_TO_PA_MAPPING)) {
    const naNum = parseInt(na);
    let province = '';
    let code = '';
    
    if (naNum >= 1 && naNum <= 45) {
        province = 'KPK';
        code = 'PK';
    } else if (naNum >= 46 && naNum <= 48) {
        province = 'Islamabad';
        code = 'I';
    } else if (naNum >= 49 && naNum <= 189) {
        province = 'Punjab';
        code = 'PP';
    } else if (naNum >= 190 && naNum <= 250) {
        province = 'Sindh';
        code = 'PS';
    } else if (naNum >= 251 && naNum <= 266) {
        province = 'Balochistan';
        code = 'PB';
    }
    
    CONSTITUENCY_MAPPING[naNum] = {
        pa: paSeats || [],
        province: province,
        code: code
    };
}

function getPASeatsForNA(naSeat) {
    return CONSTITUENCY_MAPPING[naSeat] || null;
}

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
    if (!isElectionDay()) return { open: false, reason: 'not_election_day' };
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
console.log('⏳ Loading voting configuration from backend...');