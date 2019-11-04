//Include wire library, which allows communication with I2C Devices.
#include <Wire.h> 
//Include the library that enables you to use LCD
#include <LiquidCrystal_I2C.h>
//Declare what the LCD screen is connected to 
LiquidCrystal_I2C lcd(0x27,20,4);  // LCD2004 - 20x4 are the dimensions of the LCD

//Define Pins & Constants
int pinA = 3;   //CLK
int pinB = 4;    //DT
int encoderCount;
int pinAlast;  
int aVal;
boolean CWCheck;


void setup() {
  //Initialise and Start LCD Screen
  lcd.init();
  lcd.backlight();
  lcd.print("Start LCD...");

  //Configure Pins for KY-040
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  //Read Last Encoder Value
  pinAlast = digitalRead(pinA);

  //Begin process of receiving serial data
  Serial.begin (9600);

  //Delay & Clear LCD
  delay(1000);
  lcd.clear();    
  
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Reading Encoder..");
  
  aVal = digitalRead(pinA); //Read Current Encoder Value
  
  if (aVal != pinAlast){
    if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
       encoderCount ++;
       CWCheck = true;
     } else {// Otherwise B changed first and we're moving CCW
       CWCheck = false;
       encoderCount--;
     } 
     
     lcd.setCursor(0,2);
     lcd.print("EncoderValue:");
     lcd.setCursor(0,1);
     lcd.print("EncoderDirection:");
     
     //Encoder Rotating Clockwise if bCW is True - Print to show this
     if (CWCheck){ 
       lcd.setCursor(17,1);
       lcd.print("CW");
     }
     //Encoder Rotating Counter-Clockwise if bCW is False - Print to show this
     else{
       lcd.setCursor(17,1);
       lcd.print("CC");
     }
     lcd.setCursor(14,2);
     float angle = (360/38)*encoderCount; //Encoder has 38 available positions - This is multiplied by the encoder position to form the encoder angle.
     lcd.print(angle);
   } 
   pinAlast = aVal; //Set the last encoder value to the current encoder value
  }
