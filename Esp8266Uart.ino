#include <SoftwareSerial.h>
#include <iostream>
#include <string>
#include <iomanip>

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6BX-eeWqf"
#define BLYNK_TEMPLATE_NAME "powder"
#define BLYNK_AUTH_TOKEN "MqwtlkSnRYULJIC1FCNpPR8hVqtRvSgJ"
// Khai báo các chân RX và TX cho espsoftwareserial
#define RX_PIN 4 // D2
#define TX_PIN 5 // D1

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <BlynkSimpleEsp8266.h>

const int pwmMotorA = D1;
const int dirMotorA = D3;
int motorSpeed = 100;
int button;

//LED
int LED = D5;
int LED1 = D6;
int LED2 = D7; 
s

char ssid[] = "smarthome";
char pass[] = "smarthome";

// Tạo một đối tượng espsoftwareserial với tốc độ baud là 9600
SoftwareSerial mySerial(RX_PIN, TX_PIN);

String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
      if (data.charAt(i) == separator || i == maxIndex) {
          found++;
          strIndex[0] = strIndex[1] + 1;
          strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() {
  // Khởi tạo cổng nối tiếp phần cứng với tốc độ baud là 115200
  Serial.begin(9600);

  // Khởi tạo cổng nối tiếp phần mềm với tốc độ baud là 9600
  mySerial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // In ra thông báo khởi động
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
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
  if (mySerial.available()) { // Nếu có dữ liệu từ cổng nối tiếp mềm
    String data = mySerial.readString(); // Đọc chuỗi dữ liệu
    Serial.println(data); // In ra chuỗi dữ liệu
    String value1 = getValue(data, ';', 0); // Tách phần tử thứ 0 theo ký tự phân cách ';'
    String value2 = getValue(data, ';', 1); // Tách phần tử thứ 1 theo ký tự phân cách ';'
    String value3 = getValue(data, ';', 2); // Tách phần tử thứ 2 theo ký tự phân cách ';'
    String value4 = getValue(data, ';', 3); // Tách phần tử thứ 2 theo ký tự phân cách ';'
    // String blankvalue = getValue(data, ';', 4); // Tách phần tử thứ 2 theo ký tự phân cách ';'
    
    Blynk.virtualWrite(V2, value1);
    Blynk.virtualWrite(V3, value2);
    Blynk.virtualWrite(V4, value3);
    Blynk.virtualWrite(V5, value4);

    Serial.println("Nhiet do: "+value1 + "*C"); // In ra phần tử thứ 0
    Serial.println("Do am: "+value2 + "%"); // In ra phần tử thứ 1
    Serial.println("Nong do CO: "+value3 +" ppm"); // In ra phần tử thứ 1
    Serial.println("Mat do bui min PM2.5: "+value4 + " ug/m3");
    // Serial.println(value4); // In ra chuỗi dữ liệu
    double n3 = value3.toDouble();
    double n4 = value4.toDouble();
    if(n4 > 55.5 || n3 > 11){
      digitalWrite(LED1, LOW);   // Tắt LED
      digitalWrite(LED2, LOW);   // Tắt LED
      digitalWrite(LED, HIGH);  // Bật LED do
      digitalWrite(pwmMotorA, motorSpeed);
      digitalWrite(dirMotorA, LOW);
    } else if (n4 < 12 || n3 < 4.4){
       digitalWrite(LED, LOW);   // Tắt LED
       digitalWrite(LED1, LOW);   // Tắt LED
      digitalWrite(LED2, HIGH);  // Bật LED xanh
      if (button != 1){
        digitalWrite(pwmMotorA, 0);
        digitalWrite(dirMotorA, LOW);
      }
    } else {
      digitalWrite(LED, LOW);   // Tắt LED
      digitalWrite(LED2, LOW);   // Tắt LED
      digitalWrite(LED1, HIGH);  // Bật LED vang
    }
  
  }
}
