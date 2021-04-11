  //inicializace knihoven
  #include <ThingSpeak.h>
  #include <ESP8266WiFi.h>
  #include <Wire.h>
  #include <HTU21D.h>

  HTU21D myHTU21D(HTU21D_RES_RH12_TEMP14);

  //jménoa  heslo k wifi
  const char* ssid = "IoT";
  const char* pass = "17091991";

  //číslo kanálu na thingspeaku najdete jako channel ID, jeto 6 místné číslo, to napište místo nul
  unsigned long myChannelNumber = 1327277;
  //API Keys - Write API Key (16 znaků)
  const char* myWriteAPIKey = "2O02CL15KHBU7RY0";

  //definujeme si jednu sekundu, tedy 1000 ms
  const int second = 1000;
  //definujeme si interval prodlevy - číslem násobíme sekundu, tj. kolik sekund chceme čekat
  //minimální prodleva je 20s, menší prodlevu thingspeak neumožňuje
  unsigned const int interval = 20*second;

  /*teď ještě knihovna WiFiClient pro vytvoření klienta
   * klient je to, co se připojí k zařízení
   * když třeba hledáte něco na googlu, tak vy jste klient
   * v našem případě je klient thingspeak a připojuje se na naše zařízení, uvidíte níže v kódu
   */
  WiFiClient client;
  
//metoda připojení k wifi, vrací logickou hodnotu, kterou informuje o úspěšnosti připojení
boolean connectWiFi(){
  //vypíše na seriovy monitor že probíhá inicializace wifi
  Serial.println("Connecting to WiFi.");
  delay(10);
  //nastavení persistence - zařízení nebude hledat již použité WiFi sítě
  WiFi.persistent(false);
  //připojí se k wifi s daným ssid a heslem
  WiFi.begin(ssid, pass);
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

//metoda pro odeslání hodnot na thingspeak, vrací logickou hodnotu o povedeném nebo nepovedeném odeslání
boolean sendToThingspeak(){
  // write to the ThingSpeak channel, proměnná x je hodnota číselného kodu http, jímž se ověřuje správnost odesílacího požadavku
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
    return true;
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
    return false;
  }
}

void setup() {
  //inicializace sériové komunikace pro stavové hlášení
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
  
  //nastavíme wifi jako klienta, zde je klientem myšleno naše zařízení, které se připojuje k síti wifi jako klient
  WiFi.mode(WIFI_STA);
  //a inicializujeme thingspeak, abychom s ním mohli komunikovat, předáváme mu wifi klienta
  ThingSpeak.begin(client);
  //připojíme se k wifi
  connectWiFi();
}

void loop() {
  //pokud je wifi odpojena, znovu ji připojíme
  if(WiFi.status() != WL_CONNECTED){
    connectWiFi();
  }

  //z čidel si do proměnných načteme hodnoty
  float teplota = myHTU21D.readTemperature();
  float vlhkost = myHTU21D.readHumidity();
  
  ThingSpeak.setField(1, teplota);
  ThingSpeak.setField(2, vlhkost);
  
  //odešleme hodnoty polí na thingspeak
  sendToThingspeak();
  
  //počká interval
  delay(interval);
}
