#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "pitches.h"
#include <Servo.h>

//Définition pins servos
int P1 = 3;
Servo servo1;

const int tps = 150;

LiquidCrystal_I2C lcd(0x27, 20, 4);

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


void setup() {

  pinMode(7, OUTPUT); // Trigger HC-SR04
  pinMode(6, INPUT); // Echo HC-SR04
  pinMode(8, OUTPUT); // Led Power
  pinMode(9, OUTPUT); // Led Statut
  pinMode(5, OUTPUT); // Led DEBUG
  pinMode(4, OUTPUT); //Buzzer

  servo1.attach(3);
  
  digitalWrite(8, HIGH);

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
  Serial.begin(1200); // Lancement moniteur série
  Serial.print("Chargement termine !"); // Annonce fin du chargement
  servo1.write(60);
  
  delay(1000);
  
   
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
  
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  
  delay(1000);
  
  systemop();
  
}

 
void thumbsup() {
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

void systemop() {
  
  lcd.home();
  
  lcd.setCursor(5,0);
  lcd.print("Systeme");
  lcd.setCursor(5,1);
  lcd.print("demarre");
  delay(1000);
  tone(4, NOTE_A2, 200);
  delay(500);
  tone(4, NOTE_A2, 200);
  lcd.clear();
}

long lecho; // Variable de lecture de l'echo
long cm; // Variable pour passer en cm

void loop()
{
  // Capteur ultrason
  digitalWrite(7, HIGH); // Activation Trigger HC-SR04
  delay(10); // Attente de 10ms
  digitalWrite(7, LOW); // Désactivation Trigger HC-SR04
  lecho = pulseIn(6, HIGH); //Récupération Echo
  cm = lecho /58; // Conversion Echo en cm
  Serial.println(cm);
  loop2();
}

void loop2()
{
  if (cm <= 15) {// Distance d'activation
  //delay(500);
    digitalWrite(5, HIGH);
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
  else {
    digitalWrite(5, LOW);
  }
}
