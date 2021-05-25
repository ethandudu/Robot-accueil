// Chargement librairies
#include <Servo.h> 

// Définition du servo
Servo myservo; //

void setup() {
  myservo.attach(6);
  Serial.begin(1200); // Lancement moniteur série
  Serial.print("Chargement termine !"); // Annonce fin du chargement
}

void loop() {
  delay(1000);
  Serial.println("Servo : ");
  Serial.println(myservo.read());
}
