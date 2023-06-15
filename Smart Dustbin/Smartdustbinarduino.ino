#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int trigPin = 6;
const int echoPin = 7;

const int trigPin1 = 8;
const int echoPin1 = 9;

const int buzzer = 10;

const int servoPin = 13;

long duration;
int distanceCm, distanceInch;
int safetyDistance;

long duration1;
int distanceCm1, distanceInch1;
int safetyDistance1;

Servo servo;

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(buzzer, OUTPUT);

  servo.attach(servoPin);
  servo.write(0);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distanceCm1 = duration1 * 0.034 / 2;
  distanceInch1 = duration1 * 0.0133 / 2;

  Serial.print("Distance 1: ");
  Serial.print(distanceCm);
  Serial.print(" cm | ");
  Serial.print(distanceInch);
  Serial.println(" inch");


  Serial.print("Distance 2: ");
  Serial.print(distanceCm1);
  Serial.print(" cm | ");
  Serial.print(distanceInch1);
  Serial.println(" inch");

  safetyDistance = distanceCm;
  if (safetyDistance <= 5) {
    digitalWrite(buzzer, HIGH);
  }
  else {
    digitalWrite(buzzer, LOW);
  }

  if (distanceCm1 <= 10) {
    servo.write(90);
    delay(7000);
  } else {
    servo.write(0);
  }

  lcd.setCursor(0, 0);
  lcd.print("Distance 1: ");
  lcd.print(distanceCm);
  lcd.print("cm");

  lcd.setCursor(0, 1);
  lcd.print("Distance 1: ");
  lcd.print(distanceInch);
  lcd.print("inch");

  delay(100); // Adjust delay as needed
}
