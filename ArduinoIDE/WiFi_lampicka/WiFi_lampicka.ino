#include <ESP8266WiFi.h>

 // Nazev Wi-Fi site, do ktere se mam pripojit
const char* ssid = "ASUS";

 // Heslo Wi-Fi site, do ktere se mam pripojit
const char* pass = "n0ctu136";

// Ma svitit lampicka?
bool svetlo = false;

// Webovy server pobezi na portu 80 (HTTP komunikace)
WiFiServer server(80);

#define ledka 5
 
void setup(){
 // Nastartuj seriovou linku, do ktere budu vypisovat provozni informace
 Serial.begin(9600);
 delay(2000);
 Serial.println("Sériová komunikace funguje");

 // Nastav pin D1 na zapis a nastav nizkou hodnotu (LED dioda nesviti)
 pinMode(ledka, OUTPUT);
 digitalWrite(ledka, LOW);
 
 // Pripojeni k Wi-Fi
 Serial.println();
 Serial.print("Pripojuji k ");
 Serial.println(ssid);
 connectWiFi();
 
 // Spusteni serveru
 server.begin();
 Serial.println("Server spusten");
 
 // Napis IP adresu, kterou mikropocitac dostal
 Serial.print("Pouzij k pripojeni tuto adresu: ");
 Serial.print("http://");
 Serial.println(WiFi.localIP());
}

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

// Smycka loop se opakuje stale dokola 
void loop() {
 // Pokud ma promenna svetlo hodnotu pravda, posli na pin D1 napeti a rozsvit LED diodu
 if(svetlo == true)
  {
    digitalWrite(ledka, HIGH);
  }
  else
  {
    digitalWrite(ledka, LOW);
  }
 
 // Cekej, dokud se nepripoji nejaky klient
 WiFiClient client = server.available();
 if (!client) {
 return;
 }
 
 // Cekej, dokud klient neposle nejaka data
 Serial.println("Novy klient!");
 while(!client.available()){
 delay(1);
 }
 
 // Precti a vypis prvni radek od klienta s URL dotazem
 String request = client.readStringUntil('\r');
 Serial.println(request);
 client.flush();
 
 // Pokud je v radku vyraz ZapnoutSvetlo, nastav promennou svetlo na pravdu
 if(request.indexOf("ZapnoutSvetlo") > -1) svetlo = true;
 // Pokud je v radku vyraz VypnoutSvetlo, nastav promennou svetlo na nepravdu
 if(request.indexOf("VypnoutSvetlo") > -1) svetlo = false;

 // Posli pripojenemu klientu HTML kod stranky s tlacitky
 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println("");
 client.println("<!DOCTYPE html>");
 client.println("<html><body>");
 client.print("<h1>Moje Wi-Fi lampicka</h2>");
 // Tlacitko pro zapnuti lampicky vede na adresu /ZapnoutSvetlo
 client.println("<a href=\"/ZapnoutSvetlo\"><button>Zapni svetlo</button></a>");
 // Tlacitko pro vypnuti lampicky vede na adresu /VypnoutSvetlo
 client.println("<a href=\"/VypnoutSvetlo\"><button>Vypni svetlo</button></a><br />");
 client.println("</body></html>");

 // To je vse, ted jeste 1 ms pockam a cela smycka se muze zopakovat
 delay(1);
 Serial.println("Klient odpojen");
 Serial.println("");
}
