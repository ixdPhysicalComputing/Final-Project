#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

const int rPin = 5;
const int gPin = 10;
const int bPin = 3;

const int sdaPin = A4;
const int sclPin = A5;

int counter, red, green, blue;
int s = 5;
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
  }
  
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  counter = 0; red = 0; green = 0; blue = 0;
}

void loop() {
  
  DateTime now = RTC.now();
   if(Serial.available()) {
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    to2digits(now.day());
    Serial.print(' ');
    to2digits(now.hour());
    Serial.print(':');
    to2digits(now.minute());
    Serial.print(':');
    to2digits(now.second());
    Serial.println();
  }
//  if (Serial.available()) {
//
//  }
  if (now.unixtime() > 1417479300) {
    risingSun();
  }
}

void sunRose() {
  counter = 0; red = 0; green = 0; blue = 0;
}

void risingSun() {
//  counter = 0; red = 0; green = 0; blue = 0;
  if (counter > t1 && red < x) {
    red = (counter - t1) / s;
  }
  if (counter > t2 && green < x) {
    green = (counter - t2) / (s * 1.5);
  }
  if (counter > t3 && blue < y) {
    blue = (counter - t3) / s;
  }
  if (Serial.available()) {
    Serial.print("Red: ");
    Serial.println(red);
    Serial.print("Green: ");
    Serial.println(green);
    Serial.print("Blue: ");
    Serial.println(blue);
  }
  analogWrite(rPin, red);
  analogWrite(bPin, blue);
  analogWrite(gPin, green);
  
  counter++;
  delay(s);
}

void to2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

void dateCheck() {
  const int newDates[] = { 1, 2, 3 };
}
