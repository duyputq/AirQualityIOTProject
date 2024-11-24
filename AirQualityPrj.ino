#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6BX-eeWqf"
#define BLYNK_TEMPLATE_NAME "powder"
#define BLYNK_AUTH_TOKEN "MqwtlkSnRYULJIC1FCNpPR8hVqtRvSgJ"
//dht
#define DHTPIN 4 //(D2)
#define DHTTYPE DHT11 // Dinh nghia loai cam bien DHT

#include <ESP8266WiFi.h>
#include <DHT.h>
#include <WiFiClient.h> 
#include <BlynkSimpleEsp8266.h>

char ssid[] = "smarthome";
char pass[] = "smarthome";

//gas sensor
int Gas_analog = A0;
int Gas_digital = 2; //(D4)

//motor
const int bb = 23;
const int pwmMotorA = D1;
const int dirMotorA = D3;
int motorSpeed = 100;
int button;

DHT dht(DHTPIN, DHTTYPE); //Set up cam bien nhiet do


void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(Gas_analog, INPUT);
  pinMode(Gas_digital, INPUT);
  pinMode(pwmMotorA, OUTPUT);
  pinMode(dirMotorA, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  delay(1000);
}

BLYNK_WRITE (V1)
{
  button = param.asInt();
  if (button ==1) {
    digitalWrite(pwmMotorA, motorSpeed);
    digitalWrite(dirMotorA, LOW);
  }
  else {
    digitalWrite(pwmMotorA, 0);
    digitalWrite(dirMotorA, LOW);
  }
}

void loop() {
  Blynk.run();
  float h = dht.readHumidity();    // Doc do am tu cam bien
  float t = dht.readTemperature(); // Doc nhiet do tu cam bien

  int gassensorAnalog = analogRead(Gas_analog);
  int gassensorDigital = digitalRead(Gas_digital);

  Serial.print("Do am: ");
  Serial.print(h);
  Serial.print("%");
  Serial.println();

  Serial.print("Nhiet do");
  Serial.print(t);
  Serial.print("°C");
  Serial.println();

  Serial.print("Nong do khi gas: "); //1-1024
  Serial.print(gassensorAnalog);
  Serial.println();

  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, h);
  Blynk.virtualWrite(V0, gassensorAnalog);

  // Serial.println("Kich hoat motor A quay trong 5s");
  // digitalWrite(pwmMotorA, motorSpeed);
  // digitalWrite(dirMotorA, LOW);
  // delay(5000);

  // Serial.println("Stop motor A trong 2s ");
  // digitalWrite(pwmMotorA, 0);
  // digitalWrite(dirMotorA, LOW);
  delay(1000);
}
