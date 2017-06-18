// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
// mod by fama for servo meter, DC FAN, LCD

#include "DHT.h"
#include <LiquidCrystal.h>
#include <Servo.h> 

#define DHTPIN 11     // what pin we're connected to

// Uncomment whatever type you're using! 
#define DHTTYPE DHT11   // DHT 11 
// #define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
Servo myservo; 
Servo myservo2;
int motorPin = 3;

LiquidCrystal lcd(13, 12, 16, 17, 18, 19); //pins for LCD display

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  lcd.clear();
  lcd.print("DHT11 - Super");
  dht.begin();
   myservo.attach(9);
   myservo2.attach(8);
   pinMode(motorPin, OUTPUT);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
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

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: ");
  lcd.print("Humidade: "); 
  Serial.print(h);
  Serial.print(" %\t");
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(h);
  lcd.print(" h");
  lcd.print(t);
  lcd.print(" *c");
  lcd.setCursor(1,1);
  lcd.print(f);
  lcd.print(" *f");
  
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
  myservo.write(90);

  if (t > 30) 
  {
    myservo.write(10);
    digitalWrite(motorPin, HIGH);
  }
  
  if (t < 29) 
  {
    myservo.write(140);
   digitalWrite(motorPin, LOW); 
  }

  if (t < 27)
  {
    myservo.write(180);
    
  }
  
  

//  myservo2.write(90);
//  if (h > 50) myservo2.write(10);
//  else
//  if (h <50) myservo2.write(180);
  
}
