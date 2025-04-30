#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int motionPin = 7;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal_I2C lcd(0x27, 16,2);

void setup() {
  Serial.begin(9600);
  pinMode(motionPin, INPUT);
  // Set up the LCD's number of columns and rows
  lcd.begin();
  // Print a welcome message on the LCD
  lcd.setCursor(1, 0);
  lcd.print("Smart Charging");
  lcd.setCursor(4, 1);
  lcd.print("Station");
  // Wait for a moment
}

void loop() {
  // Read any incoming data from the serial port
  
    String incomingData="";
    // Read the data and print it on the LCD
    while(Serial.available() )
    {
      char c=Serial.read();
      incomingData +=c;
    }
    
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print(incomingData);
    delay(5000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Smart Charging");
    lcd.setCursor(4, 1);
    lcd.print("Station");   
    

  if (digitalRead(motionPin) == HIGH)
   {
    lcd.setCursor(1, 0);
    lcd.print("Smart Charging");
    lcd.setCursor(4, 1);
    lcd.print("Station");
    Serial.print("@");
    delay(1000);
    
    
   }
  
}
