  //naimportujeme si knihovny
  #include <Wire.h>
  #include <HTU21D.h>
  #include <LiquidCrystal_I2C.h>

  int prodleva = 1000;
  
  HTU21D myHTU21D(HTU21D_RES_RH12_TEMP14);

  // Nastevení adresy displeje a počet znaků na řádek a počet řádků
  LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  delay(2000);
  Serial.println("Sériová komunikace funguje");

  //kontroluje, že je čidlo správně zapojené a funguje
  while (myHTU21D.begin() != true)
  {
    Serial.println(F("HTU21D, SHT21 snímač selhal nebo není připojen"));
    delay(5000);
  }
  Serial.println(F("HTU21D, SHT21 snímač je aktivní"));

  //zapnutí displeje a podsvícení
  lcd.begin();
  lcd.backlight();
}


void loop()
{
  //načtení hodnot
  float teplota = myHTU21D.readTemperature();
  float vlhkost = myHTU21D.readHumidity();

  //konzole
  Serial.print("Teplota: ");
  Serial.print(teplota);
  Serial.println(" °C");
  Serial.print("Vlhkost: ");
  Serial.print(vlhkost);
  Serial.println(" %");

  //display
  lcd.clear();
  //první řádek
  lcd.setCursor(0, 0);
  lcd.print("Te: ");
  lcd.print(teplota);
  lcd.print(" ");
  lcd.write(223);
  lcd.print("C");
  //druhý řádek
  lcd.setCursor(0, 1);
  lcd.print("Vl: ");
  lcd.print(vlhkost);
  lcd.print(" %");

  delay(prodleva);
}
