#include "LiquidCrystal.h"
// POWERTIP LCD PC1602 - H
// LiquidCrystal display with:
// rs lcd  pin 4 on arduino pin 12
// rw lcd pin 5 on arduino pin 11
// enable lcd  pin 6 arduino on pin 10
// d4,d5,d6,d7 lcd pins 11, 12, 13, 14 on arduino pins 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

int sensorPin = A0; //the analog pin the TMP36's Vout (sense) pin is connected to
int sensorPin2 = A1;
int backlightPin = 6;
int buttonpin = 7;

//the resolution is 10 mV / degree centigrade with a
//500 mV offset to allow for negative temperatures
float voltsPerDegree = 0.02; // change to 0.01 for TMP35 & 36
 
int wait=1000;
int val=0;
void setup()
{
    Serial.begin(9600); //Start the serial connection with the computer
    
    pinMode(backlightPin,OUTPUT); 
    pinMode(buttonpin,INPUT);
  
    // Print a message to the LCD.
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    
    digitalWrite(backlightPin, HIGH);
    lcd.print("Welcome! Loading...");
    lcd.setCursor(0,1);
    lcd.print("Bklt on w/ btn.");
    delay(2500);
    digitalWrite(backlightPin, LOW);
    
}
 
void loop()
{
    int sensorValue;
    int sensorValue2;
    float volts;
    float celsius;
    float farenheit;
    float volts2;
    float celsius2;
    float farenheit2;
    boolean val = 0;
    
    //getting the voltage reading from the temperature sensor
    sensorValue = analogRead(sensorPin);
    sensorValue2 = analogRead(sensorPin2);
    
    // converting that reading to voltage, for 3.3v arduino use 3.3
    volts = sensorValue * 5.0 / 1024.0;
    volts2 = sensorValue2 * 5.0 / 1024.0;
    
    celsius = (sensorValue * 5.0 / 1024.0) / voltsPerDegree;
    celsius2 = (sensorValue2 * 5.0 / 1024.0) / voltsPerDegree;

    // now convert to Fahrenheit
    farenheit = (((sensorValue * 5.0 / 1024.0) / voltsPerDegree)  * 9.0 / 5.0) + 32;
    farenheit2 = (((sensorValue2 * 5.0 / 1024.0) / voltsPerDegree)  * 9.0 / 5.0) + 32;
    Serial.print(farenheit); Serial.println(" F");
    Serial.print(farenheit2); Serial.println(" F");
    
    // set the cursor to column 8, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    // print the number of seconds since reset:
    lcd.setCursor(0, 0);
    lcd.print("Room Temp: ");
    lcd.print(farenheit);
    lcd.print("F");
    lcd.setCursor(0, 1);
    lcd.print("Frdg Temp: ");
    lcd.print(farenheit2);
    lcd.print("F");

    val = digitalRead(buttonpin);     
    if(val == HIGH) {
        digitalWrite(backlightPin, HIGH);
        delay(5000);
        digitalWrite(backlightPin, LOW);
    } else {
        delay(50);
    }
}
 
// rs on pin 12
// rw on pin 11
