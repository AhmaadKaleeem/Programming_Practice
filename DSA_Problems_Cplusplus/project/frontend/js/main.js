// ==================== MAIN.JS - Homepage & General Functionality ====================

// ==================== MOBILE MENU ====================
function initializeMobileMenu() {
    const hamburger = document.getElementById('hamburger');
    const navMenu = document.getElementById('nav-menu');
    
    if (hamburger && navMenu) {
        hamburger.addEventListener('click', () => {
            navMenu.classList.toggle('active');
            hamburger.classList.toggle('active');
        });
        
        // Close menu when clicking on a link
        document.querySelectorAll('.nav-link').forEach(link => {
            link.addEventListener('click', () => {
                navMenu.classList.remove('active');
                hamburger.classList.remove('active');
            });
        });
        
        // Close menu when clicking outside
        document.addEventListener('click', (e) => {
            if (!hamburger.contains(e.target) && !navMenu.contains(e.target)) {
                navMenu.classList.remove('active');
                hamburger.classList.remove('active');
            }
        });
    }
}

// ==================== CHECK BACKEND CONNECTION ====================
async function checkBackendConnection() {
    try {
        const response = await fetch(`${CONFIG.API.BASE_URL.replace('/api', '')}/api/test`, {
            method: 'GET',
            headers: { 'Content-Type': 'application/json' }
        });
        
        if (response.ok) {
            const data = await response.json();
            console.log('✅ Backend connected:', data);
            return true;
        }
        
        console.warn('⚠️ Backend responded but not OK:', response.status);
        return false;
    } catch (error) {
        console.error('❌ Backend connection failed:', error);
        return false;
    }
}

// ==================== FETCH VOTING STATUS FROM API ====================
async function fetchVotingStatus() {
    try {
        const timestamp = new Date().getTime();
        const response = await fetch(`${CONFIG.API.BASE_URL}/voting/status? t=${timestamp}`);
        
        if (! response.ok) {
            throw new Error(`HTTP ${response.status}`);
        }
        
        const data = await response.json();
        console.log('📡 Backend voting status:', data);
        return data;
    } catch (error) {
        console.error('❌ Error fetching voting status:', error);
        return null;
    }
}

// ==================== LOAD STATISTICS FROM BACKEND ====================
async function loadStatistics() {
    try {
        console.log('📊 Loading statistics...');
        
        // Try to get stats from backend first
        const response = await fetch(`${CONFIG.API.BASE_URL}/admin/stats`);
        
        if (response.ok) {
            const data = await response.json();
            
            if (data.success) {
                console.log('📊 Backend stats:', data.data);
                
                // Update voter count from backend
                const voterCountEl = document.getElementById('stat-voters');
                if (voterCountEl) {
                    const count = data.data.totalVoters || 0;
                    voterCountEl.setAttribute('data-target', count);
                    voterCountEl.textContent = '0';
                    console.log(`👥 Registered voters: ${count}`);
                }
                
                return;
            }
        }
        
        // Fallback to localStorage if backend unavailable
        console.log('⚠️ Backend stats unavailable, using localStorage');
        const voters = JSON.parse(localStorage.getItem('voters') || '[]');
        const voterCountEl = document.getElementById('stat-voters');
        if (voterCountEl) {
            voterCountEl.setAttribute('data-target', voters.length);
            voterCountEl.textContent = '0';
            console.log(`👥 Registered voters (local): ${voters.length}`);
        }
    } catch (error) {
        console.error('❌ Error loading statistics:', error);
        
        // Set to 0 on error
        const voterCountEl = document.getElementById('stat-voters');
        if (voterCountEl) {
            voterCountEl.setAttribute('data-target', 0);
            voterCountEl.textContent = '0';
        }
    }
}

