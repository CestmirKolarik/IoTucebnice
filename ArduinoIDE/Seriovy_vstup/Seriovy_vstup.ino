void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Sériová komunikace funguje");
}

void loop() {
  String prectenaHodnota = "";
  Serial.println("Zadejte slovo");
  while(prectenaHodnota.equals("")) {
    prectenaHodnota = Serial.readString();
  }
  Serial.print("Prectena hodnota je: ");
  Serial.println(prectenaHodnota);
}
