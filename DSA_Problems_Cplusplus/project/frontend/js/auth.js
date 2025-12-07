// ==================== AUTHENTICATION SERVICE ====================
// Manages user sessions and authentication state

class AuthService {
    static TOKEN_KEY = 'auth_token';
    static USER_KEY = 'current_user';
    
    // Store authentication data after successful login
    static login(token, userData) {
        sessionStorage.setItem(this.TOKEN_KEY, token);
        sessionStorage.setItem(this.USER_KEY, JSON.stringify(userData));
    }
    
    // Get authentication token
    static getToken() {
        return sessionStorage.getItem(this.TOKEN_KEY);
    }
    
    // Get current logged-in user data
    static getCurrentUser() {
        const userData = sessionStorage.getItem(this.USER_KEY);
        return userData ? JSON.parse(userData) : null;
    }
    
    // Check if user is authenticated
    static isAuthenticated() {
        return !!this.getToken();
    }
    
    // Check if current user is admin
    static isAdmin() {
        const user = this.getCurrentUser();
        return user && user.type === 'admin';
    }
    
    // Check if current user is voter
    static isVoter() {
        const user = this.getCurrentUser();
        return user && user.type === 'voter';
    }
    
    // Logout user and clear session
    static logout() {
        sessionStorage.removeItem(this.TOKEN_KEY);
        sessionStorage.removeItem(this.USER_KEY);
        window.location.href = 'index.html';
    }
    
    // Protect page - redirect if not authenticated
    static protectPage(requiredType = null) {
        if (!this.isAuthenticated()) {
            // Save intended destination
            sessionStorage.setItem('redirect_after_login', window.location.href);
            window.location.href = 'login.html';
            return false;
        }
        
        const user = this.getCurrentUser();
        
        // Check if required type matches
        if (requiredType === 'admin' && !this.isAdmin()) {
            this.showError('Admin access required');
            window.location.href = 'index.html';
            return false;
        }
        
        if (requiredType === 'voter' && !this.isVoter()) {
            this.showError('Voter access required');
            window.location.href = 'index.html';
            return false;
        }
        
        return true;
    }
    
    // Get voter profile data
    static getVoterData() {
        const user = this.getCurrentUser();
        if (!user || user.type !== 'voter') {
            return null;
        }
        return user.voter || user;
    }
    
    // Update voter data in session (e.g., after voting)
    static updateVoterData(newData) {
        const user = this.getCurrentUser();
        if (user && user.type === 'voter') {
            if (user.voter) {
                user.voter = { ...user.voter, ...newData };
            } else {
                Object.assign(user, newData);
            }
            sessionStorage.setItem(this.USER_KEY, JSON.stringify(user));
        }
    }
    
    // Check if voter has voted for MNA
    static hasVotedMNA() {
        const voter = this.getVoterData();
        return voter ?  voter.hasVotedMNA : false;
    }
    
    // Check if voter has voted for MPA
    static hasVotedMPA() {
        const voter = this.getVoterData();
        return voter ?  voter.hasVotedMPA : false;
    }
    
    // Redirect to intended page after login
    static redirectAfterLogin() {
        const redirect = sessionStorage.getItem('redirect_after_login');
        sessionStorage.removeItem('redirect_after_login');
        
        const user = this.getCurrentUser();
        
        if (redirect && redirect !== 'login.html') {
            window.location.href = redirect;
        } else if (user.type === 'admin') {
            window.location.href = 'admin-panel.html';
        } else if (user.type === 'voter') {
            window.location.href = 'voter-dashboard.html';
        } else {
            window.location.href = 'index.html';
        }
    }
    
    // Show error message
    static showError(message) {
        // Create toast notification
        const toast = document.createElement('div');
        toast.className = 'toast toast-error';
        toast.innerHTML = `
            <i class="fas fa-exclamation-circle"></i>
            <span>${message}</span>
        `;
        document.body.appendChild(toast);
        
        setTimeout(() => {
            toast.classList.add('show');
        }, 100);
        
        setTimeout(() => {
            toast.classList.remove('show');
            setTimeout(() => toast.remove(), 300);
        }, 3000);
    }
    
    // Show success message
    static showSuccess(message) {
        const toast = document.createElement('div');
        toast.className = 'toast toast-success';
        toast.innerHTML = `
            <i class="fas fa-check-circle"></i>
            <span>${message}</span>
        `;
        document.body.appendChild(toast);
        
        setTimeout(() => {
            toast.classList.add('show');
        }, 100);
        
        setTimeout(() => {
            toast.classList.remove('show');
            setTimeout(() => toast.remove(), 300);
        }, 3000);
    }
    
