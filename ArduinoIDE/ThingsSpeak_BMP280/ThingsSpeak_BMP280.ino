  //inicializace knihoven
  #include <ThingSpeak.h>
  #include <ESP8266WiFi.h>

  //jméno a heslo k wifi
  const char* ssid = "IoT";
  const char* pass = "17091991";

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

  //číslo kanálu - channel ID (7 místné číslo)
  unsigned long myChannelNumber = 1444083;
  //API Keys - Write API Key (16 znaků)
  const char* myWriteAPIKey = "ZSJI6CWHO5FG0A1Z";

  //definice 1 sekundy (tedy 1000 ms)
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
  Wire.begin(SDA, SCL);
  //inicializace sériové komunikace pro stavové hlášení
  Serial.begin(9600);
  //nastavíme wifi jako klienta, zde je klientem myšleno naše zařízení, které se připojuje k síti wifi jako klient
  WiFi.mode(WIFI_STA);
  //a inicializujeme thingspeak, abychom s ním mohli komunikovat, tak jako s ledkou nebo seriovým monitorem, předáváme mu wifi klienta
  ThingSpeak.begin(client);
  //připojíme se k wifi
  connectWiFi();
  Serial.println("Inicializace senzoru");
  // zahájení komunikace se senzorem BMP280,
  // v případě chyby je vypsána hláška po sériové lince
  // a zastaven program
  if (!bmp.begin(BMP280_ADRESA)) {
    Serial.println("BMP280 senzor nenalezen, zkontrolujte zapojeni!");
    while (1);
  }
}

//cislo, ktere budeme vypisovat na thingspeak. v průběhu loopu se bude jeho hodnota náhodně měnit
float teplota = bmp.readTemperature();
void loop() {
  //pokud je wifi odpojena, znovu ji připojíme
  if(WiFi.status() != WL_CONNECTED){
    connectWiFi();
  }
  //přiřadíme hodnotu prvnímu poli v thingspeaku, pokud budete mít více polí, měníte číslo pole, tedy první parametr, druhý parametr je posílaná hodnota
  ThingSpeak.setField(1, teplota);
  //takto by vypadal zápis do druhého pole
  //ThingSpeak.setField(2, hodnota);
  
  
  //odešleme hodnoty polí na thingspeak
  sendToThingspeak();

  //změní hodnotu proměnné cislo na náhodné číslo z rozsahu 0-100
  teplota = bmp.readTemperature();
  
  //počká interval
  delay(interval);
}
