// ==================== REGISTER.JS - Voter Registration ====================

let currentStep = 1;
const totalSteps = 3;
let naAreaNames = {};
let paAreaNames = {};

// ==================== INITIALIZE REGISTRATION ====================
async function initializeRegistration() {
    console.log('📝 Registration page initialized');
    await loadConstituencyNames();
    populateNASeats();
    setupFormValidation();
    setupFormSubmission();
    updateProgressIndicator();
}

// ==================== LOAD CONSTITUENCY NAMES FROM BACKEND ====================
async function loadConstituencyNames() {
    try {
        console.log('📡 Fetching constituency names from backend...');
        const naResponse = await fetch(`${CONFIG.API.BASE_URL}/constituencies/na-names`);
        
        if (naResponse.ok) {
            const naData = await naResponse.json();
            if (naData.success) {
                naAreaNames = naData.data;
                console.log(`✅ Loaded ${Object.keys(naAreaNames).length} NA constituencies`);
            }
        } else {
            console.warn('⚠️ Backend returned error for NA names');
        }
    } catch (error) {
        console.error('❌ Error loading constituency names:', error);
        naAreaNames = {};
    }
}

// ==================== POPULATE NA SEATS WITH NAMES ====================
function populateNASeats() {
    const naSelect = document.getElementById('na-seat');
    if (!naSelect) return;
    
    const constituencies = {
        'KPK': { start: 1, end: 45, label: 'Khyber Pakhtunkhwa (NA 1-45)' },
        'Islamabad': { start: 46, end: 48, label: 'Islamabad Capital Territory (NA 46-48)' },
        'Punjab': { start: 49, end: 189, label: 'Punjab (NA 49-189)' },
        'Sindh': { start: 190, end: 250, label: 'Sindh (NA 190-250)' },
        'Balochistan': { start: 251, end: 266, label: 'Balochistan (NA 251-266)' }
    };
    
    for (const [province, range] of Object.entries(constituencies)) {
        const optgroup = document.createElement('optgroup');
        optgroup.label = range.label;
        
        for (let i = range.start; i <= range.end; i++) {
            const option = document.createElement('option');
            option.value = i;
            const areaName = naAreaNames[i] || '';
            
            // Better formatting: "NA-117 | Lahore-I" (shorter, cleaner)
            option.textContent = areaName ?  `NA-${i} | ${areaName}` : `NA-${i}`;
            option.setAttribute('data-area-name', areaName);
            
            optgroup.appendChild(option);
        }
        
        naSelect.appendChild(optgroup);
    }
    
    naSelect.addEventListener('change', handleNASeatChange);
    console.log('✅ NA seat dropdown populated');
}

// ==================== HANDLE NA SEAT CHANGE ====================
async function handleNASeatChange(e) {
    const naSeat = parseInt(e.target.value);
    if (! naSeat) return;
    
    const selectedOption = e.target.options[e.target.selectedIndex];
    const areaName = selectedOption.getAttribute('data-area-name') || naAreaNames[naSeat] || 'Unknown Area';
    
    console.log(`🗳️ NA seat selected: ${naSeat} - ${areaName}`);
    
    const provinceInfo = getProvinceFromNA(naSeat);
    if (!provinceInfo) {
        showAlert('Invalid NA seat selected', 'error');
        return;
    }
    
    console.log(`📍 Province: ${provinceInfo.name} (${provinceInfo.code})`);
    
    const provinceInput = document.getElementById('province');
    if (provinceInput) {
        provinceInput.value = `${provinceInfo.name} (${provinceInfo.code})`;
    }
    
    showConstituencyInfo(naSeat, areaName, provinceInfo);
    await loadPANamesForProvince(provinceInfo.name);
    populatePASeatsWithNames(naSeat, provinceInfo.name);
    
    e.target.classList.add('valid');
    e.target.classList.remove('invalid');
}