// ==================== VOTING STATUS DISPLAY ====================
async function updateVotingStatus() {
    const statusContent = document.getElementById('voting-status-content');
    const electionDateEl = document.getElementById('election-date');
    const votingHoursEl = document.getElementById('voting-hours');
    const currentTimeEl = document.getElementById('current-time');
    
    if (!statusContent) return;
    
    // Check backend connection
    const isConnected = await checkBackendConnection();
    
    if (!isConnected) {
        if (electionDateEl) electionDateEl.textContent = '⚠️ Backend Offline';
        if (votingHoursEl) votingHoursEl.textContent = 'N/A';
        
        statusContent.innerHTML = `
            <div class="status-indicator status-closed" style="background: rgba(255, 193, 7, 0.1); border: 2px solid #ffc107;">
                <i class="fas fa-exclamation-triangle" style="font-size: 3rem; color: #ffc107; margin-bottom: 1rem;"></i>
                <h3 style="color: #ffc107; font-size: 1.8rem; margin-bottom: 1rem;">⚠️ Backend Server Not Running</h3>
                <div style="background: rgba(255, 193, 7, 0.1); padding: 20px; border-radius: 10px; text-align: left; margin: 1rem 0;">
                    <p style="margin-bottom: 10px; font-weight: 600; color: #333;">
                        <i class="fas fa-server"></i> To start the backend:
                    </p>
                    <ol style="margin-left: 20px; color: #555; line-height: 1.8;">
                        <li>Open terminal in project directory</li>
                        <li>Run: <code style="background: #f0f0f0; padding: 2px 6px; border-radius: 3px; color: #01411C;">.\\build\\elections_api.exe</code></li>
                        <li>Wait for "Listening..." message</li>
                        <li>Refresh this page</li>
                    </ol>
                </div>
                <div style="margin-top: 1.5rem;">
                    <button onclick="location.reload()" class="btn btn-primary" style="display: inline-block; padding: 12px 30px; font-size: 1.1rem; background: #01411C; color: white; border: none; border-radius: 8px; cursor: pointer;">
                        <i class="fas fa-sync"></i> Retry Connection
                    </button>
                </div>
            </div>
        `;
        return;
    }
    
    // Fetch voting status from API
    const apiStatus = await fetchVotingStatus();
    
    if (! apiStatus || !apiStatus.success) {
        console.warn('⚠️ Could not fetch voting status');
        if (electionDateEl) electionDateEl.textContent = 'Connection Error';
        if (votingHoursEl) votingHoursEl.textContent = 'N/A';
        
        statusContent.innerHTML = `
            <div class="status-indicator status-closed">
                <i class="fas fa-exclamation-triangle" style="font-size: 3rem; color: #ffc107; margin-bottom: 1rem;"></i>
                <h3 style="color: #ffc107; font-size: 1.8rem;">Unable to Fetch Status</h3>
                <p style="color: var(--text-secondary);">Backend is running but status unavailable</p>
            </div>
        `;
        return;
    }
    
    // Update CONFIG with backend data
    CONFIG.ELECTION.year = apiStatus.data.year;
    CONFIG.ELECTION.month = apiStatus.data.month;
    CONFIG.ELECTION.day = apiStatus.data.day;
    CONFIG.ELECTION.votingHours.startHour = apiStatus.data.startHour;
    CONFIG.ELECTION.votingHours.endHour = apiStatus.data.endHour;
    
    // ALWAYS UPDATE election date
    if (electionDateEl) {
        const date = new Date(apiStatus.data.year, apiStatus.data.month - 1, apiStatus.data.day);
        electionDateEl.textContent = date.toLocaleDateString('en-US', { 
            weekday: 'long', 
            year: 'numeric', 
            month: 'long', 
            day: 'numeric' 
        });
    }
    
    // ALWAYS UPDATE voting hours
    if (votingHoursEl) {
        votingHoursEl.textContent = `${formatTime(apiStatus.data.startHour)} - ${formatTime(apiStatus.data.endHour)}`;
    }
    
    // ALWAYS UPDATE current time
    if (currentTimeEl) {
        const now = new Date();
        currentTimeEl.innerHTML = `
            <i class="fas fa-clock"></i>
            ${now.toLocaleTimeString('en-US', {
                hour: '2-digit',
                minute: '2-digit',
                second: '2-digit',
                hour12: true
            })}
        `;
    }
    
    // Get current date/time
    const now = new Date();
    const electionDate = new Date(apiStatus.data.year, apiStatus.data.month - 1, apiStatus.data.day);
    const electionStart = new Date(apiStatus.data.year, apiStatus.data.month - 1, apiStatus.data.day, apiStatus.data.startHour, 0, 0);
    const electionEnd = new Date(apiStatus.data.year, apiStatus.data.month - 1, apiStatus.data.day, apiStatus.data.endHour, 0, 0);
    
    console.log(`🗳️ Status: ${apiStatus.data.isVotingOpen ? 'OPEN' : 'CLOSED'} | Election: ${electionDate.toDateString()} | Current: ${now.toDateString()}`);
    
    // ==================== CASE 1: VOTING IS OPEN ====================
    if (apiStatus.data.isVotingOpen) {
        const timeRemaining = getTimeRemainingInVoting();
        statusContent.innerHTML = `
            <div class="status-indicator status-open">
                <i class="fas fa-check-circle" style="font-size: 3rem; color: #28a745; margin-bottom: 1rem;"></i>
                <h3 style="color: #28a745; font-size: 1.8rem; margin-bottom: 0.5rem;">🗳️ Voting is OPEN</h3>
                <p style="color: var(--text-secondary); font-size: 1.2rem; margin-bottom: 1rem;">Cast your vote now!</p>
                ${timeRemaining ?  `
                    <div class="time-remaining" style="background: rgba(40, 167, 69, 0.1); padding: 15px; border-radius: 10px; margin-top: 1rem;">
                        <i class="fas fa-hourglass-half" style="color: #28a745; margin-right: 10px;"></i>
                        <span style="color: #28a745; font-weight: 600; font-size: 1.1rem;">
                            ${timeRemaining.hours}h ${timeRemaining.minutes}m ${timeRemaining.seconds}s remaining
                        </span>
                    </div>
                ` : ''}
                <div style="margin-top: 1.5rem;">
                    <a href="login.html" class="btn btn-primary" style="display: inline-block; padding: 12px 30px; font-size: 1.1rem; text-decoration: none; background: #01411C; color: white; border-radius: 8px; transition: all 0.3s;">
                        <i class="fas fa-vote-yea"></i> Vote Now
                    </a>
                </div>
            </div>
        `;
        return;
    }
    
    // ==================== CASE 2: ELECTION DAY - BEFORE VOTING ====================
    if (now.toDateString() === electionDate.toDateString() && now < electionStart) {
        const diff = electionStart - now;
        const hoursUntil = Math.floor(diff / (1000 * 60 * 60));
        const minutesUntil = Math.floor((diff % (1000 * 60 * 60)) / (1000 * 60));
        const secondsUntil = Math.floor((diff % (1000 * 60)) / 1000);
        
        statusContent.innerHTML = `
            <div class="status-indicator" style="background: linear-gradient(135deg, rgba(255, 193, 7, 0.1), rgba(255, 152, 0, 0.1)); border: 2px solid rgba(255, 152, 0, 0.3);">
                <i class="fas fa-clock" style="font-size: 3rem; color: #ff9800; margin-bottom: 1rem; animation: pulse 2s infinite;"></i>
                <h3 style="color: #ff9800; font-size: 1.8rem; margin-bottom: 0.5rem;">⏰ Voting Opens Today! </h3>
                <p style="color: var(--text-secondary); font-size: 1.1rem; margin-bottom: 1.5rem;">Get ready to cast your vote!</p>
                <div class="countdown-timer" style="margin: 2rem 0;">
                    <div class="countdown-item">
                        <span class="countdown-value" id="countdown-hours-today">${hoursUntil}</span>
                        <span class="countdown-label">Hours</span>
                    </div>
                    <div class="countdown-item">
                        <span class="countdown-value" id="countdown-minutes-today">${minutesUntil}</span>
                        <span class="countdown-label">Minutes</span>
                    </div>
                    <div class="countdown-item">
                        <span class="countdown-value" id="countdown-seconds-today">${secondsUntil}</span>
                        <span class="countdown-label">Seconds</span>
                    </div>
                </div>
                <div style="background: rgba(255, 152, 0, 0.15); padding: 15px; border-radius: 10px; margin-top: 1.5rem;">
                    <i class="fas fa-info-circle" style="color: #ff9800; margin-right: 10px;"></i>
                    <span style="color: #ff9800; font-weight: 600; font-size: 1.1rem;">
                        Voting starts at ${formatTime(apiStatus.data.startHour)}
                    </span>
                </div>
            </div>
        `;
        return;
    }
    
    // ==================== CASE 3: ELECTION DAY - AFTER VOTING ====================
    if (now.toDateString() === electionDate.toDateString() && now >= electionEnd) {
        statusContent.innerHTML = `
            <div class="status-indicator status-closed">
                <i class="fas fa-times-circle" style="font-size: 3rem; color: #dc3545; margin-bottom: 1rem;"></i>
                <h3 style="color: #dc3545; font-size: 1.8rem; margin-bottom: 0.5rem;">Voting Has Closed for Today</h3>
                <p style="color: var(--text-secondary); font-size: 1.1rem; margin-bottom: 1rem;">
                    Voting ended at ${formatTime(apiStatus.data.endHour)}
                </p>
                <div style="margin-top: 1.5rem;">
                    <a href="results.html" class="btn btn-primary" style="display: inline-block; padding: 12px 30px; font-size: 1.1rem; text-decoration: none; background: #01411C; color: white; border-radius: 8px;">
                        <i class="fas fa-chart-bar"></i> View Results
                    </a>
                </div>
            </div>
        `;
        return;
    }
    
    // ==================== CASE 4: BEFORE ELECTION DAY ====================
    if (now < electionDate) {
        const timeUntil = getTimeUntilElection();
        statusContent.innerHTML = `
            <div class="status-indicator">
                <h3 style="color: var(--primary-color); font-size: 1.8rem; margin-bottom: 1.5rem;">
                    <i class="fas fa-calendar-alt"></i> Elections Starting In
                </h3>
                <div class="countdown-timer">
                    <div class="countdown-item">
                        <span class="countdown-value" id="countdown-days">${timeUntil.days}</span>
                        <span class="countdown-label">Days</span>
                    </div>
                    <div class="countdown-item">
                        <span class="countdown-value" id="countdown-hours">${timeUntil.hours}</span>
                        <span class="countdown-label">Hours</span>
                    </div>
                    <div class="countdown-item">
                        <span class="countdown-value" id="countdown-minutes">${timeUntil.minutes}</span>
                        <span class="countdown-label">Minutes</span>
                    </div>
                    <div class="countdown-item">
                        <span class="countdown-value" id="countdown-seconds">${timeUntil.seconds}</span>
                        <span class="countdown-label">Seconds</span>
                    </div>
                </div>
            </div>
        `;
        return;
    }
    
    // ==================== CASE 5: AFTER ELECTION ====================
    statusContent.innerHTML = `
        <div class="status-indicator status-closed">
            <i class="fas fa-times-circle" style="font-size: 3rem; color: #dc3545; margin-bottom: 1rem;"></i>
            <h3 style="color: #dc3545; font-size: 1.8rem; margin-bottom: 0.5rem;">Elections Have Ended</h3>
            <p style="color: var(--text-secondary);">Check results page for final outcomes</p>
            <div style="margin-top: 1.5rem;">
                <a href="results.html" class="btn btn-primary" style="display: inline-block; padding: 12px 30px; font-size: 1.1rem; text-decoration: none; background: #01411C; color: white; border-radius: 8px;">
                    <i class="fas fa-chart-bar"></i> View Results
                </a>
            </div>
        </div>
    `;
}

