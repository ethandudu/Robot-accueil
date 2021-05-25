/*

Programme réalisé par les STI2D B, plus d'infos sur le github du projet : https://github.com/ethandudu/Robot-Accueil
 Note : Servo : if value is < 200 its treated as an angle, otherwise as pulse width in microseconds
*/


//Définition des librairies à utiliser
#include <LiquidCrystal_I2C.h> // Écran LCD
#include <Wire.h> // Shield de l'écran
#include "pitches.h" // Notes du buzzer
#include <Servo.h> // Servo moteurs


// Définition pins autres
int PinBuzzer = 4;


// Définition pins Leds
int PinLedPower = 8;
int PinLedStatus = 9;
int PinLedDebug = 5;


// Définition pins HC-SR04
int PinHCTrigger = 7;
int PinHCEcho = 6;


// Définition pins servos             Pin = Pin, S = Servo-moteur, R= Rotation, O = Ouverture, B = Bas, H = Haut, I = Inclinaison, F = Fermeture
int PinSRTete = 3; // Rotation de la tête
int PinSITete = 10; //Inclinaison tête
int PinSIYeux = 11; // Inclinaison des yeux
int PinSRYeux = 12; // Rotation des yeux
int PinSFYeux = 13; // Fermeture des paupières
int PinSOBoucheB = 14; // Lèvre bas
int PinSOBoucheH = 15; // Lèvre haut


// Définition servos
Servo ServoRTete; // Rotation de la tête
Servo ServoITete; //Inclinaison tête
Servo ServoIYeux; // Inclinaison des yeux
Servo ServoRYeux; // Rotation des yeux
Servo ServoFYeux; // Fermeture des paupières
Servo ServoOBoucheB; // Lèvre bas
Servo ServoOBoucheH; // Lèvre haut


// Variables pour le HC-SR04
long lecho; // Variable de lecture de l'echo
long cm; // Variable pour passer en cm


// Écran
const int tps = 150;

LiquidCrystal_I2C lcd(0x27, 20, 4); // Définition des pins de communication entre l'écran et l'Arduino (20 (Data), 21 (Fréquence))

byte pacman[] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B11011,
  B11111,
  B11100,
  B01110
};

byte ball[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000
};

byte clear[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};


