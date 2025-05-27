#include <LiquidCrystal.h>  // Biblioteka do wyświetlacza LCD

// Inicjalizacja wyświetlacza LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Definiujemy piny dla Trig i Echo
const int trigPin = 9;
const int echoPin = 10;

// Zmienna do przechowywania wyniku pomiaru odległości
long duration;
int distance;

void setup() {
  // Ustawienie pinów Trig i Echo
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Inicjalizacja wyświetlacza LCD
  lcd.begin(16, 2);  // Ustawienie wyświetlacza 16x2
  
  // Wiadomość powitalna na LCD
  lcd.setCursor(0, 0);    // Ustawienie kursora na początku pierwszego wiersza
  lcd.print("Mierzenie"); 
  lcd.setCursor(0, 1);    // Ustawienie kursora na początku drugiego wiersza
  lcd.print("odleglosci...");
  delay(2000);            // Czekamy 2 sekundy
}

void loop() {
  // Wyzwolenie sygnału ultradźwiękowego
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Odczytanie czasu powrotu sygnału Echo
  duration = pulseIn(echoPin, HIGH);

  // Przeliczenie czasu na odległość (w centymetrach)
  distance = duration * 0.034 / 2;

  // Wyczyszczenie ekranu LCD
  lcd.clear();

  // Wyświetlenie wyniku na LCD
  lcd.setCursor(0, 0);             // Kursor na początek pierwszego wiersza
  lcd.print("Odleglosc:");

  lcd.setCursor(0, 1);             // Kursor na początek drugiego wiersza
  lcd.print(distance);             // Wyświetlenie zmierzonej odległości
  lcd.print(" cm");

  delay(500); // Odczekaj pół sekundy przed kolejnym pomiarem
}
