#include <ESP32Servo.h>

// Define servo pins
const int servoPins[6] = {5, 18, 19, 17, 16, 15};
Servo servos[6];

void setup() {
  Serial.begin(115200);

  // Attach each servo to its respective pin
  for (int i = 0; i < 6; i++) {
    servos[i].attach(servoPins[i]);
  }

  Serial.println("Servo control initialized. Use format sX-angle, e.g., s1-90");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove any whitespace or newline

    // Check if the command format is correct
    if (command.startsWith("s")) {
      int dashIndex = command.indexOf('-');
      if (dashIndex != -1) {
        int servoIndex = command.substring(1, dashIndex).toInt();
        int angle = command.substring(dashIndex + 1).toInt();

        if (servoIndex >= 1 && servoIndex <= 6 && angle >= 0 && angle <= 180) {
          servos[servoIndex - 1].write(angle);
          Serial.print("Servo ");
          Serial.print(servoIndex);
          Serial.print(" set to angle: ");
          Serial.println(angle);
        } else {
          Serial.println("Invalid servo number or angle. Servo: 1-6, Angle: 0-180.");
        }
      } else {
        Serial.println("Invalid command format. Use: sX-angle (e.g., s1-90)");
      }
    }
  }
  delay(20);
}