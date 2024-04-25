#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void lcd_innit()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void show_display()
{
  lcd.setCursor(0, 0);
  lcd.print("LCD 20x4");
  lcd.setCursor(0, 1);
  lcd.print("I2C Address: 0x27");
  lcd.setCursor(0, 2);
  lcd.print("DIYables");
  lcd.setCursor(0, 3);
  lcd.print("www.diyables.io");
}