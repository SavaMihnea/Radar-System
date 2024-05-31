#include <Servo.h>

//Trig and Echo pins of the ultrasonic
const int trigPin = 10;
const int echoPin = 11;

// LED pins
const int redLedPin = 8;
const int greenLedPin = 9;

//variables for the duration and the distance
long duration;
int distance;

//servo object for controlling the servo
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT); //trigPin as an output
  pinMode(echoPin, INPUT); //echoPin as an input
  
  //LED pins as outputs
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  Serial.begin(9600);
  myServo.attach(12); //pin for the servo
}

void loop() {
  //rotates the servo motor from 0 to 180 degrees
  for(int i=0;i<=180;i++){  
    myServo.write(i);
    delay(30);
    distance = calculateDistance();//calling a function for calculating the distance measured by the Ultrasonic sensor for each degree
    
    Serial.print(i); //sends the current degree into the port (COM4)
    Serial.print(","); //sends addition character right next to the previous value needed later in the Processing app
    Serial.print(distance); //sends the distance value into the port
    Serial.print("."); //sends addition character right next to the previous value needed later in the Processing app
    
    //check distance and update LEDs
    updateLEDs(distance);
  }

  //for structure for repeating the previous lines from 180 to 0 degrees
  for(int i=180;i>0;i--){
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    
    //check distance and update LEDs
    updateLEDs(distance);
  }
}

//function for calculating the distance measured by the ultrasonic
int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}

//function to update LEDs based on distance
void updateLEDs(int distance) {
  if (distance > 40) {
    digitalWrite(greenLedPin, HIGH); //no object, green LED ON
    digitalWrite(redLedPin, LOW);    //no object, red LED OFF
  } else {
    digitalWrite(greenLedPin, LOW);  //object detected, green LED OFF
    digitalWrite(redLedPin, HIGH);   //object detected, red LED ON
  }
}