    // Show info message
    static showInfo(message) {
        const toast = document.createElement('div');
        toast.className = 'toast toast-info';
        toast.innerHTML = `
            <i class="fas fa-info-circle"></i>
            <span>${message}</span>
        `;
        document.body.appendChild(toast);
        
        setTimeout(() => {
            toast.classList.add('show');
        }, 100);
        
        setTimeout(() => {
            toast.classList.remove('show');
            setTimeout(() => toast.remove(), 300);
        }, 3000);
    }
    
    // Check session validity
    static checkSession() {
        const token = this.getToken();
        const user = this.getCurrentUser();
        
        if (!token || !user) {
            return false;
        }
        
        // Check if token is expired (if using JWT)
        try {
            const tokenData = JSON.parse(atob(token.split('.')[1] || token));
            if (tokenData.exp && Date.now() >= tokenData.exp * 1000) {
                this.logout();
                return false;
            }
        } catch (e) {
            // Not a JWT token, continue
        }
        
        return true;
    }
    
    // Auto-logout after inactivity
    static setupAutoLogout(minutes = 30) {
        let timeout;
        
        const resetTimer = () => {
            clearTimeout(timeout);
            timeout = setTimeout(() => {
                this.showInfo('Session expired due to inactivity');
                this.logout();
            }, minutes * 60 * 1000);
        };
        
        // Reset timer on user activity
        ['mousedown', 'keypress', 'scroll', 'touchstart'].forEach(event => {
            document.addEventListener(event, resetTimer, true);
        });
        
        resetTimer();
    }
    
    // Get user display name
    static getUserDisplayName() {
        const user = this.getCurrentUser();
        if (! user) return 'Guest';
        
        if (user.type === 'admin') {
            return user.admin?.username || user.username || 'Admin';
        }
        
        if (user.type === 'voter') {
            return user.voter?.name || user.name || 'Voter';
        }
        
        return 'User';
    }
    
    // Get voter ID
    static getVoterId() {
        const voter = this.getVoterData();
        return voter?.voterId || 'N/A';
    }
    
    // Get voter CNIC
    static getVoterCNIC() {
        const voter = this.getVoterData();
        return voter?.cnic || 'N/A';
    }
}

// ==================== UI HELPER FUNCTIONS ====================

// Show loading spinner
function showLoader(message = 'Please wait...') {
    let loader = document.getElementById('global-loader');
    
    if (!loader) {
        loader = document.createElement('div');
        loader.id = 'global-loader';
        loader.className = 'loader-overlay';
        loader.innerHTML = `
            <div class="loader-content">
                <div class="spinner"></div>
                <p class="loader-text">${message}</p>
            </div>
        `;
        document.body.appendChild(loader);
    } else {
        loader.querySelector('.loader-text').textContent = message;
    }
    
    loader.classList.add('show');
}

// Hide loading spinner
function hideLoader() {
    const loader = document.getElementById('global-loader');
    if (loader) {
        loader.classList.remove('show');
    }
}

// Show confirmation dialog
function showConfirmDialog(message, onConfirm, onCancel) {
    const dialog = document.createElement('div');
    dialog.className = 'modal-overlay';
    dialog.innerHTML = `
        <div class="modal-content">
            <div class="modal-header">
                <h3>Confirmation</h3>
            </div>
            <div class="modal-body">
                <p>${message}</p>
            </div>
            <div class="modal-footer">
                <button class="btn btn-secondary" id="cancel-btn">Cancel</button>
                <button class="btn btn-primary" id="confirm-btn">Confirm</button>
            </div>
        </div>
    `;
    
    document.body.appendChild(dialog);
    
    setTimeout(() => dialog.classList.add('show'), 10);
    
    document.getElementById('confirm-btn').addEventListener('click', () => {
        dialog.classList.remove('show');
        setTimeout(() => dialog.remove(), 300);
        if (onConfirm) onConfirm();
    });
    
    document.getElementById('cancel-btn').addEventListener('click', () => {
        dialog.classList.remove('show');
        setTimeout(() => dialog.remove(), 300);
        if (onCancel) onCancel();
    });
    
    // Close on overlay click
    dialog.addEventListener('click', (e) => {
        if (e.target === dialog) {
            dialog.classList.remove('show');
            setTimeout(() => dialog.remove(), 300);
            if (onCancel) onCancel();
        }
    });
}

// Show alert dialog
function showAlert(message, type = 'info', duration = 3000) {
    const icons = {
        success: 'check-circle',
        error: 'times-circle',
        info: 'info-circle',
        warning: 'exclamation-triangle'
    };
    
    const alert = document.createElement('div');
    alert.className = `alert alert-${type} alert-toast`;
    alert.innerHTML = `
        <i class="fas fa-${icons[type]}"></i>
        <span>${message}</span>
        <button class="alert-close">&times;</button>
    `;
    
    document.body.appendChild(alert);
    
    setTimeout(() => alert.classList.add('show'), 10);
    
    const closeAlert = () => {
        alert.classList.remove('show');
        setTimeout(() => alert.remove(), 300);
    };
    
    alert.querySelector('.alert-close').addEventListener('click', closeAlert);
    
    if (duration > 0) {
        setTimeout(closeAlert, duration);
    }
}

