  //Import knihoven
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>

  // Nastevení adresy displeje a počet znaků na řádek a počet řádků
  LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	lcd.begin();

	// Zapnutí podstvícení a výpis zprávy
	lcd.backlight();
	lcd.print("Hrajeme si s IoT");
}

void loop()
{

}
