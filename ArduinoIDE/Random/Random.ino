void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Sériová komunikace funguje");

}

void loop() {
  int cislo = random(10, 20);

  Serial.println(cislo);

  delay(1000);

}
