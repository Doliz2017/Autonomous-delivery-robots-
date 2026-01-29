// --- PIN DEFINITIONS ---
// L293D Motor Driver Pins
const int motorLeft_Input1 = 3;   // Pin 3 to L293D Pin 2 (IN1)
const int motorLeft_Input2 = 4;   // Pin 4 to L293D Pin 7 (IN2)
const int motorRight_Input3 = 5;  // Pin 5 to L293D Pin 10 (IN3)
const int motorRight_Input4 = 6;  // Pin 6 to L293D Pin 15 (IN4)

// Sensor Pin (Simulated by Potentiometer)
const int sensorPin = A0; 

// --- SETTINGS ---
// Adjust this threshold based on your Potentiometer testing
// 0 = Far away, 1023 = Very close (Hitting the wall)
const int OBSTACLE_THRESHOLD = 700; 

void setup() {
  // Set motor pins as outputs
  pinMode(motorLeft_Input1, OUTPUT);
  pinMode(motorLeft_Input2, OUTPUT);
  pinMode(motorRight_Input3, OUTPUT);
  pinMode(motorRight_Input4, OUTPUT);
  
  // Set sensor pin as input
  pinMode(sensorPin, INPUT);
  
  // Start Serial for debugging (Optional)
  Serial.begin(9600);
}

void loop() {
  // 1. Read the "Distance" from the Potentiometer
  int sensorValue = analogRead(sensorPin);
  
  // Print value to Virtual Terminal so you can see it
  Serial.print("Distance Sensor Value: ");
  Serial.println(sensorValue);

  // 2. Decide what to do
  if (sensorValue > OBSTACLE_THRESHOLD) {
    // OBSTACLE DETECTED! (Voltage is high)
    // Sequence: Stop -> Reverse -> Turn
    stopRobot();
    delay(500);
    moveBackward();
    delay(1000);
    turnRight();
    delay(800);
  } else {
    // PATH IS CLEAR
    moveForward();
  }
}

// --- MOVEMENT FUNCTIONS ---

void moveForward() {
  // Left Motor Forward
  digitalWrite(motorLeft_Input1, HIGH);
  digitalWrite(motorLeft_Input2, LOW);
  // Right Motor Forward
  digitalWrite(motorRight_Input3, HIGH);
  digitalWrite(motorRight_Input4, LOW);
}

void moveBackward() {
  // Left Motor Backward
  digitalWrite(motorLeft_Input1, LOW);
  digitalWrite(motorLeft_Input2, HIGH);
  // Right Motor Backward
  digitalWrite(motorRight_Input3, LOW);
  digitalWrite(motorRight_Input4, HIGH);
}

void turnRight() {
  // Left Motor Forward
  digitalWrite(motorLeft_Input1, HIGH);
  digitalWrite(motorLeft_Input2, LOW);
  // Right Motor Backward (Spin turn)
  digitalWrite(motorRight_Input3, LOW);
  digitalWrite(motorRight_Input4, HIGH);
}

void stopRobot() {
  digitalWrite(motorLeft_Input1, LOW);
  digitalWrite(motorLeft_Input2, LOW);
  digitalWrite(motorRight_Input3, LOW);
  digitalWrite(motorRight_Input4, LOW);
}
