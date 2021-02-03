void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Sériová komunikace funguje");
}

void loop() {
  Serial.print(); //vypíše na aktuální řádek a další výpis bude na stejném řádku
  Serial.println(); //vypíše na aktuální řádek a další výpis bude na novém řádku

  String pozdrav = "Ahoj světe";
  Serial.println(pozdrav);
  Serial.println("Ahoj světe");

}
