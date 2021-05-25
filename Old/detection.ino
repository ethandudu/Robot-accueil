#include <Servo.h>

long lecho; // Variable de lecture de l'echo
long cm; // Variable pour passer en cm
//
// Définition du servo
Servo myservo;
int pos = 0; // variable permettant de conserver la position du servo
bool angle_actuel = false;//Envoi sur le port série la position courante du servomoteur

void setup()
{
pinMode(5, OUTPUT); // Trigger HC-SR04
pinMode(4, INPUT); // Echo HC-SR04
pinMode(13, OUTPUT); // LED Alimentation
pinMode(12, OUTPUT); // LED Détection
myservo.attach(7); //Servo
Serial.begin(500); // Lancement moniteur série
Serial.print("Chargement termine !"); // Annonce fin du chargement
}

void loop()
{
  capteur_ultra();
  debug();
  distance();
}

void capteur_ultra() // Capteur Ultrason HC-SR04
{
  digitalWrite(13, HIGH); // Allumage LED Alimentation
  digitalWrite(5, HIGH); // Activation Trigger
  delay(10); // Attente de 10ms
  digitalWrite(5, LOW); // Désactivation Trigger
  lecho = pulseIn(4, HIGH); //Récupération Echo
  cm = lecho /58; // Conversion Echo en cm
}

void debug() //Debug
{
  Serial.println("Ultra");
  Serial.println(cm);
  delay(1000);
  Serial.println("Servo");
  Serial.println(myservo.read());
}

void distance()
{
  if (cm >= 100) {
      digitalWrite(12, LOW);
      myservo.write(0);
      delay(1000);
  }
  else {
      digitalWrite(12, HIGH); // LED détection ON
      myservo.write(45); //Servo 90°
      delay(1000);
  }
}