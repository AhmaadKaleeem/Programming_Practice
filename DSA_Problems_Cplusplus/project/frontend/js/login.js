// ==================== LOGIN.JS - Voter & Admin Login ====================

let currentLoginType = 'voter';

// ==================== INITIALIZE LOGIN ====================
function initializeLogin() {
    console.log('🔐 Login page initialized');
    
    // Check if admin mode from URL
    const urlParams = new URLSearchParams(window.location.search);
    if (urlParams.get('admin') === 'true') {
        switchLoginTab('admin');
    }
    
    setupFormValidation();
    setupFormSubmissions();
    autoFillRememberedCNIC();
}

// ==================== SWITCH LOGIN TAB ====================
window.switchLoginTab = function(type) {
    currentLoginType = type;
    
    const voterForm = document.getElementById('voter-login-form');
    const adminForm = document.getElementById('admin-login-form');
    const tabBtns = document.querySelectorAll('.tab-btn');
    
    if (! voterForm || !adminForm) return;
    
    // Update tabs
    tabBtns.forEach(btn => btn.classList.remove('active'));
    
    if (type === 'voter') {
        voterForm.classList.add('active');
        adminForm.classList.remove('active');
        if (tabBtns[0]) tabBtns[0].classList.add('active');
    } else {
        adminForm.classList.add('active');
        voterForm.classList.remove('active');
        if (tabBtns[1]) tabBtns[1].classList.add('active');
    }
    
    console.log(`🔄 Switched to ${type} login`);
};

// ==================== SETUP FORM VALIDATION ====================
function setupFormValidation() {
    // CNIC auto-format
    const cnicInput = document.getElementById('voter-cnic');
    if (cnicInput) {
        cnicInput.addEventListener('input', (e) => {
            e.target.value = e.target.value.replace(/\D/g, '').slice(0, 13);
        });
    }
    
    // Real-time validation
    const allInputs = document.querySelectorAll('input[required]');
    allInputs.forEach(input => {
        input.addEventListener('blur', () => validateLoginField(input));
        input.addEventListener('input', () => {
            // Clear error on input
            const errorEl = input.parentElement.querySelector('.error-message');
            if (errorEl && input.value.trim()) {
                errorEl.classList.remove('show');
                input.classList.remove('invalid');
            }
        });
    });
}

// ==================== VALIDATE LOGIN FIELD ====================
function validateLoginField(field) {
    const value = field.value.trim();
    let isValid = true;
    let errorMessage = '';
    
    if (!value) {
        isValid = false;
        errorMessage = 'This field is required';
    } else if (field.id === 'voter-cnic') {
        const cnicValidation = validateCNIC(value);
        if (!cnicValidation.valid) {
            isValid = false;
            errorMessage = cnicValidation.message;
        }
    }
    
    // Show/hide error
    let errorEl = field.parentElement.querySelector('.error-message');
    if (! errorEl) {
        errorEl = document.createElement('span');
        errorEl.className = 'error-message';
        field.parentElement.appendChild(errorEl);
    }
    
    if (! isValid) {
        errorEl.textContent = errorMessage;
        errorEl.classList.add('show');
        field.classList.add('invalid');
    } else {
        errorEl.classList.remove('show');
        field.classList.remove('invalid');
    }
    
    return isValid;
}

// ==================== SETUP FORM SUBMISSIONS ====================
function setupFormSubmissions() {
    // Voter Login
    const voterForm = document.getElementById('voter-login-form');
    if (voterForm) {
        voterForm.addEventListener('submit', handleVoterLogin);
    }
    
    // Admin Login
    const adminForm = document.getElementById('admin-login-form');
    if (adminForm) {
        adminForm.addEventListener('submit', handleAdminLogin);
    }
}