// ==================== SHOW CONSTITUENCY INFO ====================
function showConstituencyInfo(naSeat, areaName, provinceInfo) {
    let infoDiv = document.getElementById('constituency-info');
    
    if (!infoDiv) {
        infoDiv = document.createElement('div');
        infoDiv.id = 'constituency-info';
        infoDiv.style.cssText = `
            margin-top: 15px;
            padding: 15px;
            background: linear-gradient(135deg, rgba(1, 65, 28, 0.1), rgba(1, 65, 28, 0.05));
            border-left: 4px solid var(--pakistan-green);
            border-radius: 8px;
            animation: slideIn 0.3s ease;
        `;
        
        const naSelectGroup = document.getElementById('na-seat').parentElement;
        naSelectGroup.appendChild(infoDiv);
    }
    
    infoDiv.innerHTML = `
        <div style="display: flex; align-items: center; gap: 10px; color: var(--pakistan-green); font-weight: 600;">
            <i class="fas fa-map-marker-alt" style="font-size: 1.2rem;"></i>
            <div>
                <div style="font-size: 1.1rem;">✓ Selected: NA-${naSeat}</div>
                <div style="font-size: 0.95rem; color: #555; font-weight: 500; margin-top: 3px;">
                    ${areaName}
                </div>
                <div style="font-size: 0.9rem; color: #777; margin-top: 3px;">
                    Province: ${provinceInfo.name}
                </div>
            </div>
        </div>
    `;
}

// ==================== LOAD PA NAMES FOR PROVINCE ====================
async function loadPANamesForProvince(province) {
    try {
        console.log(`📡 Fetching ${province} PA constituency names...`);
        const response = await fetch(`${CONFIG.API.BASE_URL}/constituencies/pa-names? province=${province}`);
        
        if (response.ok) {
            const data = await response.json();
            if (data.success) {
                paAreaNames = data.data;
                console.log(`✅ Loaded ${Object.keys(paAreaNames).length} ${province} PA constituencies`);
            }
        } else {
            console.warn(`⚠️ Backend returned error for ${province} PA names`);
            paAreaNames = {};
        }
    } catch (error) {
        console.error('❌ Error loading PA names:', error);
        paAreaNames = {};
    }
}

// ==================== POPULATE PA SEATS WITH NAMES ====================
function populatePASeatsWithNames(naSeat, provinceName) {
    const paSelect = document.getElementById('pa-seat');
    const paGroup = document.getElementById('pa-seat-group');
    
    if (!paSelect || !paGroup) return;
    
    paSelect.innerHTML = '';
    const mapping = CONSTITUENCY_MAPPING[naSeat];
    
    if (!mapping) {
        paSelect.innerHTML = '<option value="">Invalid NA seat</option>';
        paSelect.disabled = true;
        return;
    }
    
    if (mapping.province === 'Islamabad' || mapping.pa.length === 0) {
        paSelect.innerHTML = '<option value="0" selected>Not Applicable (Islamabad)</option>';
        paSelect.disabled = true;
        paSelect.value = "0";
        paGroup.style.display = 'block';
        console.log('ℹ️ Islamabad - No PA constituency required');
        return;
    }
    
    paSelect.disabled = false;
    paGroup.style.display = 'block';
    
    const defaultOption = document.createElement('option');
    defaultOption.value = '';
    defaultOption.textContent = `Select ${mapping.code} Constituency`;
    paSelect.appendChild(defaultOption);
    
    mapping.pa.forEach(paSeat => {
        const option = document.createElement('option');
        option.value = paSeat;
        const areaName = paAreaNames[paSeat] || '';
        
        // Better formatting: "PP-145 | Lahore Cantonment"
        option.textContent = areaName ? `${mapping.code}-${paSeat} | ${areaName}` : `${mapping.code}-${paSeat}`;
        option.setAttribute('data-area-name', areaName);
        
        paSelect.appendChild(option);
    });
    
    paSelect.addEventListener('change', handlePASeatChange);
    
    let helperText = paGroup.querySelector('.constituency-hint');
    if (!helperText) {
        helperText = document.createElement('small');
        helperText.className = 'form-hint constituency-hint';
        paSelect.parentElement.appendChild(helperText);
    }
    
    const paList = mapping.pa.map(pa => `${mapping.code}-${pa}`).join(', ');
    helperText.textContent = `NA-${naSeat} covers: ${paList}`;
    helperText.style.color = 'var(--pakistan-green-lighter)';
    helperText.style.fontWeight = '600';
    
    console.log(`✅ PA dropdown populated with ${mapping.pa.length} options`);
}