// Format CNIC for display (e.g., 12345-1234567-1)
function formatCNIC(cnic) {
    if (!cnic || cnic.length !== 13) return cnic;
    return `${cnic.slice(0, 5)}-${cnic.slice(5, 12)}-${cnic.slice(12)}`;
}

// Mask CNIC for privacy (e.g., *****-*****67-1)
function maskCNIC(cnic) {
    if (!cnic || cnic.length !== 13) return cnic;
    return `*****-*****${cnic.slice(10, 12)}-${cnic.slice(12)}`;
}

// Format date
function formatDate(dateString) {
    const date = new Date(dateString);
    return date.toLocaleDateString('en-US', {
        year: 'numeric',
        month: 'long',
        day: 'numeric',
        hour: '2-digit',
        minute: '2-digit'
    });
}

// Debounce function
function debounce(func, wait) {
    let timeout;
    return function executedFunction(...args) {
        const later = () => {
            clearTimeout(timeout);
            func(...args);
        };
        clearTimeout(timeout);
        timeout = setTimeout(later, wait);
    };
}

// Throttle function
function throttle(func, limit) {
    let inThrottle;
    return function(...args) {
        if (! inThrottle) {
            func.apply(this, args);
            inThrottle = true;
            setTimeout(() => inThrottle = false, limit);
        }
    };
}

// Copy to clipboard
async function copyToClipboard(text) {
    try {
        await navigator.clipboard.writeText(text);
        showAlert('Copied to clipboard!', 'success', 2000);
    } catch (err) {
        // Fallback for older browsers
        const textArea = document.createElement('textarea');
        textArea.value = text;
        textArea.style.position = 'fixed';
        textArea.style.opacity = '0';
        document.body.appendChild(textArea);
        textArea.select();
        document.execCommand('copy');
        document.body.removeChild(textArea);
        showAlert('Copied to clipboard!', 'success', 2000);
    }
}

// Generate random color
function getRandomColor() {
    const colors = [
        '#01411C', '#0C6B3D', '#14805E', 
        '#28a745', '#20913a', '#17a2b8',
        '#007bff', '#6c757d'
    ];
    return colors[Math.floor(Math.random() * colors.length)];
}

// Validate form
function validateForm(formId) {
    const form = document.getElementById(formId);
    if (!form) return false;
    
    const inputs = form.querySelectorAll('input[required], select[required], textarea[required]');
    let isValid = true;
    
    inputs.forEach(input => {
        if (! input.value.trim()) {
            input.classList.add('invalid');
            isValid = false;
        } else {
            input.classList.remove('invalid');
            input.classList.add('valid');
        }
    });
    
    return isValid;
}

// Smooth scroll to element
function scrollToElement(elementId) {
    const element = document.getElementById(elementId);
    if (element) {
        element.scrollIntoView({
            behavior: 'smooth',
            block: 'start'
        });
    }
}

// ==================== PAGE INITIALIZATION ====================

// Initialize authentication state on page load
document.addEventListener('DOMContentLoaded', () => {
    // Check if user is logged in and update UI
    if (AuthService.isAuthenticated()) {
        const user = AuthService.getCurrentUser();
        
        // Update navigation with user info
        const navMenu = document.querySelector('.nav-menu');
        if (navMenu && ! window.location.pathname.includes('login')) {
            const userInfo = document.createElement('li');
            userInfo.innerHTML = `
                <div class="user-dropdown">
                    <button class="user-btn">
                        <i class="fas fa-user-circle"></i>
                        <span>${AuthService.getUserDisplayName()}</span>
                        <i class="fas fa-chevron-down"></i>
                    </button>
                    <div class="dropdown-menu">
                        ${user.type === 'voter' ? 
                            `<a href="voter-dashboard.html"><i class="fas fa-tachometer-alt"></i> Dashboard</a>` : 
                            `<a href="admin-panel.html"><i class="fas fa-shield-alt"></i> Admin Panel</a>`
                        }
                        <a href="#" onclick="AuthService.logout()"><i class="fas fa-sign-out-alt"></i> Logout</a>
                    </div>
                </div>
            `;
            navMenu.appendChild(userInfo);
        }
        
        // Setup auto-logout
        AuthService.setupAutoLogout(30); // 30 minutes
    }
    
    // Add toast container
    if (! document.querySelector('.toast-container')) {
        const toastContainer = document.createElement('div');
        toastContainer.className = 'toast-container';
        document.body.appendChild(toastContainer);
    }
});

// Export for use in other files
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        AuthService,
        showLoader,
        hideLoader,
        showConfirmDialog,
        showAlert,
        formatCNIC,
        maskCNIC,
        formatDate
    };
}