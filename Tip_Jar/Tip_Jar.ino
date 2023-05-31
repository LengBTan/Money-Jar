#include <LiquidCrystal.h>

//LCD pin variables
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int piezo = 9; // pin variable for piezo
const int sensorPin = 0;// pin variable for photoresitor
const int LCDBacklight = 8;// pin for the LCD backlight

const int tune[3]= {1976, 2637};//use piezo to play 1976hz and 2637hz pitched notes
const int tuneLength[3]= {100, 400};//play the notes for 100ms and 400ms respectively

int lightCal;//calibrated light value
int lightVal;//current light value

void setup(){
  Serial.begin(9600);
  pinMode(piezo, OUTPUT);//set piezo pin as a output
  lcd.begin(16, 2);//initialize LCD, 16 columns and 2 rows
  digitalWrite(LCDBacklight, LOW);//set LCD backlight to an off state
  lightCal = analogRead(sensorPin);
}

void loop(){
  lightVal = analogRead(sensorPin);

  //print out values to serial monitor
  Serial.print("Val:");
  Serial.print(lightVal);
  Serial.print(",");
  Serial.print("Cal:");
  Serial.println(lightCal);

  if(lightVal < lightCal - 7){//if the current light value is less than the calibrated value
    //display message on LCD display
    lcd.setCursor(1, 0);
    lcd.print("Thank you!");
    digitalWrite(LCDBacklight, HIGH);
    delay(5000);
  }
  
  digitalWrite(LCDBacklight, LOW);
  lcd.clear();
}