// ==================== UPDATE COUNTDOWN ====================
function updateCountdown() {
    const timeUntil = getTimeUntilElection();
    if (timeUntil.isPast) return;
    
    const daysEl = document.getElementById('countdown-days');
    const hoursEl = document.getElementById('countdown-hours');
    const minutesEl = document.getElementById('countdown-minutes');
    const secondsEl = document.getElementById('countdown-seconds');
    
    if (daysEl) daysEl.textContent = timeUntil.days;
    if (hoursEl) hoursEl.textContent = timeUntil.hours;
    if (minutesEl) minutesEl.textContent = timeUntil.minutes;
    if (secondsEl) secondsEl.textContent = timeUntil.seconds;
}

// ==================== UPDATE TODAY'S COUNTDOWN ====================
function updateTodayCountdown() {
    const hoursEl = document.getElementById('countdown-hours-today');
    const minutesEl = document.getElementById('countdown-minutes-today');
    const secondsEl = document.getElementById('countdown-seconds-today');
    
    if (! hoursEl || !minutesEl || !secondsEl) return;
    
    const now = new Date();
    const electionStart = new Date(
        CONFIG.ELECTION.year,
        CONFIG.ELECTION.month - 1,
        CONFIG.ELECTION.day,
        CONFIG.ELECTION.votingHours.startHour,
        0, 0
    );
    
    const diff = electionStart - now;
    if (diff < 0) return;
    
    const hours = Math.floor(diff / (1000 * 60 * 60));
    const minutes = Math.floor((diff % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((diff % (1000 * 60)) / 1000);
    
    hoursEl.textContent = hours;
    minutesEl.textContent = minutes;
    secondsEl.textContent = seconds;
}

// ==================== ANIMATE STATISTICS ====================
function animateStatistics() {
    const statNumbers = document.querySelectorAll('.stat-number');
    
    const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                const target = parseInt(entry.target.getAttribute('data-target'));
                animateCounter(entry.target, target);
                observer.unobserve(entry.target);
            }
        });
    }, { threshold: 0.5 });
    
    statNumbers.forEach(stat => observer.observe(stat));
}