// ==================== HANDLE PA SEAT CHANGE ====================
function handlePASeatChange(e) {
    const paSeat = parseInt(e.target.value);
    if (!paSeat) return;
    
    const selectedOption = e.target.options[e.target.selectedIndex];
    const areaName = selectedOption.getAttribute('data-area-name') || paAreaNames[paSeat] || 'Unknown Area';
    const provinceCode = selectedOption.textContent.split('|')[0].trim().split('-')[0];
    
    console.log(`🏛️ PA seat selected: ${provinceCode}-${paSeat} - ${areaName}`);
}

// ==================== STEP NAVIGATION ====================
window.nextStep = function(step) {
    if (! validateCurrentStep()) {
        showAlert('Please fill all required fields correctly', 'error');
        return;
    }
    document.getElementById(`step-${currentStep}`).classList.remove('active');
    currentStep = step;
    document.getElementById(`step-${currentStep}`).classList.add('active');
    updateProgressIndicator();
    window.scrollTo({ top: 0, behavior: 'smooth' });
};

window.prevStep = function(step) {
    document.getElementById(`step-${currentStep}`).classList.remove('active');
    currentStep = step;
    document.getElementById(`step-${currentStep}`).classList.add('active');
    updateProgressIndicator();
    window.scrollTo({ top: 0, behavior: 'smooth' });
};

// ==================== UPDATE PROGRESS INDICATOR ====================
function updateProgressIndicator() {
    document.querySelectorAll('.progress-step').forEach((step, index) => {
        const stepNum = index + 1;
        if (stepNum <= currentStep) {
            step.classList.add('active');
        } else {
            step.classList.remove('active');
        }
    });
}

// ====================  VALIDATE CURRENT STEP ====================
function validateCurrentStep() {
    const currentStepEl = document.getElementById(`step-${currentStep}`);
    const inputs = currentStepEl.querySelectorAll('input[required], select[required]');
    let isValid = true;
    
    inputs.forEach(input => {
        if (!validateField(input)) {
            isValid = false;
        }
    });
    
    return isValid;
}

// ==================== VALIDATE FIELD ====================
function validateField(field) {
    const value = field.value.trim();
    const fieldName = field.name;
    let isValid = true;
    let errorMessage = '';
    
    if (! value && field.hasAttribute('required')) {
        isValid = false;
        errorMessage = 'This field is required';
    }
    
    if (isValid && value) {
        switch (fieldName) {
            case 'name':
                if (value.length < 3) {
                    isValid = false;
                    errorMessage = 'Name must be at least 3 characters';
                } else if (!/^[a-zA-Z\s]+$/.test(value)) {
                    isValid = false;
                    errorMessage = 'Name can only contain letters and spaces';
                }
                break;
            case 'cnic':
                const cnicValidation = validateCNIC(value);
                if (!cnicValidation.valid) {
                    isValid = false;
                    errorMessage = cnicValidation.message;
                }
                break;
            case 'age':
                const ageValidation = validateAge(value);
                if (!ageValidation.valid) {
                    isValid = false;
                    errorMessage = ageValidation.message;
                }
                break;
            case 'na-seat':
                const naSeatValidation = validateNASeat(value);
                if (! naSeatValidation.valid) {
                    isValid = false;
                    errorMessage = naSeatValidation.message;
                }
                break;
            case 'pa-seat':
                const naSeat = parseInt(document.getElementById('na-seat').value);
                const mapping = CONSTITUENCY_MAPPING[naSeat];
                if (mapping && mapping.province !== 'Islamabad' && ! value) {
                    isValid = false;
                    errorMessage = 'Please select a PA constituency';
                }
                break;
            case 'password':
                const passwordValidation = validatePassword(value);
                if (!passwordValidation.valid) {
                    isValid = false;
                    errorMessage = passwordValidation.message;
                }
                break;
            case 'confirm-password':
                const password = document.getElementById('password').value;
                if (value !== password) {
                    isValid = false;
                    errorMessage = 'Passwords do not match';
                }
                break;
        }
    }
    
    if (isValid) {
        field.classList.add('valid');
        field.classList.remove('invalid');
        hideFieldError(field);
    } else {
        field.classList.add('invalid');
        field.classList.remove('valid');
        showFieldError(field, errorMessage);
    }
    
    return isValid;
}

