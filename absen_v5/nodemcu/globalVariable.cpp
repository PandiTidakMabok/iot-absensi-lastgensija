#include "require.hpp"

WiFiUDP ntpUDP;
Condition condition;

NTPClient timeClient(ntpUDP, NTPSERVER, NTPOFFSET);

int I2CADDR = 0x27;
bool runprogram = false;
const char html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Konfigurasi NodeMCU</title>
    <style>
        :root {
            --primary-color: #4361ee;
            --primary-hover: #3a56d4;
            --text-color: #333;
            --light-text: #666;
            --lighter-text: #999;
            --success-color: #2ecc71;
            --error-color: #e74c3c;
            --bg-color: #f0f2f5;
            --card-bg: #ffffff;
            --border-radius: 12px;
            --input-border: #e1e4e8;
            --input-focus: #4361ee;
            --box-shadow: 0 10px 15px -3px rgba(0, 0, 0, 0.1), 0 4px 6px -2px rgba(0, 0, 0, 0.05);
        }

        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }

        body {
            background: var(--bg-color);
            color: var(--text-color);
            padding: 20px;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            line-height: 1.6;
        }

        .container {
            max-width: 420px;
            width: 100%;
            background: var(--card-bg);
            padding: 28px;
            border-radius: var(--border-radius);
            box-shadow: var(--box-shadow);
            animation: fadeIn 0.5s ease-out;
        }

        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(20px); }
            to { opacity: 1; transform: translateY(0); }
        }

        .header {
            text-align: center;
            margin-bottom: 25px;
        }

        .header h1 {
            font-size: 24px;
            color: var(--text-color);
            margin-bottom: 8px;
            font-weight: 600;
        }

        .header p {
            color: var(--light-text);
            font-size: 14px;
        }

        .icon {
            margin: 0 auto 15px;
            width: 70px;
            height: 70px;
            background-color: rgba(67, 97, 238, 0.1);
            border-radius: 50%;
            display: flex;
            align-items: center;
            justify-content: center;
        }

        .form-group {
            margin-bottom: 18px;
            position: relative;
        }

        .form-label {
            display: block;
            margin-bottom: 8px;
            font-weight: 500;
            font-size: 14px;
            color: var(--light-text);
        }

        .form-control {
            width: 100%;
            padding: 12px 16px;
            border: 1px solid var(--input-border);
            border-radius: 8px;
            font-size: 16px;
            transition: all 0.3s ease;
            background-color: #fafbfc;
        }

        .form-control:focus {
            border-color: var(--input-focus);
            outline: none;
            box-shadow: 0 0 0 3px rgba(67, 97, 238, 0.25);
            background-color: #fff;
        }

        .form-control::placeholder {
            color: var(--lighter-text);
        }

        .btn {
            display: block;
            width: 100%;
            padding: 12px;
            font-size: 16px;
            border-radius: 8px;
            cursor: pointer;
            border: none;
            font-weight: 600;
            transition: all 0.3s ease;
            position: relative;
            overflow: hidden;
        }

        .btn-primary {
            color: #fff;
            background: var(--primary-color);
        }

        .btn-primary:hover {
            background: var(--primary-hover);
            transform: translateY(-2px);
            box-shadow: 0 5px 15px rgba(67, 97, 238, 0.4);
        }

        .btn-primary:active {
            transform: translateY(0);
        }

        .btn-primary:disabled {
            opacity: 0.7;
            cursor: not-allowed;
            transform: none;
            box-shadow: none;
        }

        .btn .spinner {
            display: none;
            width: 16px;
            height: 16px;
            border: 2px solid transparent;
            border-top-color: #ffffff;
            border-radius: 50%;
            position: absolute;
            top: 50%;
            left: 50%;
            margin-top: -8px;
            margin-left: -8px;
            animation: spin 1s linear infinite;
        }

        @keyframes spin {
            to { transform: rotate(360deg); }
        }

        .btn.loading .spinner {
            display: block;
        }

        .btn.loading .btn-text {
            visibility: hidden;
        }

        .alert {
            padding: 12px 16px;
            border-radius: 8px;
            margin-top: 20px;
            display: flex;
            align-items: center;
            transform: translateY(20px);
            opacity: 0;
            height: 0;
            overflow: hidden;
            transition: all 0.3s ease;
        }

        .alert.show {
            transform: translateY(0);
            opacity: 1;
            height: auto;
        }

        .alert-success {
            background: rgba(46, 204, 113, 0.15);
            color: #27ae60;
            border-left: 4px solid #2ecc71;
        }

        .alert-error {
            background: rgba(231, 76, 60, 0.15);
            color: #c0392b;
            border-left: 4px solid #e74c3c;
        }

        .alert-icon {
            margin-right: 12px;
            font-size: 18px;
        }

        .form-footer {
            text-align: center;
            margin-top: 25px;
            font-size: 13px;
            color: var(--lighter-text);
        }

        .show-password {
            position: absolute;
            right: 12px;
            top: 38px;
            cursor: pointer;
            color: var(--lighter-text);
            background: none;
            border: none;
            font-size: 16px;
        }

        @media (max-width: 480px) {
            .container {
                padding: 20px;
                border-radius: 8px;
            }
        }

        /* Styling untuk menampilkan kekuatan password */
        .password-strength {
            height: 5px;
            margin-top: 8px;
            border-radius: 3px;
            transition: all 0.3s ease;
            background: #f1f1f1;
        }

        .password-strength-meter {
            height: 100%;
            width: 0;
            border-radius: 3px;
            transition: all 0.3s ease;
        }

        .weak { width: 33%; background-color: #e74c3c; }
        .medium { width: 66%; background-color: #f39c12; }
        .strong { width: 100%; background-color: #2ecc71; }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <div class="icon">
                <svg width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="#4361ee" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                    <path d="M5 12h14"></path>
                    <path d="M12 5v14"></path>
                    <path d="M20 18v3h-3"></path>
                    <path d="M16 3h3v3"></path>
                    <path d="M4 20l2-2"></path>
                    <path d="M4 9V6h3"></path>
                </svg>
            </div>
            <h1>Konfigurasi NodeMCU</h1>
            <p>Masukkan informasi untuk mengkonfigurasi perangkat</p>
        </div>

        <form id="configForm">
            <div class="form-group">
                <label for="ssid" class="form-label">WiFi (SSID)</label>
                <input type="text" class="form-control" id="ssid" name="ssid" placeholder="Masukkan nama WiFi" required>
            </div>

            <div class="form-group">
                <label for="password" class="form-label">Password WiFi</label>
                <input type="password" class="form-control" id="password" name="password" placeholder="Masukkan password WiFi" required>
                <button type="button" class="show-password" id="togglePassword" aria-label="Tampilkan password">👁️</button>
                <div class="password-strength">
                    <div class="password-strength-meter" id="passwordStrength"></div>
                </div>
            </div>

            <div class="form-group">
                <label for="nodered" class="form-label">Node-RED URL</label>
                <input type="url" class="form-control" id="nodered" name="nodered" placeholder="http://IP:PORT/absensi" required>
            </div>

            <button type="submit" class="btn btn-primary">
                <span class="btn-text">Simpan Konfigurasi</span>
                <span class="spinner"></span>
            </button>
        </form>

        <div class="alert alert-success" id="successMsg">
            <span class="alert-icon">✅</span>
            <span>Konfigurasi berhasil disimpan! Perangkat akan terhubung kembali...</span>
        </div>

        <div class="alert alert-error" id="errorMsg">
            <span class="alert-icon">❌</span>
            <span>Gagal menyimpan konfigurasi. Silakan coba lagi.</span>
        </div>

        <div class="form-footer">
            NodeMCU Configuration v1.0 &copy; 2025
        </div>
    </div>

    <script>
        // Toggle password visibility
        document.getElementById('togglePassword').addEventListener('click', function() {
            const passwordInput = document.getElementById('password');
            if (passwordInput.type === 'password') {
                passwordInput.type = 'text';
                this.textContent = '🔒';
            } else {
                passwordInput.type = 'password';
                this.textContent = '👁️';
            }
        });

        // Password strength meter
        document.getElementById('password').addEventListener('input', function() {
            const password = this.value;
            const meter = document.getElementById('passwordStrength');
            
            if (password.length === 0) {
                meter.className = '';
                meter.style.width = '0';
                return;
            }
            
            // Simple password strength check
            if (password.length < 8) {
                meter.className = 'weak';
            } else if (password.length < 12 || !/[A-Z]/.test(password) || !/[0-9]/.test(password)) {
                meter.className = 'medium';
            } else {
                meter.className = 'strong';
            }
        });

        // Form submission
        document.getElementById('configForm').addEventListener('submit', function(e) {
            e.preventDefault();
            
            const formData = new FormData(e.target);
            const urlEncoded = new URLSearchParams(formData).toString();
            const submitBtn = document.querySelector('.btn-primary');
            
            // Show loading state
            submitBtn.classList.add('loading');
            submitBtn.disabled = true;
            
            // Hide any previous alerts
            document.getElementById('successMsg').classList.remove('show');
            document.getElementById('errorMsg').classList.remove('show');
            
            fetch('/save', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded'
                },
                body: urlEncoded
            })
            .then(response => {
                if (response.ok) {
                    document.getElementById('successMsg').classList.add('show');
                    // Countdown for reload
                    let countdown = 3;
                    const intervalId = setInterval(() => {
                        countdown--;
                        if (countdown <= 0) {
                            clearInterval(intervalId);
                            location.reload();
                        }
                    }, 1000);
                } else {
                    throw new Error('Server responded with an error');
                }
            })
            .catch(error => {
                console.error('Gagal menyimpan:', error);
                document.getElementById('errorMsg').classList.add('show');
            })
            .finally(() => {
                // Reset button state
                submitBtn.classList.remove('loading');
                submitBtn.disabled = false;
            });
        });

        // Add input validation for URL format
        document.getElementById('nodered').addEventListener('input', function() {
            const urlPattern = /^(http|https):\/\/[^ "]+$/;
            if (this.value && !urlPattern.test(this.value)) {
                this.setCustomValidity('Silakan masukkan URL yang valid (dimulai dengan http:// atau https://)');
            } else {
                this.setCustomValidity('');
            }
        });
    </script>
</body>
</html>
)rawliteral";