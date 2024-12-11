#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>

// Konfigurasi WiFi
const char* ssid = "Nvr";
const char* password = "abcdefgh";

// Konfigurasi Server Database
const char* serverName = "http://192.168.54.178/absensi/get_data.php";

// Pin Konfigurasi
#define RST_PIN D1
#define SS_PIN D2

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variabel Global
WiFiClient client;
HTTPClient http;
unsigned long lastTime = 0;
unsigned long timerDelay = 5000; // Interval pengiriman data (5 detik)

void setup() {
  Serial.begin(115200);
  
  // Konfigurasi I2C
  Wire.begin(D3, D4); // SDA -> D3, SCL -> D4
  
  // Inisialisasi LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Connecting WiFi");

  // Koneksi WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Terhubung ke WiFi. IP: ");
  Serial.println(WiFi.localIP());
  
  // Inisialisasi RFID
  SPI.begin(); 
  rfid.PCD_Init(); 
  
  lcd.clear();
  lcd.print("Siap Absensi");
}

bool kirimDataAbsensi(String uid) {
  if(WiFi.status() == WL_CONNECTED) {
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Buat payload untuk dikirim
    String postData = "uid=" + uid;
    
    int httpResponseCode = http.POST(postData);
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Server Response: " + response);
      
      // Parse JSON response
      DynamicJsonDocument doc(256);
      DeserializationError error = deserializeJson(doc, response);
      
      if (!error) {
        // Ekstrak data dari JSON
        const char* nama = doc["nama"] | "Tidak Dikenal";
        const char* status = doc["status"] | "Gagal";
        
        // Tampilkan di LCD
        lcd.clear();
        lcd.print(nama);
        lcd.setCursor(0, 1);
        lcd.print(status);
        
        return true;
      }
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
      
      lcd.clear();
      lcd.print("Koneksi Error");
    }
    
    http.end();
  }
  return false;
}

void loop() {
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