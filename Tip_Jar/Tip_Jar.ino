#include <LiquidCrystal.h>

//LCD pin variables
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int piezo = 9; // pin variable for piezo
const int sensorPin = 0;// pin variable for photoresitor
void setup(){
const int LCDBacklight = 8;// pin for the LCD backlight

int lightCal;
int lightCal;//calibrated light value
int lightVal;//current value

void setup(){
  Serial.begin(9600);
  pinMode(piezo, OUTPUT);//set piezo pin as a output
  lcd.begin(16, 2);//initialize LCD, 16 columns and 2 rows
  digitalWrite(LCDBacklight, LOW);//set LCD backlight to an off state
}

void loop(){
  
}