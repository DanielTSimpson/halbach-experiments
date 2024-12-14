#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

int motorDia = 11.5;
int limitSwitch = 12;
int hallPin = 7;
float distance = 0;
float calibratedMICROSTEP = 111.71/700;
float calibratedINTERLEAVE = 56.03/700;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  while (!Serial);
  Serial.println("Stepper test!");
  pinMode(limitSwitch, INPUT_PULLUP);
  pinMode(hallPin, INPUT);

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
}

void loop() {
  while(digitalRead(limitSwitch) == 1){
    myMotor->setSpeed(20);  // 20 rpm
    myMotor->step(1,BACKWARD,INTERLEAVE);
    distance = 0;
  }
  myMotor->setSpeed(50);
  myMotor->step(700,FORWARD,INTERLEAVE);
  myMotor->release();
  delay(60000);

  myMotor->setSpeed(10);
  myMotor->step(700,FORWARD,INTERLEAVE);
  distance += 700*calibratedMICROSTEP;
  Serial.println(distance);
  Serial.print(" mm");
  myMotor->release();
  delay(70000);
  distance = 0;
}