// ==================== SHOW/HIDE FIELD ERROR ====================
function showFieldError(field, message) {
    let errorEl = field.parentElement.querySelector('.error-message');
    if (!errorEl) {
        errorEl = document.createElement('span');
        errorEl.className = 'error-message';
        field.parentElement.appendChild(errorEl);
    }
    errorEl.textContent = message;
    errorEl.classList.add('show');
}

function hideFieldError(field) {
    const errorEl = field.parentElement.querySelector('.error-message');
    if (errorEl) {
        errorEl.classList.remove('show');
    }
}

// ==================== SETUP FORM VALIDATION ====================
function setupFormValidation() {
    const form = document.getElementById('registration-form');
    if (!form) return;
    
    const inputs = form.querySelectorAll('input, select');
    inputs.forEach(input => {
        input.addEventListener('blur', () => validateField(input));
        input.addEventListener('input', () => {
            if (input.classList.contains('invalid')) {
                validateField(input);
            }
        });
    });
    
    const cnicInput = document.getElementById('cnic');
    if (cnicInput) {
        cnicInput.addEventListener('input', (e) => {
            e.target.value = e.target.value.replace(/\D/g, '').slice(0, 13);
        });
    }
    
    const nameInput = document.getElementById('name');
    if (nameInput) {
        nameInput.addEventListener('input', (e) => {
            e.target.value = e.target.value.replace(/[^a-zA-Z\s]/g, '');
        });
    }
}

// ==================== TOGGLE PASSWORD VISIBILITY ====================
window.togglePasswordVisibility = function(inputId) {
    const input = document.getElementById(inputId);
    if (! input) return;
    
    const button = input.parentElement.querySelector('.toggle-password i');
    if (! button) return;
    
    if (input.type === 'password') {
        input.type = 'text';
        button.classList.remove('fa-eye');
        button.classList.add('fa-eye-slash');
    } else {
        input.type = 'password';
        button.classList.remove('fa-eye-slash');
        button.classList.add('fa-eye');
    }
};

// ==================== FORM SUBMISSION ====================
function setupFormSubmission() {
    const form = document.getElementById('registration-form');
    if (!form) return;
    
    form.addEventListener('submit', async (e) => {
        e.preventDefault();
        
        if (!validateCurrentStep()) {
            showAlert('Please fill all required fields correctly', 'error');
            return;
        }
        
        const naSeat = parseInt(document.getElementById('na-seat').value);
        const provinceInfo = getProvinceFromNA(naSeat);
        const mapping = CONSTITUENCY_MAPPING[naSeat];
        
        if (!provinceInfo || !mapping) {
            showAlert('Invalid NA constituency selected', 'error');
            return;
        }
        
        let paSeat = parseInt(document.getElementById('pa-seat').value) || 0;
        
        const formData = {
            name: document.getElementById('name').value.trim(),
            cnic: document.getElementById('cnic').value.trim(),
            age: parseInt(document.getElementById('age').value),
            naSeat: naSeat,
            province: provinceInfo.name,
            provinceCode: provinceInfo.code,
            paSeat: paSeat,
            password: document.getElementById('password').value
        };
        
        console.log('📋 Submitting registration:', formData);
        showLoader('Registering voter... Please wait');
        
        try {
            const response = await API.call(CONFIG.API.ENDPOINTS.REGISTER_VOTER, 'POST', formData);
            hideLoader();
            console.log('📡 Registration response:', response);
            
            if (response.success) {
                const voterId = response.data.voterId || response.data.voter_id;
                showAlert(
                    `Registration Successful!\n\nYour Voter ID: ${voterId}\n\nPlease save this ID for login.`,
                    'success'
                );
                setTimeout(() => {
                    window.location.href = 'login.html';
                }, 5000);
            } else {
                showAlert(response.message || 'Registration failed', 'error');
            }
        } catch (error) {
            hideLoader();
            showAlert(error.message || 'Registration failed. Please try again.', 'error');
            console.error('❌ Registration error:', error);
        }
    });
}

// ==================== DOM READY ====================
document.addEventListener('DOMContentLoaded', () => {
    initializeRegistration();
});