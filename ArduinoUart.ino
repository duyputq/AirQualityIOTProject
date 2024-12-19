#include <SoftwareSerial.h> // Thư viện cho cổng nối tiếp mềm
#include <DHT.h>
#define RX_PIN 10 // Chân RX của cổng nối tiếp mềm
#define TX_PIN 11 // Chân TX của cổng nối tiếp mềm
#define LED_PIN 13 // Chân kết nối với led

#define DHTPIN 2    // Dinh nghia chan ket noi voi cam bien DHT
#define DHTTYPE DHT11 // Dinh nghia loai cam bien DHT
DHT dht(DHTPIN, DHTTYPE); //Set up cam bien nhiet do

int Gas_analog = A0;
int Gas_digital = 4; //(D2)


int measurePin = A2;
int ledPower = 6; //(D6)

int samplingTime = 280;
int deltaTime = 50;
int sleepingTime = 9680;
float voMesured = 0;
float calcVoltage = 0;
float dustDensisty = 0;

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Tạo một đối tượng cổng nối tiếp mềm

void setup() {
  Serial.begin(9600); // Khởi tạo cổng nối tiếp cứng với tốc độ baud là 9600
  mySerial.begin(9600); // Khởi tạo cổng nối tiếp mềm với tốc độ baud là 9600
  pinMode(Gas_analog, INPUT);
  pinMode(Gas_digital, INPUT);
  pinMode(ledPower, OUTPUT);
  // pinMode(LED_PIN, OUTPUT); // Đặt chân kết nối với led là chân đầu ra
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();    // Doc do am tu cam bien
  float t = dht.readTemperature(); // Doc nhiet do tu cam bien
  float f = dht.readTemperature(true);
  float gassensorAnalog = analogRead(Gas_analog);
  float voltage = gassensorAnalog * (5.0 / 1023.0);
  float ppm = MQ2_getPPM(voltage);
  int gassensorDigital = digitalRead(Gas_digital);
  
    // Nếu có dữ liệu từ cổng nối tiếp cứng, gửi nó sang cổng nối tiếp mềm
  // Serial.println(h);
  // delay(1000);
  // voMesured = analogRead(measurePin);
  // calcVoltage = voMesured * (5.0 / 1024.0);
  // dustDensisty = 170 * calcVoltage - 0.1;

  // digitalWrite(ledPower, LOW);
  // delay(1000);
  // digitalWrite(ledPower, HIGH);
  // Serial.println(voMesured);
  // Serial.println(dustDensisty);

  digitalWrite(ledPower, LOW);
  delayMicroseconds(samplingTime);

  voMesured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(sleepingTime);

  calcVoltage = voMesured * (5.0 / 1024.0);
  dustDensisty = (170 * calcVoltage - 0.1)/10;

  Serial.println(dustDensisty);

  String Data = String(t,1) + ";" + String(h,1) + ";" + String(ppm,1) + ";" + String(dustDensisty,2)+ ";";

  mySerial.println(Data); 
  Serial.println(Data);
  delay(1000);

}

float MQ2_getPPM(float voltage) {
  // Calibration curve parameters (adjust based on your sensor and gas)
  float RS_air = 10.0; // Sensor resistance in clean air (in kilo ohms)
  float RL = 2.0; // Load resistance (in kilo ohms)
  float ratio = RL / RS_air; // Ratio of RL to RS_air
 
  // Calculate sensor resistance (RS) in kilo ohms
  float RS = ((5.0 / voltage) - 1.0) * RL;
 
  // Calculate gas concentration (PPM) using the derived formula (adjust based on calibration)
  float ppm = 1.0 * pow((RS / RS_air), ratio); // Gas concentration in parts per million (PPM) //goc 1000
 
  return ppm;
}