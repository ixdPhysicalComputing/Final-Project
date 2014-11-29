#include <Adafruit_NeoPixel.h>


#define PIN            6
#define NUMPIXELS      12

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11 

DHT dht(2, DHT11);

int dirtSensor = A0;
int sunSensor = A2;

int ledPin1 = 13;
int ledPin2 = 11;
int ledPin3 = 9;


int dirtSensorVal = 0;
int sunSensorVal = 0;
int tempSensorVal = 0;

int DirtThreshold = 500;
int SunThreshold = 255;
int TempThreshold = 73.50;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayVal = 150;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(dirtSensor, INPUT);
  pinMode(sunSensor, INPUT);
  
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  
  pixels.begin(); 
  dht.begin();
}

void loop () { 
  float dirt = analogRead(dirtSensor);
  //dirtSensorVal = analogRead(dirtSensor);
  float sun = analogRead(sunSensor);
  //sunSensorVal = analogRead(sunSensor);
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  
  Serial.print("Dirt: ");
  Serial.print(dirt);
  Serial.print(" \t");
  Serial.print("Sun: ");
  Serial.print(sun);
  Serial.print(" \t");
  
  float index = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(index);
  Serial.println(" *F");
  
 if (dirt > DirtThreshold) {
   for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
   pixels.setPixelColor(i, pixels.Color(20,125,0)); // Moderately bright green color.
   pixels.show(); // This sends the updated pixel color to the hardware.
   delay(delayVal);
     }
   for(int i=0;i<NUMPIXELS;i++){
   pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
   pixels.show(); // This sends the updated pixel color to the hardware.
   delay(delayVal);
      }
 } 
 
if(sun < SunThreshold) {
     for(int i=0;i<NUMPIXELS;i++){
// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(250,250,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal);
     }
for(int i=0;i<NUMPIXELS;i++){
// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
pixels.show(); // This sends the updated pixel color to the hardware.
delay(delayVal);
}
}

if(index < TempThreshold) {
     for(int i=0;i<NUMPIXELS;i++){
// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,35,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal);
     }
for(int i=0;i<NUMPIXELS;i++){
// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
pixels.show(); // This sends the updated pixel color to the hardware.
delay(delayVal);
}
}
}
