//To include library for the use of LCD
#include <LiquidCrystal.h>

//INITIALISATION OF PIN NUMBERS 
int sensor = 8;       //CONNECTION TO OUT PIN OF PIR SENSOR          
int led = 13;        //CONNECTION TO LED
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;   //CONNECTION TO THE RESPECTIVE PINS OF THE LCD DISPLAY
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);    //CONFIGURATION OF CONNECTION WITH LCD DISPLAY

void setup() {
  lcd.begin(24, 4);       //To set the number of columns and rows of the LCD
  Serial.begin(9600);
  pinMode(sensor, INPUT);   //Taking the output of the PIR sensor as input 
  pinMode(led, OUTPUT);     //Choose the LED as output
  digitalWrite(led,LOW);    //INITIALISATION OF LED'S STATE
}

void loop() {

  int k=0;      
  long lastReset=millis();      //To save the time of last reset of the PIR sensor
  while(digitalRead(sensor)==HIGH)
  {
   lcd.setCursor(0, 0);         // Cursor is set at the 0th position
   int t1=10000-(millis()-lastReset);     //Calculation of time left in the room with time limit 10s

   if(t1/1000>0)      //If within set limit
   {
    String hellomsg="HELLO!! YOUR TIME LEFT HERE IS ";
    String s=" SECONDS.";
    lcd.print(hellomsg);
    digitalWrite(led,HIGH);   //Turn ON the LED lights
    lcd.setCursor(4,14);      //Cursor can be set to the desire position to display the seconds
    lcd.print(t1/1000);
    lcd.print(s);
   }
   
   else     //When exceeds limit
   {
    while(k<1)
    {
      lcd.clear();      //Clear the LCD only once
      k++;
    }
    
    lcd.setCursor(0,0);       //Set the Cursor back to 0th position
    digitalWrite(led,LOW);    //Make the LED blink
    delay(500);
    digitalWrite(led,HIGH);
    lcd.print("YOUR TIME IS UP! PLEASE LEAVE.");    //Alert Message
   }


   if(digitalRead(sensor)==LOW)     //When the sensor doesn't find any movement
   {
    digitalWrite(led,LOW);      //Turn OFF the LED light
    lcd.setCursor(0,0);         //Set the cursor to 0th position
    lcd.clear();                //Clear the screen
    lcd.print("THANK YOU FOR VISITING! ");    //Thank You message
    delay(500);
    lcd.clear();    //Clear again
   }


  }
  
}