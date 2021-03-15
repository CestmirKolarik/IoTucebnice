void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Sériová komunikace funguje");
}

void loop() {

  for(int cislo = 1; cislo <=20; cislo++)
  {
    if(cislo > 10)
    {
      Serial.println("Číslo je větší než 10");
    }
      else
    {
      Serial.println("Číslo není větší než 10");
    }
  }

  Serial.println("KONEC");
  
}
