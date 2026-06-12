#include <LiquidCrystal.h>
// Components and pin connections
// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(4, 11, 9, 10, 6, 5);
// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;
// RGB LED pins
const int redPin = 13;
const int greenPin = 8;
const int bluePin = 12;
// Buzzer pin
const int buzzer = 7;
long duration;
int distance;
void setup() {
  // Initialize LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
  // Set input/output modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  // Welcome message
  lcd.print("Parking Assist");
  delay(2000);
  lcd.clear();}
void loop() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read echo time
  duration = pulseIn(echoPin, HIGH);
  // Calculate distance in cm
  // 0.034 = speed of sound in cm/us
  distance = duration * 0.034 / 2;
  // If sensor gives no reading
  if (duration == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Sensor");
    // Blue LED
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    noTone(buzzer);
    delay(500);
    return;
  }
  // Display distance on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.print(distance);
  lcd.print("cm");
  // Safe distance
  if (distance > 60) {
    // Green LED and no sound
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    noTone(buzzer);
    lcd.setCursor(0, 1);
    lcd.print("Safe");
  }
  // Medium distance
  else if (distance > 30) {
    // Yellow LED and slow beep
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    tone(buzzer, 1000);
    delay(200);
    noTone(buzzer);
    delay(200);
    lcd.setCursor(0, 1);
    lcd.print("Careful");
  }
  // Very close
  else if (distance > 20) {
    // Red LED and faster beep
    digitalWrite(redPin, HIGH);
digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    tone(buzzer, 1500);
    delay(100);
    noTone(buzzer);
    delay(100);
    lcd.setCursor(0, 1);
    lcd.print("TOO CLOSE");
  }
  // Stop immediately
  else {
    // Red LED and continuous alarm
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    tone(buzzer, 2000);
    lcd.setCursor(0, 1); 
 lcd.print("STOP !!");
  }
  delay(100);
}
