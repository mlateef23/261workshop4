#include <Servo.h>

Servo angleServo;      // Positional servo connected to pin 11
Servo spinServo;       // Continuous rotation servo connected to pin 9
int userValue = 0;

void setup() {
  Serial.begin(9600);
  angleServo.attach(11);  // Attach positional servo
  spinServo.attach(9);    // Attach rotational servo
  Serial.println("Type 'P <angle>' to move the angle servo or 'R <speed>' to control the rotation servo.");
}

void moveAngleServo(int angleInput) {
  angleInput = constrain(angleInput, 0, 180);  // Ensure angle is valid
  angleServo.write(angleInput);
  Serial.print("Angle servo moved to: ");
  Serial.println(angleInput);
}

void setRotationSpeed(int speedInput) {
  speedInput = constrain(speedInput, -100, 100);  // Clamp speed
  int signalValue = map(speedInput, -100, 100, 0, 180);
  spinServo.write(signalValue);

  Serial.print("Spin servo set to speed: ");
  Serial.print(speedInput);
  Serial.print("% (PWM value: ");
  Serial.print(signalValue);
  Serial.println(")");
}

void loop() {
  if (Serial.available() > 0) {
    String commandLine = Serial.readStringUntil('\n');
    commandLine.trim(); // Remove whitespace
    char controlType = commandLine.charAt(0);
    int spaceIndex = commandLine.indexOf(' ');
    
    if (spaceIndex != -1) {
      String valueStr = commandLine.substring(spaceIndex + 1);
      int controlValue = valueStr.toInt();
      
      if (controlType == 'P' || controlType == 'p') {
        moveAngleServo(controlValue);
      } else if (controlType == 'R' || controlType == 'r') {
        setRotationSpeed(controlValue);
      } else {
        Serial.println("Invalid command. Use 'P' for position or 'R' for rotation.");
      }
    } else {
      Serial.println("Format error. Use: 'P <angle>' or 'R <speed>'");
    }
  }
}