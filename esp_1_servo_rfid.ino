#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#include <WebServer.h>

// WIFI
const char* ssid = "tes";
const char* password = "12345678";

// XAMPP IP
String serverName =
"http://10.78.169.163/rfid_project/cek_rfid.php?uid=";

// RFID
#define SS_PIN 5
#define RST_PIN 27
MFRC522 rfid(SS_PIN, RST_PIN);

// SERVO
Servo gate;
#define SERVO_PIN 13

// SERVER ESP1 (untuk ESP2)
WebServer server(80);

// anti spam RFID
unsigned long lastScan = 0;

// ===== TUTUP dari ESP2 =====
void tutup() {
  Serial.println("REQUEST TUTUP MASUK");
  gate.write(0);
  server.send(200,"text/plain","OK");
}

void setup() {

  Serial.begin(115200);

  SPI.begin(18,19,23,5);
  rfid.PCD_Init();

  gate.attach(SERVO_PIN);
  gate.write(0);

  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nESP1 READY");
  Serial.println(WiFi.localIP());

  server.on("/tutup",tutup);
  server.begin();
}

void loop() {

  server.handleClient();

  if(!rfid.PICC_IsNewCardPresent()) return;
  if(!rfid.PICC_ReadCardSerial()) return;

  if(millis()-lastScan < 3000) return;
  lastScan = millis();

  String uid="";

  for(byte i=0;i<rfid.uid.size;i++){
    uid += String(rfid.uid.uidByte[i],HEX);
  }

  uid.toUpperCase();

  if(uid.length()==0) return;

  String url = serverName + uid;

  Serial.println("URL: " + url);

  HTTPClient http;
  http.begin(url);

  int code = http.GET();
  String res = http.getString();

  http.end();

  Serial.println("RESP: " + res);

  if(res == "OK"){
    gate.write(90);   // BUKA PALANG
  }
}