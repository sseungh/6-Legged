/*
  Controls servo position from 0-180 degrees and back
  https://wokwi.com/projects/350037178957431378
  by dlloydev, December 2022.
*/

#include <pwmWrite.h>

Pwm pwm = Pwm();

const int servo[2] = {15, 2};
int pos = 0;
void setup() {
  ledcAttachPin(25, 1);
}

void loop() {
  for (pos = 0; pos <= 180; pos++) {  // go from 0-180 degrees
    pwm.writeServo(servo[0], pos);
    delay(25);
  }
  for (pos = 180; pos >= 0; pos--) {  // go from 180-0 degrees
    pwm.writeServo(servo[0], pos);
    delay(25);
  }
    for (pos = 0; pos <= 180; pos++) {  // go from 0-180 degrees
    pwm.writeServo(servo[1], pos);
    delay(25);
  }
    for (pos = 180; pos >= 0; pos--) {  // go from 0-180 degrees
    pwm.writeServo(servo[1], pos);
    delay(25);
  }
}
