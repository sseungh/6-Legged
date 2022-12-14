/*
  Controls servo position from 0-180 degrees and back
  https://wokwi.com/projects/350037178957431378
  by dlloydev, December 2022.
*/

#include <pwmWrite.h>

Pwm pwm = Pwm();

const int servo[16] = {33, 32, 16, 17, 14, 12, 13, 4, 2, 15, 23, 22, 21, 19, 18, 5};
int pos = 0;
void setup() {
  //서보 채널 정해주기, 처음 들어오는 순서대로 0번
  for(int i = 0; i < 16; i++){
    pwm.writeServo(servo[i], pos);
  }
  ledcAttachPin(25, 1);
}

void loop() {
  for (pos = 0; pos <= 180; pos++) {  // go from 0-180 degrees
    pwm.writeServo(32, pos);
    delay(25);
  }
    for (pos = 180; pos >= 0; pos--) {  // go from 0-180 degrees
    pwm.writeServo(32, pos);
    delay(25);
  }
}
