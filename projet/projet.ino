#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  // Print a message to the LCD.
  lcd.setCursor(3,0);
  lcd.print("Welcome to");
  lcd.setCursor(3,1);
  lcd.print("VoltVault !");
}

void loop() {
  char key = customKeypad.getKey();
  if (key){
    lcd.clear();
    lcd.setCursor(0, 0); 
    if (key != NO_KEY) {
    if (key == '#') {              // if # is pressed, clear the LCD and display "Enter NIC"
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter NIC :");
      
      // read 8 digits from the keypad
      lcd.setCursor(0,1);
        char nicKey[9];
        int i = 0;
        while (i < 8) {
          char digit = customKeypad.getKey();
          if (digit != NO_KEY && isDigit(digit)) {
            lcd.print(digit);  // print the digit for a second
            delay(1000);
            lcd.setCursor(i, 1);
            lcd.print("*");    // print an asterisk instead of the digit
            nicKey[i++] = digit;
          }
        }
        nicKey[8] = '\0'; // terminate the nicKey array with null character
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Processing... ");
        //lcd.setCursor(0,1);
        //lcd.print(nicKey);
        delay(2000);
        Serial.print(nicKey);
        delay(2000);
        String message = "";
        while (Serial.available() > 0) 
        {
          char c = Serial.read();
          message += c;
        }

        // Print the message on the LCD
        delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        // Split the message into two parts
        int newlinePos = message.indexOf('\n');
        if (newlinePos != -1) {
          String greeting = message.substring(0, newlinePos);
          String credit = message.substring(newlinePos + 1);

           // Print the two parts on separate lines on the LCD
          lcd.print(greeting);
          lcd.setCursor(0, 1);
          lcd.print(credit); 
          
         }
    }
         else if (key == '*') {   //if * is pressed, clear the LCD and ask for credit
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("How much ?");
            lcd.setCursor(0,1);
            char credit[5];
            credit[0]='#';
            int j = 1;
            while (j < 4) { 
              char digit = customKeypad.getKey();
              if (digit != NO_KEY && isDigit(digit)) {
                lcd.print(digit);  // print the digit for a second
                delay(1000);
                credit[j++] = digit;
                lcd.setCursor(j-1, 1);
              }
            }
            credit[4] = '\0'; // terminate the credit array with null character
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Processing... ");
            delay(2000);
            Serial.print(credit);
            delay(2000);
            String rest = "";
            while (Serial.available() > 0) 
            {
              char d = Serial.read();
              rest += d;
            }
    
            // Print the message on the LCD
            delay(2000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Done!");
            lcd.setCursor(0,1);
            lcd.print(rest);
            delay(5000);
            lcd.clear();
            lcd.setCursor(3,0);
            lcd.print("Welcome to");
            lcd.setCursor(3,1);
            lcd.print("VoltVault !");

        
    }
  }
}
}
