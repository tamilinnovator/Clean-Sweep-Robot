#include <Servo.h>

Servo myservo; 
// Create a servo object 
int trigPin = 13; 
// Ultrasonic sensor trigger pin 
int echoPin = 12; // Ultrasonic sensor echo pin 
long duration, distance;

int angle = 45;

int r_motor_n = 10; //PWM control Right Motor +
int r_motor_p = 11; //PWM control Right Motor -
int l_motor_p = 9; //PWM control Left Motor -
int l_motor_n = 6; //PWM control 0Left Motor +
int pump = 4;
int mop = 5;
int fan = 3;
int speedy = 255;
int incomingByte = 0; // for incoming serial data
void setup()
{
myservo.attach(3); // Attaches the servo on pin 3
pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);
pinMode(r_motor_n, OUTPUT); //Set control pins to be outputs
pinMode(r_motor_p, OUTPUT);
pinMode(l_motor_p, OUTPUT);
pinMode(l_motor_n, OUTPUT);
pinMode(pump, OUTPUT);
pinMode(mop, OUTPUT);
pinMode(fan, OUTPUT);
digitalWrite(r_motor_n, LOW); //set both motors off for start-up
digitalWrite(r_motor_p, LOW);
digitalWrite(l_motor_p, LOW);
digitalWrite(l_motor_n, LOW);
digitalWrite(pump, HIGH.);
digitalWrite(mop, LOW);
digitalWrite(fan, LOW);
Serial.begin(9600);
}
void loop()
{

digitalWrite(trigPin, LOW); delayMicroseconds(2); digitalWrite(trigPin, HIGH); delayMicroseconds(10); digitalWrite(trigPin, LOW); // Read the duration of the pulse from the echo pin 
duration = pulseIn(echoPin, HIGH); // Calculate the distance in centimeters 
distance = (duration / 2) / 29.1;

// Check if an object is within a certain range (adjust as needed) 
if (distance > 10 && distance < 40)
{
myservo.write(90 + angle);
myservo.write(90 - angle);
delay(1000);
}
else if (distance <= 10) { 
digitalWrite(r_motor_n, LOW); 
digitalWrite(r_motor_p, LOW);
digitalWrite(l_motor_p, LOW);
digitalWrite(l_motor_n, LOW);
Serial.println("Stop");
delay(1000); 
// Wait for the servo to turn
} 
else {
myservo.write(0);
} 
delay(100);

if (Serial.available() > 0) 
{
incomingByte = Serial.read();
}
switch(incomingByte)
{
case 'S': // control to stop the robot
digitalWrite(r_motor_n, LOW); 
digitalWrite(r_motor_p, LOW);
digitalWrite(l_motor_p, LOW);
digitalWrite(l_motor_n, LOW);
Serial.println("Stop");
incomingByte='*';
break;
case 'R': //control for right
analogWrite(r_motor_n, speedy); 
digitalWrite(r_motor_p, LOW);
analogWrite(l_motor_p, speedy);
digitalWrite(l_motor_n, LOW);
Serial.println("right");
incomingByte='*';
break;
case 'L': //control for left
digitalWrite(r_motor_n, LOW); 
analogWrite(r_motor_p, speedy);
digitalWrite(l_motor_p, LOW);
analogWrite(l_motor_n, speedy);
Serial.println("left");
incomingByte='*';
break;
case 'F': //control for forward
analogWrite(r_motor_n, speedy);
digitalWrite(r_motor_p, LOW);
digitalWrite(l_motor_p, LOW);
analogWrite(l_motor_n, speedy);
Serial.println("forward");
incomingByte='*';
break;
case 'B': //control for backward
digitalWrite(r_motor_n, LOW);
analogWrite(r_motor_p, speedy);
analogWrite(l_motor_p, speedy);
digitalWrite(l_motor_n, LOW);
Serial.println("back");
incomingByte='*';
break;
case 'P': // pump on
digitalWrite(pump, LOW);
Serial.println("pump on");
incomingByte='*';
break;

case 'p': // pump off
digitalWrite(pump, HIGH); 
Serial.println("pump off");
incomingByte='*';
break;

case 'M':
digitalWrite(mop, HIGH); // mopper on
Serial.println("mopper on");
incomingByte='*';
break;
case 'm':
digitalWrite(mop, LOW); // mopper off
Serial.println("mopper off");
incomingByte='*';
break;

/*case 'U': // fan on
delay(1000);
digitalWrite(fan, HIGH);
Serial.println("fan on");
incomingByte='*';
break;

case 'u': // fan off
digitalWrite(fan, LOW);
Serial.println("fan off");
incomingByte='*';
break;*/

delay(5000);
}
}
 
