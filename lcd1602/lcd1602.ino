/*
 Demonstrates the use a 16x2 LCD display.  Hitachi HD44780 driver.  16-pin interface.

 * LCD RS pin to digital pin 12 / 2
 * LCD Enable pin to digital pin 11 / 3
 * LCD D4 pin to digital pin 5 / 8
 * LCD D5 pin to digital pin 4 / 9
 * LCD D6 pin to digital pin 3 / 10
 * LCD D7 pin to digital pin 2 / 11
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
based on http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld
*/

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int rs = 2, en = 3, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
//  lcd.print("hello, world!");
}
