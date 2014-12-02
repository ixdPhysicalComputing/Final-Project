#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

const int rPin = 5;
const int gPin = 10;
const int bPin = 3;

const int sdaPin = A4;
const int sclPin = A5;

const unsigned long fd = 1417478400;
const unsigned long d = 86400;
unsigned long td = fd - d;
unsigned long nd = fd;
unsigned long dateRoll[30];
unsigned long sunriseTime[30] = {
  1417516200,// 1417503720 is true for 12/2; 1417516200 is 10:30 am
  1417590180,
  1417676640,
  1417763100,
  1417849560,
  1417935960,
  1418022420,
  1418108880,
  1418195340,
  1418281800,
  1418368260,
  1418454660,
  1418541120, //12/14
  1418627580,
  1418714040,
  1418800440,
  1418886900,
  1418973300,
  1419059760,
  1419146220,
  1419232620,
  1419319020,
  1419405480,
  1419491880,
  1419578340,
  1419664740,
  1419751140,
  1419837600,
  1419924000,
  1420010400
};

int today;
unsigned long counter;
int red, green, blue;

int s = 1; // delay means we don't need 1000
int f = 9;

unsigned long t1 = 2 * s;
unsigned long t2 = 12 * s;
unsigned long t3 = 36 * s;
unsigned long tf = 120 * 60 * s;

int x = 255;
int y = 64;

void setup() {
  Serial.begin(115200);
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
  unsigned long ud = now.unixtime();
  
  today = (ud/td) - 1;
  
  if (ud > nd) {
    checkDate(today);
  }
  
  if(Serial.available()) {
    Serial.print("Date number: ");
    Serial.println(today);
    Serial.print("Today: ");
    Serial.println(dateRoll[today]);
    Serial.print("Time now: ");
    Serial.println(ud);
    Serial.print("Sunrise today: ");
    Serial.println(sunriseTime[today]);
    Serial.print("Red: ");
    Serial.println(red);
    Serial.print("Green: ");
    Serial.println(green);
    Serial.print("Blue: ");
    Serial.println(blue);
    Serial.print("Counter: ");
    Serial.println(counter);
  }
  
  if ( (ud > sunriseTime[today]) && (counter < tf) ) {
    risingSun();
  } else {
    sunRose();
  }
  
  delay(1000);
}

void checkDate(int dateToCheck) {
  counter = 0;
  nd += d;
  td += d;
  
  for (int i = 0; i < 30; i++) {
    dateRoll[i] = fd + (d * i);
  }
}

void risingSun() {
//  counter = 0; red = 0; green = 0; blue = 0;
  if (counter > t1 && red < x) {
    red = (counter - t1) / f;
  }
  if (counter > t2 && green < x) {
    green = (counter - t2) / (f * 1.5);
  }
  if (counter > t3 && blue < y) {
    blue = (counter - t3) / f;
  }
  analogWrite(rPin, red);
  analogWrite(bPin, blue);
  analogWrite(gPin, green);
  
  counter++;
}

void sunRose() {
  red = 0; green = 0; blue = 0;
  analogWrite(rPin, red);
  analogWrite(bPin, blue);
  analogWrite(gPin, green);
}

void to2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
