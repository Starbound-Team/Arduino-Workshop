// To view the schematic and more information about this circuit go to the following article: https://www.tinkercad.com/things/3rR1Bc1BIpf-starbound-workshop-p3?sharecode=pSAk-YyKQ2BFswExL0f8UD_c0g538VUTlVTgXOvF7-E

// To view the circuit on tinkercad copy this link: https://www.tinkercad.com/things/3rR1Bc1BIpf-starbound-workshop-p3

#include<Servo.h>           // Include the Servo library, which allows us to control servo motors

#define trigPin 8           // Define the trigPin as digital pin 8, which will be used to trigger the ultrasonic sensor
#define echoPin 9           // Define the echoPin as digital pin 9, which will read the echo from the ultrasonic sensor

long duration;              // Variable to store the time duration of the echo
int distance;               // Variable to store the calculated distance based on duration
int i;                      // Loop variable for moving the servo angle

Servo myservo;              // Create a Servo object to control a servo motor

// Function to calculate distance using the ultrasonic sensor
int calculateDistance() {
  digitalWrite(trigPin, LOW);          // Set the trigPin to LOW to ensure a clean HIGH pulse later
  delayMicroseconds(2);                // Short delay to stabilize signal
  digitalWrite(trigPin, HIGH);         // Set trigPin to HIGH to send out an ultrasonic burst
  delayMicroseconds(10);               // Keep trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, LOW);          // Set trigPin back to LOW to stop the burst
  
  duration = pulseIn(echoPin, HIGH);   // Measure the time it takes for the echo to return to the echoPin
  
  // Calculate the distance in centimeters based on the time duration
  // (sound speed in air is ~0.034 cm/µs, dividing by 2 to account for the round trip)
  distance = duration * 0.034 / 2;
  
  return distance;                     // Return the calculated distance
}

void setup() {
  pinMode(trigPin , OUTPUT);           // Set the trigPin as an output pin
  pinMode(echoPin, INPUT);             // Set the echoPin as an input pin
  myservo.attach(11);                  // Attach the servo to digital pin 11 for PWM control
  Serial.begin(9600);                  // Begin serial communication at 9600 bps to send data to the serial monitor
}

void loop() {
   // Move the servo from 15 to 165 degrees, checking distance at each position
   for (i = 15; i <= 165; i++) {
      myservo.write(i);                // Set servo position to angle i
      delay(15);                       // Short delay to allow servo to reach the position
      calculateDistance();             // Calculate the distance at the current servo angle
      Serial.print(i);                 // Print the current servo angle to the serial monitor
      Serial.print(",");               // Print a comma to separate angle and distance data
      Serial.print(distance);          // Print the measured distance
      Serial.print(".");               // Print a period as a delimiter for each reading
   }
   
   // Move the servo back from 165 to 15 degrees, checking distance at each position
   for (i = 165; i >= 15; i--) {
      myservo.write(i);                // Set servo position to angle i
      delay(15);                       // Short delay to allow servo to reach the position
      calculateDistance();             // Calculate the distance at the current servo angle
      Serial.print(i);                 // Print the current servo angle to the serial monitor
      Serial.print(",");               // Print a comma to separate angle and distance data
      Serial.print(distance);          // Print the measured distance
      Serial.print(".");               // Print a period as a delimiter for each reading
   }
}
