/*
 * Timing Gates
 * Using pressure Sensor
 */

int const interPin = 2;
int led = 13; // Pin 13 has an LED connected on most Arduino boards.
unsigned long DELAY_TIME = 1500; // 1.5 sec
unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false; // true if still waiting for delay to finish
bool ledOn = false; // keep track of the led state

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interPin), tripNow, RISING);
  pinMode(led, OUTPUT);   // initialize the digital pin as an output.
  digitalWrite(led, LOW); // turn led off
  ledOn = false;

  // start delay
  delayStart = millis();
  delayRunning = true;

}

void loop() {
  // check if delay has timed out
  if (delayRunning && ((millis() - delayStart) >= DELAY_TIME)) {
    delayStart += DELAY_TIME; // this prevents drift in the delays
    // toggle the led
    ledOn = !ledOn;
    if (ledOn) {
      digitalWrite(led, HIGH); // turn led on
    } else {
      digitalWrite(led, LOW); // turn led off
    }
  }
}
