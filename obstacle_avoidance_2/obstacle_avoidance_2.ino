#include <Servo.h>

// Define motor control pins
int in1Pin = 3;
int in2Pin = 4;
int in3Pin = 5;
int in4Pin = 6;
int enaPin = 7;
int enbPin = 2;

// Define servo motor pin
int servoPin = 9;

// Define ultrasonic sensor pins
int trigPin = 10;
int echoPin = 11;

// Define servo motor object
Servo myservo;

void setup() {
  // Set motor control pins as output
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(enaPin, OUTPUT);
  pinMode(enbPin, OUTPUT);

  // Set servo pin as output
  myservo.attach(servoPin);

  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize Serial communication
  Serial.begin(9600);
  
  // Set initial state
  moveForward();
  myservo.write(90); // Set servo to face forward
}

void loop() {
  moveForward();
  // Check for obstacle
  /*if (checkObstacle()) {
    stopMotors();
    delay(500);
    
    if (checkObstacleRight()== true && checkObstacleLeft() == false) {
      turnLeft();
      delay(1000);
    } else if (checkObstacleRight()== false && checkObstacleLeft() == true){
      turnRight();
      delay(1000);
    } else {
      moveForward();
    }
    
    myservo.write(90); // Set servo to face forward
    delay(500);
  } else {
    moveForward();
  }*/
}

void moveForward() {
  // Forward motion
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enaPin, 200); // PWM speed control for motor A
  analogWrite(enbPin, 200); // PWM speed control for motor B
}

void stopMotors() {
  // Stop motion
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  analogWrite(enaPin, 0);
  analogWrite(enbPin, 0);
}

void turnRight() {
  // Right turn motion
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enaPin, 200); // PWM speed control for motor A
  analogWrite(enbPin, 200); // PWM speed control for motor B
  delay(500);
  stopMotors();
}

void turnLeft() {
  // Left turn motion
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  analogWrite(enaPin, 200); // PWM speed control for motor A
  analogWrite(enbPin, 200); // PWM speed control for motor B
  delay(500);
  stopMotors();
}

bool checkObstacle() {
  // Perform ultrasonic distance measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  int distance = duration / 58;

  // Print distance to Serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if obstacle is within 20 cm
  if (distance < 20) {
    return true; // Obstacle detected
  } else {
    return false;
  }
}

bool checkObstacleRight() {
  // Turn right using servo motor
  myservo.write(0); // Set servo to 0 degrees (right position)
  delay(500);

  // Perform ultrasonic distance measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  int distance = duration / 58;

  // Print distance to Serial monitor
  Serial.print("Right Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if obstacle is within 20 cm
  if (distance < 20) {
    return true; // Obstacle detected
  } else {
    return false; // No obstacle
  }
}

bool checkObstacleLeft() {
  // Turn left using servo motor
  myservo.write(180); // Set servo to 180 degrees (left position)
  delay(500);

  // Perform ultrasonic distance measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  int distance = duration / 58;

  // Print distance to Serial monitor
  Serial.print("Left Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if obstacle is within 20 cm
  if (distance < 20) {
    return true; // Obstacle detected
  } else {
    return false; // No obstacle
  }
}
