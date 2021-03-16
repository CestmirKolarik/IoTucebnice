  //naimportujeme si knihovny
  #include <Wire.h>
  #include <HTU21D.h>
  
  HTU21D myHTU21D(HTU21D_RES_RH12_TEMP14);

void setup()
{
  Serial.begin(9600);
  delay(5000);
  Serial.println("Sériová komunikace funguje");

  //kontroluje, že je čidlo správně zapojené a funguje
  while (myHTU21D.begin() != true)
  {
    Serial.println(F("HTU21D, SHT21 snímač selhal nebo není připojen"));
    delay(5000);
  }
  Serial.println(F("HTU21D, SHT21 snímač je aktivní"));
}


void loop()
{

  Serial.print("Teplota: ");
  Serial.print(myHTU21D.readTemperature()); //přečte teplotu
  Serial.println(" °C");
  Serial.print("Vlhkost: ");
  Serial.print(myHTU21D.readHumidity()); //přečte vlhkost
  Serial.println(" %");
  delay(5000);

}
