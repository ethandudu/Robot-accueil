/*                        Janvier 2014                          */
/*  A utiliser avec un shield ardumoto et un module Bluetooth   */
/*        connecté sur la liaison série Rx 0 Tx 1              */
/****************************************************************/

//Initialisation des E/S et communication

//Initialisation des E/S et communication
void setup() {
Serial.begin(9600); }
//Programme principal 
void loop() {
  Serial.println("BONJOUR de");
delay(1500);         
Serial.println("prenom"); // Ecrire votre prénom dans la parenthèse
delay(1500);
    }
//Fin
