/*
 * Timing Gates
 * Using pressure Sensor
 */


const unsigned long period = 1000; 
int const startPin = 1;
int const stopPin = 2;
int ledPin = 13; // Pin 13 has an LED connected on most Arduino boards.
unsigned long DELAY_TIME = 1500; // 1.5 sec
unsigned long startMillis;
unsigned long currentMillis;
bool delayRunning = false; // true if still waiting for timer to finish
bool ledOn = false; // keep track of the led state that visually reps the 

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(startPin), timeNow, RISING);
  attachInterrupt(digitalPinToInterrupt(stopPin), finishNow, RISING);
  pinMode(ledPin, OUTPUT);   // initialize the digital pin as an output.
  digitalWrite(ledPin, LOW); // turn led off
  ledOn = false;
  // start delay
  startMillis = 0;
  delayRunning = false;
}

void loop() {
  // check if delay has timed out
  if (delayRunning && ( >= DELAY_TIME)) {
    
    delayStart = currentMillis;
    // toggle the led
    ledOn = !ledOn;
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}

void timeNow() {
  
}
//void loop() {
//  // check if delay has timed out
//  if (delayRunning && ((millis() - delayStart) >= DELAY_TIME)) {
//    delayStart += DELAY_TIME; // this prevents drift in the delays
//    // toggle the led
//    ledOn = !ledOn;
//    if (ledOn) {
//      digitalWrite(led, HIGH); // turn led on
//    } else {
//      digitalWrite(led, LOW); // turn led off
//    }
//  }
//}
