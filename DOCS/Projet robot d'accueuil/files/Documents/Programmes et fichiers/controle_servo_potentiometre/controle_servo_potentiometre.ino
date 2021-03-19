
 /*
 Controle d'un servo moteur à partir d'un potentiomètre
 */
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object
}
void loop() {
  val = analogRead(potpin);            // Lecture des valeurs du potentiomètre entre 0 et 1023
  val = map(val, 0, 1023, 0, 180);     // convertir les valeurs 0-1023 en 0-180
  myservo.write(val);                  // écriture de la valeur dans le servo
  delay(15); // temps d'attente
}

