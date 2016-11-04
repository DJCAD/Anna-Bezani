/********************************
  DoorKnob Prototype is connecting the LDR sensor with the LCD display. 
 ********************************/
 
// include the library code
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/**********************************************************/
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
/*********************************************************/

char array1[] = "Reminder"; //Is the first message that will appear after the user being close to the LDR at the first line
char array2[] = "Don't forget your keys"; // Second line is providing the location 
int tim = 250;
int positionCounter = 20; // From were the letters will start to scroll

const int photoPIN = 0; // LDR pins
const int LED = 12;
int lightLevel;

int minLight;
int maxLight;
int adjustedLightLevel;

boolean finished = true;

void setup()
{
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  Serial.begin(9600);

  lightLevel = analogRead(photoPIN);  // set up starting light levels
  minLight = lightLevel - 20;
  maxLight = lightLevel;
}
/*********************************************************/
void loop()
{

//if(finished = true){
  lightLevel = analogRead(photoPIN);  // adjust the max and minimum in real time

  if (minLight > lightLevel) {        // this is used later to create values 0-100
    minLight = lightLevel;
  }
  if (maxLight < lightLevel) {
    maxLight = lightLevel;
  }

  // results in values 0-100
  adjustedLightLevel = map(lightLevel, minLight, maxLight, 0, 100);



  if (adjustedLightLevel < 80) { // turn on light if light level < 50
    
    lcd.setCursor(15, 0); // set the cursor to column 3, line 0
    for (int positionCounter1 = 0; positionCounter1 < 8; positionCounter1++)
    {
      lcd.scrollDisplayLeft();
      lcd.print(array1[positionCounter1]);
      // Print a message to the LCD
      delay(tim);
    }
    lcd.clear();
    lcd.setCursor(15, 1); // set the cursor to column 2, line 1
    for (int positionCounter; positionCounter < 22; positionCounter++)
    {
      lcd.scrollDisplayLeft();
      lcd.print(array2[positionCounter]);
      delay(tim);
    }
    lcd.clear();
    finished = true;
  }

  //Serial.println(adjustedLightLevel);  // dsiplay values in serial monitor
  delay(50);  // slow down to make the serial easier to read

}
/************************************************************/
