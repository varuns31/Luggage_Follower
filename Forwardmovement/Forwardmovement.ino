// Include the required libraries
#include <Arduino.h>

// Define motor control pins
const int motor1Pin1 = 18; // Motor 1 input 1
const int motor1Pin2 = 19; // Motor 1 input 2
const int enable1Pin = 21; // Motor 1 enable pin

const int motor2Pin1 = 16; // Motor 2 input 1
const int motor2Pin2 = 17; // Motor 2 input 2
const int enable2Pin = 5; // Motor 2 enable pin

// Define PWM parameters
const int pwmFrequency = 1000; // PWM frequency in Hz
const int pwmResolution = 8; // PWM resolution (8 bits for values 0-255)
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
int duty = 160;

const int trigPin = 33;
const int echoPin = 32;


//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  // Initialize motor control pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  // Set PWM frequency and resolution
  ledcSetup(pwmChannel1, pwmFrequency, pwmResolution);
  ledcSetup(pwmChannel2, pwmFrequency, pwmResolution);

  // Attach PWM channels to motor control pins
  ledcAttachPin(enable1Pin, pwmChannel1);
  ledcAttachPin(enable2Pin, pwmChannel2);
  // pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  // pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {

  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  // Run both motors at half speed for 10 seconds
  ledcWrite(pwmChannel1, 128);  //DEFECTIVE 
  ledcWrite(pwmChannel2, 128);   
    // Clears the trigPin
  delay(5000);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
    delay(5000);
  // digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  // // Sets the trigPin on HIGH state for 10 micro seconds
  // digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin, LOW);
  
  // // Reads the echoPin, returns the sound wave travel time in microseconds
  // duration = pulseIn(echoPin, HIGH);
  
  // // Calculate the distance
  // distanceCm = duration * SOUND_SPEED/2;
  // Serial.print("distanceCm: ");
  // Serial.print(distanceCm);
    
  // while(distanceCm <= 100){
  //     // Clears the trigPin
  //   digitalWrite(motor1Pin1, LOW);
  //   digitalWrite(motor1Pin2, LOW);
  //   digitalWrite(motor2Pin1, LOW);
  //   digitalWrite(motor2Pin2, LOW);
  //   digitalWrite(trigPin, LOW);
  //   delayMicroseconds(2);
  //   // Sets the trigPin on HIGH state for 10 micro seconds
  //   digitalWrite(trigPin, HIGH);
  //   delayMicroseconds(10);
  //   digitalWrite(trigPin, LOW);
    
  //   // Reads the echoPin, returns the sound wave travel time in microseconds
  //   duration = pulseIn(echoPin, HIGH);
    
  //   // Calculate the distance
  //   distanceCm = duration * SOUND_SPEED/2;
  //   Serial.print(distanceCm);
  // }

  // Serial.print("Distance (inch): ");
  // Serial.println(distanceInch);
  // Add any additional code or logic here for the rest of your program
}