void setup()
{
  // Initialisation Serial
  Serial.begin(1200); // Lancement moniteur série pour débug
  Serial.print("Chargement termine !"); // Annonce fin du chargement sur le serial


  // Définifition des pinModes
  //HC-SR04
  pinMode(PinHCTrigger, OUTPUT); // Trigger HC-SR04
  pinMode(PinHCEcho, INPUT); // Echo HC-SR04
  //LEDS
  pinMode(PinLedPower, OUTPUT); // Led Power
  pinMode(PinLedStatus, OUTPUT); // Led Statut
  pinMode(PinLedDebug, OUTPUT); // Led DEBUG
  //Autres
  pinMode(PinBuzzer, OUTPUT); //Buzzer


  // Lien pins avec les servos
  ServoRTete.attach(PinSRTete);
  ServoITete.attach(PinSITete);
  ServoIYeux.attach(PinSIYeux);
  ServoRYeux.attach(PinSRYeux);
  ServoFYeux.attach(PinSFYeux);
  ServoOBoucheB.attach(PinSOBoucheB);
  ServoOBoucheH.attach(PinSOBoucheH);
  
  digitalWrite(PinLedPower, HIGH); // Allumage Led Power


  // Démarrage de l'écran
  lcd.init();
  lcd.backlight();
  lcd.createChar(1, pacman);
  lcd.createChar(2, ball);
  lcd.createChar(3, clear);
  lcd.begin(16, 2);
  lcd.setCursor(4,0);
  lcd.print("Demarrage");
  lcd.setCursor(1,1);
  lcd.write((byte)1);
  lcd.setCursor(3,1);
  lcd.write((byte)2);
  lcd.setCursor(5,1);
  lcd.write((byte)2);
  lcd.setCursor(7,1);
  lcd.write((byte)2);
  lcd.setCursor(9,1);
  lcd.write((byte)2);
  lcd.setCursor(11,1);
  lcd.write((byte)2);
  lcd.setCursor(13,1);
  lcd.write((byte)2);


  // Initialisation de la position des servos
  ServoRTete.write(60);
  ServoITete.write(60);
  ServoIYeux.write(60);
  ServoRYeux.write(60);
  ServoFYeux.write(60);
  ServoOBoucheB.write(60);
  ServoOBoucheH.write(60);
  
  delay(500);
  
   
  for(int i = 1; i < 14; i++)
  {
    lcd.setCursor(i,1);
    lcd.write((byte)1);
    delay(tps);
    lcd.setCursor(i,1);
    lcd.write((byte)3);
    delay(tps);
  }
  
  
  lcd.clear();
 
  thumbsup();
  
  //digitalWrite(PinLedPower, LOW); // Reste désormais active
  digitalWrite(PinLedStatus, HIGH); // Allume la LED verte
  
  delay(1000);
  
  systemop();
  
}

 
// Définition du pouce en l'air une fois le chargement fini
void thumbsup()
{
 byte thumb1[8] = {B00100,B00011,B00100,B00011,B00100,B00011,B00010,B00001};
 byte thumb2[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00011};
 byte thumb3[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00001,B11110};
 byte thumb4[8] = {B00000,B01100,B10010,B10010,B10001,B01000,B11110,B00000};
 byte thumb5[8] = {B00010,B00010,B00010,B00010,B00010,B01110,B10000,B00000};
 byte thumb6[8] = {B00000,B00000,B00000,B00000,B00000,B10000,B01000,B00110};
 lcd.createChar(4, thumb1);
 lcd.createChar(5, thumb2);
 lcd.createChar(6, thumb3);
 lcd.createChar(7, thumb4);
 lcd.createChar(8, thumb5);
 lcd.createChar(9, thumb6);
 lcd.setCursor(6,1);
 lcd.write((byte)4);
 lcd.setCursor(6,0);
 lcd.write((byte)5);
 lcd.setCursor(7,1);
 lcd.write((byte)6);
 lcd.setCursor(7,0);
 lcd.write((byte)7);
 lcd.setCursor(8,1);
 lcd.write((byte)8);
 lcd.setCursor(8,0);
 lcd.write((byte)9);
}


// Définition de l'affichage "système démarré" de l'écran + Welcoming musical
void systemop()
{
  lcd.home();
  lcd.setCursor(5,0);
  lcd.print("Systeme");
  lcd.setCursor(5,1);
  lcd.print("demarre");
  tone(PinBuzzer, NOTE_A2, 200);
  delay(500);
  tone(PinBuzzer, NOTE_A2, 200);
  delay(1000);
  lcd.clear();
}

void loop()
{
  // Capteur ultrason
  digitalWrite(PinHCTrigger, HIGH); // Activation Trigger HC-SR04
  delay(10); // Attente de 10ms
  digitalWrite(PinHCTrigger, LOW); // Désactivation Trigger HC-SR04
  lecho = pulseIn(PinHCEcho, HIGH); //Récupération Echo
  // Peut être une opti en rajoutant digitalWrite(PinHCEcho, LOW) car jamais désactivé ?
  cm = lecho /58; // Conversion Echo en cm
  //Serial.println(cm); Debug avec affichage de la distance en serial
  activation();
}

void activation()
{
  if (cm <= 15) // Distance d'activation
  {
  
  //delay(500);
    digitalWrite(PinLedDebug, HIGH); // Activation LED détection
    lcd.setCursor(4,0);
    lcd.print ("BONJOUR,");
    delay(1000);
    lcd.clear();
    lcd.print("COMMENT PUIS-JE");
    lcd.setCursor(3,1);
    lcd.print("VOUS AIDER ?");
    delay(1000);
    lcd.clear();
  }
  else
  {
    digitalWrite(PinLedDebug, LOW); // Désactivation LED détection
  }

}
