#include <DHT.h>

//dht
#define DHTPIN 4 //(D2)
#define DHTTYPE DHT11 // Dinh nghia loai cam bien DHT

//gas sensor
int Gas_analog = A0;
int Gas_digital = 2; //(D4)

//motor
const int bb = 23;
const int pwmMotorA = D1;
const int dirMotorA = D3;
int motorSpeed = 100;

DHT dht(DHTPIN, DHTTYPE); //Set up cam bien nhiet do


void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(Gas_analog, INPUT);
  pinMode(Gas_digital, INPUT);
  pinMode(pwmMotorA, OUTPUT);
  pinMode(dirMotorA, OUTPUT);
  delay(1000);
}

void loop() {
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

  Serial.println("Kich hoat motor A quay trong 5s");
  digitalWrite(pwmMotorA, motorSpeed);
  digitalWrite(dirMotorA, LOW);
  delay(5000);

  Serial.println("Stop motor A trong 2s ");
  digitalWrite(pwmMotorA, 0);
  digitalWrite(dirMotorA, LOW);
  delay(2000);
}
