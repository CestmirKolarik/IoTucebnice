  //načtení potřebných knihoven
  #include <NTPClient.h>
  #include <ESP8266WiFi.h>
  #include <WiFiUdp.h>
  
  //jméno a heslo pro připojení na WiFi
  const char* ssid     = "IoT";
  const char* password = "17091991";
  
  //adresa ntp serveru - v evropě používáme evropský server
  const char* NTPServer = "europe.pool.ntp.org";
  
  /*konstanta offsetu UTC v sekundách - v naší zeměpisné šířce (zimní čas) jsme UTC+1, tedy +1 hodina, v sekundách 3600
   * pro letní čas jsme posunuti o +2 hodiny, tedy UTC+2, pak je třeba 3600s vynásobit dvěma
   */
  const long utcOffsetInSeconds = 7200;
  
  //Pole dnů v týdnu, NTP server vrací dny jako číslo, na základě čísla se pak vyčte den jako text
  char daysOfTheWeek[7][12] = {"Nedele", "Pondeli", "Utery", "Streda", "Ctvrtek", "Patek", "Sobota"};

  //inicializace protokolu pro komunikaci
  WiFiUDP ntpUDP;
  //inicializace časového klienta NZP
  NTPClient timeClient(ntpUDP, NTPServer, utcOffsetInSeconds);

//metoda pro připojení k WiFi
boolean connectWiFi(){
  //vypíše na seriovy monitor že probíhá inicializace wifi
  Serial.println("Connecting to WiFi.");
  delay(10);
  //připojí se k wifi s daným ssid a heslem
  WiFi.begin(ssid, password);
  //čítač opakování připojení
  int count = 0;
  //cyklus běží, dokud status wifi není "připojeno", jakmile se připojí, vyskočí z cyklu
  while (WiFi.status() != WL_CONNECTED)
  {
    //pokud je počet opakování připojení menší než 15
    if(count < 15){
      //vypíše tečku na seriový monitor, tečka znamená neúspěšné připojení, progress
      Serial.print(".");
      //počká půl sekundy
      delay(500);
    }
    else{
      //jinak vypíše že připojení selhalo
      Serial.println("");
      Serial.println("Connection to WiFi failed. :( ");
      //ukončí metodu a vrátí false
      return false; 
    }
    //inkrementuje čítač
    count++; 
  }
  //informuje o úspěšném připojení
  Serial.println("");
  Serial.println("WiFi connection successful. :) ");
  //ukončí metodu a vrátí true
  return true;
}


void setup() {
  //inicializace sériové komunikace 
  Serial.begin(9600);
  delay(2000);
  //výpis informace o zahájení inicializace
  Serial.println("Zahajuji inicializaci NTP");
  //připojení k WiFi
  connectWiFi();
  //spuštění časového klienta
  timeClient.begin();

}

/*Metoda pro získání času z NTP serveru
 * vrací String hodnotu - čas
 */
String ntpTime(){
  //aktualizace NTP klienta
  timeClient.update();
  //metoda vrací čas získaný z NTP serveru
  return timeClient.getFormattedTime();
}

/*Metoda pro získání dne z NTP serveru
 * vrací String hodnotu - den
 */
String ntpDay(){
  //aktualizace NTP klienta
  timeClient.update();
  //metoda vrací den získaný z NTP serveru
  return daysOfTheWeek[timeClient.getDay()];
}

void loop() {
  
  //výpis dne a času do konzole
  Serial.print("Dnes je: ");
  Serial.print(ntpDay());
  Serial.print(", ");
  Serial.println(ntpTime());
  
  //počká určenou dobu mezi výpisy - zpravidla sekundu pro výpis po sekundě
  delay(1000);

}
