#include <LiquidCrystal.h> 
#include <Servo.h>
void setup()
{
  pinMode(13, OUTPUT);
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  servo myservo;
  myservo.attach(6);
}

void loop()
{
  lcd.print(myservo.read);
  delay(1000);
}