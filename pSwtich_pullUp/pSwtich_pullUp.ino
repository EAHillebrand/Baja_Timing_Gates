/*
 * Timing Gates
 * Using pressure Sensor
 */
int const startPin = 2;
int const stopPin = 8;
unsigned long startMillis;
unsigned long currentMillis;
unsigned long lapt;
bool timerRunning = false; // true if still waiting for timer to finish
bool ledOn = false; // keep track of the led state that visually reps the 
bool lapTimed = false;

void setup() {
  Serial.begin(9600);
  pinMode(startPin,INPUT_PULLUP);
  pinMode(stopPin,INPUT_PULLUP);
  pinMode(13, OUTPUT);
  startMillis = 0;
  currentMillis = 0;
  ledOn = false;
  timerRunning = false;
  lapTimed = false;
}

void loop() {
  if (!digitalRead(2) && !timerRunning) {
    startMillis = millis();
    timerRunning = true;
    lapTimed = false;
    Serial.println("Timer Started");
  }
  if (!digitalRead(8) && timerRunning) {
    currentMillis = millis(); 
    lapt = (currentMillis - startMillis);
    timerRunning = false;
    lapTimed = true;
  }
  //Serial.println(sensorVal, DEC);
  if (timerRunning && !ledOn){
    digitalWrite(13, HIGH);
    ledOn = true;
  }
    
  if (!timerRunning && lapTimed) {
    ledOn = !ledOn;
    digitalWrite(13, LOW);
    Serial.print("The lap time was: ");
    Serial.print(lapt/1000);
    Serial.print('.');
    Serial.print(lapt%1000);
    Serial.println(" Sec");
    lapTimed = false;    
  }

}
