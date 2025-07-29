# 🕐 Mesin Absensi berbasis NodeMCU dan Web Dashboard

<div align="center">
  <img src="https://img.shields.io/badge/Platform-NodeMCU%20ESP8266-blue?style=for-the-badge" alt="Platform">
  <img src="https://img.shields.io/badge/Language-Arduino%20C++-green?style=for-the-badge" alt="Language">
  <img src="https://img.shields.io/badge/Dashboard-Node--RED-red?style=for-the-badge" alt="Dashboard">
</div>

## 📖 Deskripsi Proyek

Sistem absensi modern berbasis RFID menggunakan NodeMCU ESP8266 dengan web dashboard yang terintegrasi. Proyek ini memungkinkan pencatatan kehadiran secara otomatis menggunakan kartu RFID/NFC dan menyediakan antarmuka web untuk monitoring data absensi real-time.

### ✨ Fitur Utama

- 🔖 **Absensi RFID/NFC** - Sistem tap card untuk absen masuk/keluar
- 📱 **Web Dashboard** - Monitoring real-time melalui browser
- 🕒 **Sinkronisasi Waktu** - Otomatis sync dengan NTP server
- 📊 **Database Terintegrasi** - Penyimpanan data absensi
- 🔔 **Notifikasi Audio/Visual** - Buzzer dan LED indicator
- 📺 **Display LCD** - Informasi real-time di layar 20x4

## 🛠️ Komponen yang Dibutuhkan

### Hardware
| Komponen | Jumlah | Deskripsi |
|----------|--------|-----------|
| NodeMCU ESP8266 | 1 | Mikrokontroler utama |
| Cable USB A to USB Micro | 1 | Untuk programming dan power |
| PCB Board / Breadboard | 1 | Tempat rangkaian |
| LED | 1 | Indikator status |
| LCD I2C 20x4 | 1 | Display informasi |
| Buzzer | 1 | Notifikasi suara |
| RFID Reader RC522 | 1 | Pembaca kartu RFID |
| Jumper Cables | Secukupnya | Kabel penghubung |

### Software & Tools

#### 🔧 Development Tools
- **[Arduino IDE](https://www.arduino.cc/en/software)** - IDE untuk programming NodeMCU
- **[Driver CH340](https://www.arduined.eu/ch340-windows-10-driver-download/)** - Driver untuk komunikasi USB
- **[Node.js LTS](https://nodejs.org/en)** - Runtime JavaScript untuk Node-RED
- **[Node-RED](https://nodered.org/docs/getting-started/local)** - Penghubung NodeMCU dengan database
- **[MySQL](https://www.mysql.com/)** - Database server

#### 📚 Arduino Libraries
| Library | Fungsi |
|---------|--------|
| [LiquidCrystal_I2C](https://github.com/lucasmaziero/LiquidCrystal_I2C) | Kontrol LCD I2C |
| [MFRC522](https://github.com/miguelbalboa/rfid) | RFID reader interface |
| [ArduinoJson](https://github.com/bblanchon/ArduinoJson) | JSON parsing |
| [NTPClient](https://github.com/arduino-libraries/NTPClient) | Sinkronisasi waktu |
| [ESPAsyncWebServer](https://github.com/ESP32Async/ESPAsyncWebServer) | Web Server |
| [AsyncTCP](https://github.com/ESP32Async/AsyncTCP) | Koneksi TCP asinkron |

## 🔗 Skema Rangkaian

```
NodeMCU ESP8266 Pinout:
┌──────────────────────────┐
│ D1 │ D2 │ D3 │ D4  │ D5  |
│ D6 │ D7 │ D8 │ 3V3 │ GND |
└──────────────────────────┘

Koneksi:
• LCD I2C: SDA(D2), SCL(D1), VCC(3V3), GND(GND)
• RFID RC522: SDA(D4), SCK(D5), MOSI(D7), MISO(D6), RST(D3), VCC(3V3/5V), GND(GND)
• Buzzer/LED: Anoda(D8), Katoda(DNG)
```

## 🚀 Instalasi dan Setup

### 1. Persiapan Hardware
```
1. Rakit komponen sesuai skema rangkaian
2. Hubungkan NodeMCU ke komputer via USB
3. Pastikan driver CH340 terinstall
```

### 2. Setup Arduino IDE
```bash
1. Install Arduino IDE
2. Tambahkan board ESP8266:
   - File → Preferences → Additional Board Manager URLs
   - Masukkan: http://arduino.esp8266.com/stable/package_esp8266com_index.json
3. Install semua library yang dibutuhkan
```

### 3. Setup Server Environment
```bash
# Install Node.js dan Node-RED
npm install -g --unsafe-perm node-red
# Nyalakan Node-RED
node-red

# Install MySQL sebagai database
# - Windows
winget install MariaDB.Server
# - Debian/Ubuntu
sudo apt install mariadb -y
# - Fedora/RHEL/AlmaLinux
sudo dnf install mariadb -y
# Nyalakan MySQL
# - Windows
net start MariaDB
# - Debian/ubuntu/Fedora/RHEL/AlmaLinux
systemctl enable maridb --now
```

### 4. Upload Code
```bash
1. Buka project di Arduino IDE
2. Pilih board: NodeMCU 1.0 (ESP-12E Module)
4. Upload sketch ke NodeMCU
```

### 5. Setup Koneksi NodeMCU
```
1. Koneksikan ponsel/laptop ke wifi yang Berana "NodeMCU"
2. Masukkan password "12345678"
3. Buka Browser dan ketik "http://192.168.4.1"
4. Tunggu sampai tampilkan konfigurasi muncul
5. Masukkan semua informasi ke kolom yang disediakan kemudian klik "Simpan Konfigurasi"
```

## 📋 Penggunaan

### Menjalankan Sistem
1. **Power ON** - Nyalakan NodeMCU
2. **Koneksi WiFi** - Sistem akan connect otomatis
3. **Sinkronisasi** - Waktu akan tersinkronisasi dengan NTP
4. **Ready** - LCD menampilkan "Scan kartu"

### Absensi
1. **Tempelkan kartu RFID** ke reader
2. **Konfirmasi** - Buzzer berbunyi dan LED menyala
3. **Display** - LCD menampilkan informasi absensi
4. **Data tersimpan** - Otomatis masuk ke database

### Web Dashboard
1. Buka browser
2. Akses alamat IP Node-RED contoh: http://127.0.0.1:1880/ui
3. Monitor data absensi real-time
4. Export laporan jika diperlukan

## 🤝 Berkontribusi

Kontribusi sangat diterima! Silakan:

1. Fork repository ini
2. Buat branch fitur (`git checkout -b feature/AmazingFeature`)
3. Commit perubahan (`git commit -m 'Add some AmazingFeature'`)
4. Push ke branch (`git push origin feature/AmazingFeature`)
5. Buat Pull Request

## 📄 Lisensi

Proyek ini dilisensikan under MIT License - lihat file [LICENSE](LICENSE) untuk detail.

---

<div align="center">
  <b>⭐ Jangan lupa berikan star jika proyek ini bermanfaat! ⭐</b>
</div>
