void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Sériová komunikace funguje");
}

void loop() {

  Serial.println("Sečteme čísla 7 a 5");
  Serial.println(secti(7, 5));
  delay(10000);

}

int secti(int x, int y)
{
  int vysledek = x + y;
  return vysledek;
}

int odecti(int x, int y)
{
  int vysledek = x - y;
  return vysledek;
}
