


// Grandmother Clock by Jason Nyland
// ---------------------------------
// Grandmother Clock is a program that
// displays the weekday in word form
// eg "Tuesday" on a bright, uncluttered
// LCD display so that grandma stops
// taking her pills several times a day
// when she forgets what day it is!

#include <LiquidCrystal.h>
#include <DS3231.h>
#include <Time.h>
#include <TimeLib.h>

DS3231 rtc(SDA, SCL);

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int backlight_pin = 10;
int dayofweek = 0;

// clear the screen
int clearScreen()
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void setup() {
  pinMode(backlight_pin, INPUT);  // set as INPUT for full brightness, OUTPUT to adjust
  // analogWrite(backlight_pin, 200); // backlight contrast (0-255) comment line out when INPUT


  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 0);
  lcd.print("GrandmotherClock"); // boot message
  lcd.setCursor(0, 1);
  lcd.print("By: Jason Nyland");
  rtc.begin();
  setTime(rtc.getUnixTime(rtc.getTime()));
  delay(3000);
  clearScreen();



}

void loop() {
  lcd.setCursor(0, 0);
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


  lcd.setCursor(9, 1);
  if (hourFormat12() < 10) {
    lcd.print(" ");
  }
  lcd.print(hourFormat12());
  lcd.print(":");
  if (minute() < 10) {
    lcd.print("0");
  }
  lcd.print(minute());
  lcd.print(" ");
  if (isAM() == true) {
    lcd.print("A");
  }
  else {
    lcd.print("P");
  }


/* Debug Date
lcd.setCursor(0, 1);
lcd.print(month());
lcd.print(day());
lcd.print(year());
*/
}

