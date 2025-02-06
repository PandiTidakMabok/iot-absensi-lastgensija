#include "require.h"

WiFiUDP ntpUDP;
WiFiClient client;
HTTPClient http;
HTTPClient http2;
ESP8266WebServer web(80);
Config config;

// NTP Client untuk waktu
NTPClient timeClient(ntpUDP, ntpServer, ntpOffset);  // Menambahkan 7 jam untuk WIB (UTC+7)

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variabel Global
unsigned long lastTime = 0;
unsigned long displayUpdateInterval = 1000;  // Update tampilan setiap 1 detik
unsigned long lastDisplayUpdate = 0;

void loadConfig() {
  EEPROM.get(0, config);
  // set default value
  if (strlen(config.ssid) == 0) {
    strcpy(config.ssid, "Grendel International");
    strcpy(config.password, "");
    strcpy(config.phpserver, "http://192.168.20.250/absensi/get_data.php");
    strcpy(config.nodered, "http://192.168.20.250:1880/absensi");
  }
}

void webConfig() {
  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    web.send(500, "text/plain", "File Not Found");
    return;
  }
  web.streamFile(file, "text/html");
  file.close();
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  loadConfig();
  LittleFS.begin();
  // Konfigurasi I2C
  Wire.begin(D3, D4);  // SDA -> D3, SCL -> D4

  // Inisialisasi LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Connecting WiFi");

  // Koneksi WiFi
  WiFi.begin(config.ssid, config.password);
  Serial.println("Connecting");
  unsigned long startAttempt = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 10000) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.softAP("NodeMCU", "12345678");
  } else {
    Serial.println("");
    Serial.print("Terhubung ke WiFi. IP: ");
  }

  Serial.println(WiFi.localIP());

  // Inisialisasi NTP Client
  timeClient.begin();

  // Inisialisasi RFID
  SPI.begin();
  rfid.PCD_Init();

  lcd.clear();
  web.begin();
  web.on("/", HTTP_GET, webConfig);
}

// Fungsi untuk mendapatkan nama hari dalam bahasa Indonesia
String getNamaHari(int dayOfWeek) {
  switch (dayOfWeek) {
    case 0: return "Minggu";
    case 1: return "Senin";
    case 2: return "Selasa";
    case 3: return "Rabu";
    case 4: return "Kamis";
    case 5: return "Jumat";
    case 6: return "Sabtu";
    default: return "Error";
  }
}

// Fungsi untuk menampilkan waktu dan tanggal di LCD
void displayTimeAndDate() {
  timeClient.update();

  // Dapatkan waktu dan tanggal
  time_t epochTime = timeClient.getEpochTime();
  struct tm* ptm = localtime(&epochTime);

  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  int currentSecond = timeClient.getSeconds();

  int currentDay = ptm->tm_mday;          // Hari dalam bulan
  int currentMonth = ptm->tm_mon + 1;     // Bulan (1-12)
  int currentYear = ptm->tm_year + 1900;  // Tahun

  String namaHari = getNamaHari(timeClient.getDay());  // 0-6 (Minggu-Sabtu)

  // Format waktu dan tanggal
  char timeStr[6];
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d", currentHour, currentMinute);

  // Tampilkan di LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(timeStr);
  lcd.setCursor(7, 0);
  lcd.print(namaHari);

  lcd.setCursor(0, 1);
  lcd.printf("%02d/%02d/%d", currentDay, currentMonth, currentYear);
}

bool kirimDataAbsensi(String uid) {
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(client, config.phpserver);
    http2.begin(client, config.nodered);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http2.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Buat payload untuk dikirim
    String postData = "uid=" + uid;

    // Debug: Tampilkan UID yang dikirim ke Node-RED
    Serial.print("Sending UID to Node-RED: ");
    Serial.println(uid);

    // Kirim data ke Node-RED
    int httpResponseCode = http2.POST(postData);
    if (httpResponseCode > 0) {
      String response = http2.getString();
      Serial.println("Node-RED Response: " + response);

      // Parse JSON response dari Node-RED
      DynamicJsonDocument doc(256);
      DeserializationError error = deserializeJson(doc, response);

      if (!error) {
        // Ekstrak data dari JSON
        const char* status = doc["status"] | "Gagal";

        if (strcmp(status, "success") == 0) {
          const char* nama = doc["nama"] | "Murid";
          const char* kelas = doc["kelas"] | "";
          const char* status_absen = doc["status_absen"] | "";

          // Dapatkan waktu saat ini
          timeClient.update();
          int currentHour = timeClient.getHours();
          int currentMinute = timeClient.getMinutes();

          // Tampilkan di LCD
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(nama);
          lcd.setCursor(0, 1);
          lcd.printf("%s %02d:%02d", status_absen, currentHour, currentMinute);

          // Tahan tampilan selama 3 detik
          delay(3000);

          return true;
        } else {
          lcd.clear();
          lcd.print("Absensi Gagal");
          delay(2000);
        }
      }
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);

      lcd.clear();
      lcd.print("Koneksi Error");
      delay(2000);
    }

    http.end();
    http2.end();
  }
  return false;
}

void loop() {
    web.handleClient();
  // Update waktu secara berkala
  if (millis() - lastDisplayUpdate >= displayUpdateInterval) {
    displayTimeAndDate();
    lastDisplayUpdate = millis();
  }

  // Cek apakah ada kartu RFID
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Ambil UID dari kartu RFID
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  // Tampilkan UID di Serial Monitor
  Serial.print("UID Card: ");
  Serial.println(uid);

  // Kirim data ke server
  kirimDataAbsensi(uid);

  // Tunggu sebelum membaca kartu lagi
  delay(2000);
  rfid.PICC_HaltA();
}
