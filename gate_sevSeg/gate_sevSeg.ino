#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object

int const startPin = A0;
int const stopPin = A5;
unsigned long startMillis;
unsigned long currentMillis;
unsigned long lapt;
int curDisTime;
bool timerRunning = false; // true if still waiting for timer to finish
bool lapTimed = false;



void setup() {
  Serial.begin(9600);
  pinMode(startPin,INPUT);
  pinMode(stopPin,INPUT);
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
  
  startMillis = 0;
  currentMillis = 0;
  curDisTime = 0;

  timerRunning = false;
  lapTimed = false;
  

}

void loop() {  
  if (analogRead(startPin) == 1023){
    if(!timerRunning) {
      startMillis = millis();
      timerRunning = true;
      lapTimed = false;
      Serial.println("Timer Started");
    }
  }
  if (analogRead(stopPin) == 1023){
    if (timerRunning) {
      currentMillis = millis(); 
      lapt = (currentMillis - startMillis);
      timerRunning = false;
      lapTimed = true;
    }
  }
    
  if (!timerRunning && lapTimed) {
    Serial.print("The lap time was: ");
    Serial.print(lapt/1000);
    Serial.print('.');
    Serial.print(lapt%1000);
    Serial.println(" Sec");
    lapTimed = false; 
    curDisTime = lapt/10;

  }
  if (timerRunning){
    currentMillis = millis(); 
    curDisTime = (currentMillis - startMillis)/10;
  }

//  if (timerRunning){
//    curTime = (currentMillis - startMillis)/100;
//    sevseg.setNumber(curTime, 1);
//  }
//  else {
//    sevseg.setNumber(0, 1);
//  }
  if (curDisTime < 9990){
    sevseg.setNumber(curDisTime, 2);
    sevseg.refreshDisplay();
  }
  else if(curDisTime < 99900){
    sevseg.setNumber(curDisTime/10, 1);
    sevseg.refreshDisplay();
  }
  else{
    sevseg.setNumber(curDisTime/100, 0);
    sevseg.refreshDisplay();
  }
  
   // Must run repeatedly
  //Serial.println(analogRead())
  

}
