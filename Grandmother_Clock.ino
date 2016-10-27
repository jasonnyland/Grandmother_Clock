/*
  Grandmother Clock by Jason Nyland
  ---------------------------------
  Grandmother Clock is a program that
  displays the weekday in word form
  eg "Tuesday" on a bright, uncluttered
  LCD display so that grandma stops
  taking her pills several times a day
  when she forgets what day it is!
*/

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DS3231.h>
#include <Time.h>
#include <TimeLib.h>

DS3231 rtc(SDA, SCL);
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // OSEPP Shield pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // Raw LCD pins

// int backlight_pin = 10; // OSEPP shield backlight pin
int dayofweek = 0;
const long intervalBlinker = 1000;
const long intervalSync = 600000; // 10 minutes
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
boolean blinkingCursor = false;
boolean showDebug = false;
int blinkOnOff = 0;
int clearScreen();


int clearScreen()
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}
int bootScreen() {
  lcd.setCursor(0, 0);
  lcd.print("GrandmotherClock");
  lcd.setCursor(0, 1);
  lcd.print("By: Jason Nyland");
  delay(3000);
}
int syncRTC() {
  setTime(rtc.getUnixTime(rtc.getTime()));
}
int autoSync() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= intervalSync) {
    previousMillis = currentMillis;
    syncRTC();
  }
}
int printCursor() {
  if (blinkOnOff == 0) {
    lcd.print(":");
  } else {
    lcd.print(" ");
  }
}
int printWeekday() {
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
}
int printTime() {
  lcd.setCursor(9, 1);
  if (hourFormat12() < 10) {
    lcd.print(" ");
  }
  lcd.print(hourFormat12());

  if (blinkingCursor == true) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= intervalBlinker) {
      previousMillis = currentMillis;
      if (blinkOnOff == 0) {
        blinkOnOff = 1;
      } else {
        blinkOnOff = 0;
      }
    }
  }

  printCursor();

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
}
int printDebug() {
  lcd.setCursor(0, 1);
  lcd.print(month());
  lcd.print(day());
  lcd.print(year());
}

void setup() {
  // pinMode(backlight_pin, INPUT);  // set as INPUT for full brightness, OUTPUT to adjust
  // analogWrite(backlight_pin, 200); // backlight contrast (0-255) comment line out when in INPUT mode

  lcd.begin(16, 2);              // start libraries
  rtc.begin();

  bootScreen();
  syncRTC();
  clearScreen();
}

void loop() {

  printWeekday(); // LCD first line
  printTime();  // LCD second line
  if (showDebug == true) {
    printDebug(); // print debug info on second line
  }

  autoSync();   // sync Time library with RTC
}