// ==================== HANDLE VOTER LOGIN ====================
async function handleVoterLogin(e) {
    e.preventDefault();
    
    const cnicInput = document.getElementById('voter-cnic');
    const passwordInput = document.getElementById('voter-password');
    const rememberMe = document.getElementById('remember-me')?.checked || false;
    
    const cnic = cnicInput.value.trim();
    const password = passwordInput.value;
    
    console.log('🔐 Voter login attempt:', { cnic, hasPassword: !!password });
    
    // Validate
    const cnicValidation = validateCNIC(cnic);
    if (!cnicValidation.valid) {
        showAlert(cnicValidation.message, 'error');
        cnicInput.focus();
        return;
    }
    
    if (!password) {
        showAlert('Please enter your password', 'error');
        passwordInput.focus();
        return;
    }
    
    // Show loader
    showLoader('Authenticating...');
    
    try {
        const response = await API.call(CONFIG.API.ENDPOINTS.LOGIN_VOTER, 'POST', {
            cnic: cnic,
            password: password
        });
        
        hideLoader();
        
        console.log('📡 Voter login response:', response);
        
        if (response.success) {
            // Store auth data
            AuthService.login(response.data.token, {
                type: 'voter',
                cnic: cnic,
                voterId: response.data.voterId || response.data.voter_id,
                name: response.data.name || response.data.voter_name,
                ...response.data
            });
            
            // Remember CNIC if checked
            if (rememberMe) {
                localStorage.setItem('rememberedCNIC', cnic);
            } else {
                localStorage.removeItem('rememberedCNIC');
            }
            
            showAlert('✅ Login successful!  Redirecting...', 'success');
            
            setTimeout(() => {
                window.location.href = 'voter-dashboard.html';
            }, 1500);
        } else {
            showAlert(response.message || 'Invalid CNIC or password', 'error');
        }
    } catch (error) {
        hideLoader();
        console.error('❌ Voter login error:', error);
        showAlert(error.message || 'Invalid CNIC or password. Please try again.', 'error');
    }
}

// ==================== HANDLE ADMIN LOGIN ====================
async function handleAdminLogin(e) {
    e.preventDefault();
    
    const usernameInput = document.getElementById('admin-username');
    const passwordInput = document.getElementById('admin-password');
    
    const username = usernameInput.value.trim();
    const password = passwordInput.value;
    
    console.log('🔐 Admin login attempt:', { username, hasPassword: !!password });
    
    if (!username || !password) {
        showAlert('Please enter username and password', 'error');
        return;
    }
    
    showLoader('Authenticating admin...');
    
    try {
        const response = await API.call(CONFIG.API.ENDPOINTS.LOGIN_ADMIN, 'POST', {
            username: username,
            password: password
        });
        
        hideLoader();
        
        console.log('📡 Admin login response:', response);
        
        if (response.success) {
            // Store admin auth data
            AuthService.login(response.data.token, {
                type: 'admin',
                username: username,
                name: response.data.name || username,
                ...response.data
            });
            
            showAlert('✅ Admin login successful!  Redirecting...', 'success');
            
            setTimeout(() => {
                window.location.href = 'admin-panel.html';
            }, 1500);
        } else {
            showAlert(response.message || 'Invalid admin credentials', 'error');
        }
    } catch (error) {
        hideLoader();
        console.error('❌ Admin login error:', error);
        showAlert(error.message || 'Invalid admin credentials.Please try again.', 'error');
    }
}

// ==================== AUTO-FILL REMEMBERED CNIC ====================
function autoFillRememberedCNIC() {
    const rememberedCNIC = localStorage.getItem('rememberedCNIC');
    if (rememberedCNIC) {
        const cnicInput = document.getElementById('voter-cnic');
        const rememberCheckbox = document.getElementById('remember-me');
        
        if (cnicInput) {
            cnicInput.value = rememberedCNIC;
            console.log('📝 Auto-filled remembered CNIC');
        }
        if (rememberCheckbox) rememberCheckbox.checked = true;
    }
}

// ==================== CHECK IF ALREADY LOGGED IN ====================
function checkExistingSession() {
    if (AuthService.isAuthenticated()) {
        const user = AuthService.getCurrentUser();
        console.log('✅ Existing session found:', user.type);
        
        if (user.type === 'voter') {
            window.location.href = 'voter-dashboard.html';
        } else if (user.type === 'admin') {
            window.location.href = 'admin-panel.html';
        }
    }
}

// ==================== TOGGLE PASSWORD VISIBILITY ====================
window.togglePasswordVisibility = function(inputId) {
    const input = document.getElementById(inputId);
    const button = input.parentElement.querySelector('.toggle-password i');
    
    if (! input || !button) return;
    
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

// ==================== DOM READY ====================
document.addEventListener('DOMContentLoaded', () => {
    checkExistingSession();
    initializeLogin();
});