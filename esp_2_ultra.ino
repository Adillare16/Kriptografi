#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "tes";
const char* password = "12345678";

// ⚠️ GANTI INI DENGAN IP ESP1
String esp1 = "http://192.168.1.25/tutup";

#define TRIG 5
#define ECHO 18

bool aktif = false;

void setup() {

  Serial.begin(115200);

  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);

  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nESP2 READY");
}

float jarak(){

  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG,LOW);

  long d = pulseIn(ECHO,HIGH,30000);

  if(d==0) return 999;

  return d*0.034/2;
}

void loop() {

  float j = jarak();

  Serial.print("Jarak: ");
  Serial.println(j);

  // mobil masuk
  if(j < 20){
    aktif = true;
  }

  // mobil sudah lewat → tutup
  if(aktif && j > 20){

    Serial.println("KIRIM TUTUP");

    if(WiFi.status()==WL_CONNECTED){

      HTTPClient http;
      http.begin(esp1);

      int code = http.GET();

      Serial.print("HTTP: ");
      Serial.println(code);

      http.end();
    }

    aktif = false;
  }

  delay(300);
}