// Grandmother Clock by Jason Nyland
// ---------------------------------
// Grandmother Clock is a program that
// displays the weekday in word form
// eg "Tuesday" on a bright, uncluttered
// LCD display so that grandma stops
// taking her pills several times a day
// when she forgets what day it is!

#include <LiquidCrystal.h>
#include <Time.h>
#include <TimeLib.h>
 
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
int backlight_pin = 10;
int dayofweek = 0;
int incomingHr = 0;
int incomingMin = 0;
int incomingDay = 0;
int incomingMo = 0;
int incomingYr = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
 
// currently unused button functionality for OSEPP LCD shield
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT; 
 if (adc_key_in < 195)  return btnUP;
 if (adc_key_in < 380)  return btnDOWN;
 if (adc_key_in < 555)  return btnLEFT;
 if (adc_key_in < 790)  return btnSELECT;  
 return btnNONE;  // when all others fail, return this...
}
// clear the screen
int clearScreen()
{
 lcd.setCursor(0,0);
 lcd.print("                ");
 lcd.setCursor(0,1);
 lcd.print("                ");
}

void setup() {
 pinMode(backlight_pin, INPUT);  // set as INPUT for full brightness, OUTPUT to adjust
 // analogWrite(backlight_pin, 200); // backlight contrast (0-255) comment line out when INPUT

    Serial.begin(9600);
    
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("GrandmotherClock"); // boot message
 lcd.setCursor(0,1);
 lcd.print("By: Jason Nyland");
 delay(3000);
 clearScreen();
 


     lcd.setCursor(0,0);
     lcd.print("Set Time Now");
     Serial.println("---------------------");
     Serial.println("Set Time and Date Now");
     Serial.println("---------------------");
     
                Serial.println("Hour (24h): ");
                while (Serial.available()==0) {}
                incomingHr = Serial.parseInt();
                Serial.println(incomingHr);
                delay(50);
                
                Serial.println("Minute (0-59): ");
                while (Serial.available()==0) {}
                incomingMin = Serial.parseInt();
                Serial.println(incomingMin);
                delay(50);

                Serial.println("Month (1-12): ");
                while (Serial.available()==0) {}
                incomingMo = Serial.parseInt();
                Serial.println(incomingMo);
                delay(50);
                                
                Serial.println("Day (1-31): ");
                while (Serial.available()==0) {}
                incomingDay = Serial.parseInt();
                Serial.println(incomingDay);
                delay(50);

                Serial.println("Year (####): ");
                while (Serial.available()==0) {}
                incomingYr = Serial.parseInt();
                Serial.println(incomingYr);
                delay(50);
                
                setTime(incomingHr,incomingMin,0,incomingDay,incomingMo,incomingYr);
                lcd.setCursor(0,0);
                lcd.print("Time Set!       ");
                Serial.println("Time Set!");
                Serial.println(" ");
                delay(3000);
                clearScreen();
                
                
}

void loop() {
 lcd.setCursor(0,0);
 dayofweek = weekday();
 switch (dayofweek)
 {
   case 1:
     {
     lcd.print("Sunday   ");
     break;
     }
  case 2:
    {
    lcd.print("Monday   ");
    break; 
    }
   case 3:
    {
    lcd.print("Tuesday  ");
    break;
    }
   case 4:
    {
    lcd.print("Wednesday");
    break;
    }
   case 5:
    {
    lcd.print("Thursday ");
    break;
    }
   case 6:
    {
    lcd.print("Friday   ");
    break;
    }
   case 7:
    {
    lcd.print("Saturday ");
    break;
    }
 }

 lcd.setCursor(0,0);


 lcd.setCursor(9,1);
 if (hourFormat12()<10) {lcd.print(" ");}
 lcd.print(hourFormat12());
 lcd.print(":");
 if (minute()<10) {lcd.print("0");}
 lcd.print(minute());
 lcd.print(" ");
 if (isAM()==true) {
  lcd.print("A");
 }
 else {
  lcd.print("P");
 }


 
      
        }

