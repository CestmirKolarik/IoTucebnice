const int tlacitko = D1;
const int cervena = D2;

boolean stavTlacitka = LOW; //tlačítko je na začátku nestisknuté
  
void setup() {
  pinMode(tlacitko, INPUT); //vstup - tlačítko
  pinMode(cervena, OUTPUT); //výstup - LED dioda
  }

void loop() {
  //uloží aktuální stav tlačítka - zjistí, zda je stisklé
  stavTlacitka = digitalRead(tlacitko);
  if(stavTlacitka == HIGH){ //když bude tlačítko stisklé...
    digitalWrite(cervena, HIGH);
    delay(2000);
    digitalWrite(cervena, LOW);
    }
  delay(10);
  }
