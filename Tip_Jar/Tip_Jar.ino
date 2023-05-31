#include <LiquidCrystal.h>

//LCD pin variables
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int piezo = 9; // pin variable for piezo
const int sensorPin = 0;// pin variable for photoresitor
const int LCDBacklight = 8;// pin for the LCD backlight

const int numNotes = 2;//stores number of notes/tones being played
const int tune[numNotes]= {1976, 2637};//use piezo to play 1976hz and 2637hz pitched notes
const int tuneLength[numNotes]= {100, 400};//play the notes for 100ms and 400ms respectively

int lightCal;//calibrated light value
int lightVal;//current light value
int sensorSensitivity = 7;

unsigned long lastDelay = 0;//stores last time the LCD was displayed

//variables used to average out readings
const int numReadings = 100;
int readings[numReadings];//array to store readings of the photoresistor
int readingIndex = 0;//index of the reading in the array
int sum = 0;


void setup(){
  Serial.begin(9600);
  pinMode(piezo, OUTPUT);//set piezo pin as a output
  lcd.begin(16, 2);//initialize LCD, 16 columns and 2 rows
  digitalWrite(LCDBacklight, LOW);//set LCD backlight to an off state
  for(int i = 0; i < numReadings; i++){
    readings[i] = 0;//initialize all elements in array to 0
  }
}

void loop(){
  lightVal = analogRead(sensorPin);
  unsigned long currentMillis = millis();

  sum -= readings[readingIndex];//subtract last reading to the sum
  readings[readingIndex] = lightVal;
  sum += readings[readingIndex];//add the current reading to the sum
  readingIndex++;
  if(readingIndex >= numReadings){
    readingIndex = 0;
  }
  lightCal = sum/numReadings;//set calibrated value to the average of the readings


  //print out values to serial monitor
  Serial.print("Val:");
  Serial.print(lightVal);
  Serial.print(",");
  Serial.print("Cal:");
  Serial.println(lightCal);

  if(lightVal < lightCal - sensorSensitivity){
    //display message on LCD display
    lcd.setCursor(1, 0);
    lcd.print("Thank you!");
    digitalWrite(LCDBacklight, HIGH);
    playTune();
    lastDelay = currentMillis;//store last time LCD was displayed
  }

  if(currentMillis - lastDelay > 5000){
    digitalWrite(LCDBacklight, LOW);
    lcd.clear();
  }
  
}

void playTune(){ 
  for (int i = 0; i < numNotes; i++){
    tone(piezo, tune[i]);
    delay(tuneLength[i]);
    noTone(piezo);
  }
}