#include <SoftwareSerial.h> 
#include <DHT.h>
#include <math.h>
#define RX_PIN 10 
#define TX_PIN 11 
#define LED_PIN 13

//Do am & nhiet do
#define DHTPIN 2    
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 

//MQ2
int Gas_analog = A0;

//GPY2Y (bui pm2.5)
int measurePin = A2;
int ledPower = 6; 

//cac tham so de convert pm2.5 sang don vi ug/m3
int samplingTime = 280;
int deltaTime = 50;
int sleepingTime = 9680;
float voMesured = 0;
float calcVoltage = 0;
float dustDensisty = 0;

SoftwareSerial mySerial(RX_PIN, TX_PIN); 

float MQ2_getPPM(float voltage) {
  if (voltage <= 0 || voltage >= 5.0) {
    Serial.println("Error: Invalid voltage value.");
    return -1; 
  }

  const float RS_air = 10.0; 
  const float RL = 2.0;      
  const float B = -0.45;     
  const float M = -0.3;     

  float RS = ((5.0 / voltage) - 1.0) * RL;
  float ratio = RS / RS_air;

  if (ratio <= 0) {
    Serial.println("Error: Invalid ratio value.");
    return -1; // Return error value
  }
  float ppm = pow(10, ((log10(ratio) - B) / M));
  return ppm;
}

void setup() {
  Serial.begin(9600); 
  mySerial.begin(9600)
  pinMode(Gas_analog, INPUT);
  pinMode(ledPower, OUTPUT);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();    // Doc do am tu cam bien
  float t = dht.readTemperature(); // Doc nhiet do tu cam bien
  float f = dht.readTemperature(true);
  float gassensorAnalog = analogRead(Gas_analog);
  float voltage = gassensorAnalog * (5.0 / 1023.0);
  float ppm = MQ2_getPPM(voltage);

  //vi gia tri thiet lap khi co toi da tren matlab 23
  if (ppm > 23) {
    ppm = 22.9;
  }

  digitalWrite(ledPower, LOW);
  delayMicroseconds(samplingTime);

  voMesured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(sleepingTime);

  
  calcVoltage = voMesured * (5.0 / 1024.0);
  dustDensisty = (170 * calcVoltage - 0.1)/10 ;

  //vi gia tri thiet lap pm2.5 toi da tren matlab 70
  if (dustDensisty > 70) {
    dustDensisty = 69.9;
  }

  Serial.println(gassensorAnalog);
  Serial.println(voltage);
  Serial.println(ppm);

  String Data = String(t,1) + ";" + String(h,1) + ";" + String(ppm,1) + ";" + String(dustDensisty,1)+ ";";

  mySerial.println(Data); 
  Serial.println(Data);
  delay(1000);
}