function animateCounter(element, target) {
    const duration = 2000;
    const increment = target / (duration / 16);
    let current = 0;
    
    const timer = setInterval(() => {
        current += increment;
        if (current >= target) {
            element.textContent = target.toLocaleString();
            clearInterval(timer);
        } else {
            element.textContent = Math.floor(current).toLocaleString();
        }
    }, 16);
}

// ==================== SMOOTH SCROLL ====================
function initializeSmoothScroll() {
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            const target = document.querySelector(this.getAttribute('href'));
            if (target) {
                target.scrollIntoView({
                    behavior: 'smooth',
                    block: 'start'
                });
            }
        });
    });
}

// ==================== ACTIVE NAV LINK ====================
function updateActiveNavLink() {
    const sections = document.querySelectorAll('section[id]');
    const navLinks = document.querySelectorAll('.nav-link');
    
    let currentSection = '';
    
    sections.forEach(section => {
        const sectionTop = section.offsetTop;
        if (window.scrollY >= (sectionTop - 100)) {
            currentSection = section.getAttribute('id');
        }
    });
    
    navLinks.forEach(link => {
        link.classList.remove('active');
        if (link.getAttribute('href') === `#${currentSection}`) {
            link.classList.add('active');
        }
    });
}

// ==================== FADE IN ANIMATIONS ====================
function initializeFadeAnimations() {
    const fadeElements = document.querySelectorAll('.fade-in-up');
    
    const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.style.opacity = '1';
                entry.target.style.transform = 'translateY(0)';
            }
        });
    }, { threshold: 0.1 });
    
    fadeElements.forEach(element => {
        element.style.opacity = '0';
        element.style.transform = 'translateY(30px)';
        element.style.transition = 'all 0.6s ease';
        observer.observe(element);
    });
}

// ==================== INITIALIZE HOMEPAGE ====================
async function initializeHomepage() {
    console.log('🇵🇰 Pakistan EMS - Homepage Initialized');
    console.log('📡 Connecting to backend...');
    
    // Initialize mobile menu
    initializeMobileMenu();
    
    // Load statistics from backend
    await loadStatistics();
    
    // Update voting status
    await updateVotingStatus();
    
    // Update every second
    setInterval(updateVotingStatus, 1000); // Every 1 seconds for status
    setInterval(updateCountdown, 1000);
    setInterval(updateTodayCountdown, 1000);
    
    // Reload stats every 30 seconds
    setInterval(loadStatistics, 30000);
    
    // Initialize animations after short delay
    setTimeout(animateStatistics, 500);
    initializeFadeAnimations();
    
    // Smooth scroll
    initializeSmoothScroll();
    
    // Update active nav link on scroll
    window.addEventListener('scroll', updateActiveNavLink);
    
    console.log('✅ Homepage initialization complete');
}

// ==================== DOM READY ====================
document.addEventListener('DOMContentLoaded', () => {
    initializeHomepage();
});