# Grandmother_Clock by Jason Nyland

A minimalistic LCD clock that only shows the day of week

Grandmother Clock is a program that displays the weekday 
in word form (eg "Tuesday") on a bright, uncluttered
LCD display so that my grandmother can see what day it is
while taking her medication, to avoid double-dosing while
using a weekday pill box.  It's a clean, simple clock for 
the forgetful!  Many clocks show the weekday, but they are
dim, cluttered with other information, and optimized for 
battery life.

Instructions:
Upload this sketch, then open a serial monitor at 9600 baud
to set the clock.  If you don't use the OSEPP LCD shield,
you will need to reconfigure LCD pinouts as appropriate.

Features to add:
- RTC support for DS3231 module
- Motion-activated backlight with PIR sensor
  - Investigate battery power once backlight can turn off
