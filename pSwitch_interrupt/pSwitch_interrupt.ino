/*
 * Timing Gates
 * Using pressure Sensor
 */
 
int const startPin = 2;
int const stopPin = 3;
int ledPin = 13; // Pin 13 has an LED connected on most Arduino boards.
unsigned long startMillis;
unsigned long currentMillis;
bool timerRunning = false; // true if still waiting for timer to finish
bool ledOn = false; // keep track of the led state that visually reps the 
bool lapTimed = false;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(startPin), timeNow, FALLING);
  attachInterrupt(digitalPinToInterrupt(stopPin), finishNow, FALLING);
  pinMode(ledPin, OUTPUT);   // initialize the digital pin as an output.
  digitalWrite(ledPin, LOW); // turn led off
  startMillis = 0;
  currentMillis = 0;
  ledOn = false;
  timerRunning = false;
  lapTimed = false;
}

void loop() {
  // check if delay has timed out
  if (timerRunning && !ledOn){
    digitalWrite(ledPin, HIGH);
    ledOn = true;
  }
    
  if (!timerRunning && lapTimed) {
    ledOn = !ledOn;
    digitalWrite(ledPin, LOW);
    Serial.println("The lap time was:");
    Serial.println(currentMillis - startMillis);
    lapTimed = false;    
  }
}

void timeNow() {
  startMillis = millis();
  timerRunning = true;
  lapTimed = false;
}

void finishNow(){
  currentMillis = millis();
  timerRunning = false;
  lapTimed = true;
}
