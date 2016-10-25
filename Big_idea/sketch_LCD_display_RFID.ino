#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
 
SoftwareSerial RFID(10, 11);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
 
void setup() {
//  Serial.begin(9600);
//  Serial.println("Serial Ready");
 
RFID.begin(9600);
// Serial.println("RFID Ready");
 
lcd.begin(16, 2);
 
}
 
void loop() {
int index =0 ;
 
char unit;
String msg;
//while no card is in field of action
 
if(msg==0){                          
lcd.setCursor(0,0);
lcd.print(" TAG is not in  ");
lcd.setCursor(0,1);
lcd.print("field of action ");
}
while(RFID.available()>0){      
         //when card is in field
lcd.setCursor(0,0);
lcd.print("TAG ID number is");
lcd.setCursor(0,1);
lcd.print("                ");
//clearing previos data
 
unit = RFID.read();
 
index++;
 
msg += unit;
 
if(index == 12)  {
//       Serial.print("Tag ID:");
// uncomment it for serial debugging
//       Serial.println(msg);
lcd.setCursor(2,1);
 
lcd.print(msg);
break; }
 
}
msg="";                         
    //clearing msg container
delay(1000); 
    //giving delay for persistence of vision
}
