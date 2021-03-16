long lecho; // Variable de lecture de l'echo
long cm; // Variable pour passer en cm

void setup()
{
pinMode(5, OUTPUT); // Trigger HC-SR04
pinMode(4, INPUT); // Echo HC-SR04
pinMode(13, OUTPUT); // LED Alimentation
pinMode(3, INPUT); // Signal Servo
pinMode(12, OUTPUT); // LED Détection
Serial.begin(1000); // Lancement moniteur série
Serial.print("Chargement termine !"); // Annonce fin du chargement
}

void loop()
{
  // Capteur ultrason
  digitalWrite(13, HIGH); // Allumage LED Alimentation
  digitalWrite(5, HIGH); // Activation Trigger HC-SR04
  delay(10); // Attente de 10ms
  digitalWrite(5, LOW); // Désactivation Trigger HC-SR04
  lecho = pulseIn(4, HIGH); //Récupération Echo
  cm = lecho /58; // Conversion Echo en cm
  Serial.println(cm); // Affichage de la valeur sur le moniteur série
  delay(100); // Attente de 100ms
  
  // ON/OFF LED Détection
  if (cm >= 100) {
   digitalWrite(12, LOW); // LED détection OFF
  }
  else digitalWrite(12, HIGH);{ // LED détection ON
  }
}