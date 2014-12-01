#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;



const int rPin = 5;
const int gPin = 10;
const int bPin = 3;

const int lowOut = A2;
const int highOut = A3;
const int sdaPin = A4;
const int sclPin = A5;

int m, red, green, blue;
int s = 10;
int t1 = 100;
int t2 = 500;
int t3 = 1000;
int x = 255;
int y = 64;

void setup() {
  Serial.begin(57600);
  Wire.begin();
  RTC.begin();
  
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  pinMode(lowOut, OUTPUT);
  pinMode(highOut, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  
  m = 0;
  red = 0;
  green = 0;
  blue = 0;
  

}

void loop() {
  digitalWrite(lowOut, LOW);
  digitalWrite(highOut, HIGH);
  m++; // = millis();
  if (Serial.available()) {
     Serial.print("Time: ");
     Serial.println(m);
    }
  if (m > t1) {
//    for (r = 0; 
    red = (m - t1) / s;
    if (Serial.available()) {
     Serial.print("Red: ");
     Serial.println(red);
    }
    if (red > x) { red = x; }
  }
  if (m > t2) {
    green = (m - t2) / (s * 1.5);
    if (Serial.available()) {
     Serial.print("Green: ");
     Serial.println(green);
    }
    if (green > x) { green = x; }
  }
  if (m > t3) {
    blue = (m - t3) / s;
    if (Serial.available()) {
     Serial.print("Blue: ");
     Serial.println(blue);
    }
    if (blue > y) { blue = y; }
  }
  analogWrite(rPin, red);
  analogWrite(bPin, blue);
  analogWrite(gPin, green);
  delay(s);
}
