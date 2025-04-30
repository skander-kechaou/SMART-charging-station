#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define contrast 8
#define SS_PIN 10
#define RST_PIN 9

String msg;
String a;
int i;

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  
  Serial.begin(9600);//initialize the serial link to 9600 bauds 
  lcd.begin();       //initiate the lcd 
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop() {

    lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Put your card ");
  lcd.setCursor(5, 1);
  lcd.print("for 3s");
  delay(300);
 lcd.clear();
 
  String recu = "0";
//  if data has been received 
if (Serial.available() > 0)
  {
    //read the incoming data from the serial port (arduino)
    a = Serial.readString();
   
    if(a.compareTo("0") != 0 )
    {
            lcd.clear();
            lcd.print(a);
            delay(10000);
    }
   
  }
 // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
 
String content= "";
String msg = "";
  byte letter;
  //concatenate data read from the arduino
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }


  content.toUpperCase();
 
msg =content+"#";

  //send the data to the serial port (arduino)
 for(i=0;i<msg.length();i++)
    {
       Serial.write(msg[i]);
        delay (100);
       
    }
   

}
