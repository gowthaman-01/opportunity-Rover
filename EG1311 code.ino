#include <Servo.h>

int dir1speed, dir2speed;
long distance;
int Start;
int cStart;
bool Running = false;
bool ConstraintOpen = false;
int Count = 0;
int timer;
Servo ConstraintS;
  
long readUltrasonicDistance(int triggerPin, int echoPin) // STANDARD ULTRASONIC DISTANCE CODE
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
 // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
 // Reads the echo pin, and returns the
 // sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void Constraint() // FOR DEPLOYMENT OF CONSTRAINT
{
  cStart = millis();
  while ((millis() - cStart) < 4500){ // DEPLOYMENT FOR ___MILLISECONDS, ADJUST TO REQUIRED TIME
    ConstraintS.writeMicroseconds(1000); 
    delay(20); 
    ConstraintS.writeMicroseconds(1500);
    delay(20); 
  }
  ConstraintS.writeMicroseconds(1500);
  ConstraintOpen = true;
}

void setMotorSpeed() // FOR SETTING MOTOR SPEED
{
  distance = readUltrasonicDistance(13,12) * 0.01723;
  if (distance <= 12) {
    Running = false;
  }
  if (Running) {
    dir1speed = 180, dir2speed = 180;
  } else {
    dir1speed = 0, dir2speed = 0;
  }
}

void setup()
{
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  ConstraintS.attach(6);// CHANGE TO WHICH PIN IS USED
  Serial.begin(9600);
  ConstraintS.writeMicroseconds(1500);
  Start = millis();
}
  
void loop()
{
  setMotorSpeed();
  analogWrite(3, dir1speed);
  analogWrite(5, dir2speed);
  delay(10); // NORMAL OPERATION
  if (((millis() - Start) > 2500) && !ConstraintOpen) {  // DEPLOYMENT AFTER ___MILLISECONDS, ADJUST TO REQUIRED TIME
    analogWrite(3, 0);
    analogWrite(5, 0);
    delay(3000);
    Constraint();
    delay(48500);
  }
}
