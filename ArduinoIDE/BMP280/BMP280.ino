// Modul pro měření teploty a barometrického tlaku - bmp280

// připojení potřebných knihoven
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
// nastavení adresy senzoru - v případě potřeby kontrola přes I2C scanner a oprava
#define BMP280_ADRESA (0x76)
#define SDA D1
#define SCL D2
// inicializace senzoru BMP z knihovny
Adafruit_BMP280 bmp;
// konstanta s korekcí měření v hPa
const int korekce = 0;
//prodleva měření v ms
const int prodleva = 5000;

void setup() {
  Wire.begin(SDA, SCL);
  // inicializace komunikace po sériové lince rychlostí 9600 baud
  Serial.begin(9600);
  delay(5000);
  //Výpis hlášení
  Serial.println("Inicializace senzoru");
  // zahájení komunikace se senzorem BMP280,
  // v případě chyby je vypsána hláška po sériové lince
  // a zastaven program
  if (!bmp.begin(BMP280_ADRESA)) {
    Serial.println("BMP280 senzor nenalezen, zkontrolujte zapojeni!");
    while (1);
  }
}

void loop() {
  // načtení naměřené teploty ze senzoru
  float teplota = bmp.readTemperature();
  // načtení naměřeného tlaku ze senzoru, převedení na hPa a přidání korekce
  float tlak = (bmp.readPressure()/100.00) + korekce;
  // výpis všech dostupných informací ze senzoru BMP
  // výpis teploty
  Serial.print("Teplota: ");
  Serial.print(teplota);
  Serial.println(" °C.");
  // výpis barometrického tlaku v hekto Pascalech
  Serial.print("Barometricky tlak: ");
  Serial.print(tlak);
  Serial.println(" hPa");
  // vytištění prázdného řádku a pauza po dobu 5 vteřin
  Serial.println();
  delay(prodleva);
}
