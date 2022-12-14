/*
  Controls servo position from 0-180 degrees and back
  https://wokwi.com/projects/350037178957431378
  by dlloydev, December 2022.
*/

#include <pwmWrite.h>

Pwm pwm = Pwm();

const int servo[3][6] = 
    {{26, 25, 33, 32, 16, 17},
      {14, 12, 13, 4, 2, 15},
      {23, 22, 21, 19, 18, 5}};
int pos = 0;

void setup() {
}

void loop() {
  for (pos = 0; pos <= 180; pos++) {  // go from 0-180 degrees
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 6; j++){
        pwm.writeServo(servo[i][j], pos);
      }
    }
    delay(25);
  }
  for (pos = 180; pos >= 0; pos--) {  // go from 180-0 degrees
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 6; j++){
        pwm.writeServo(servo[i][j], pos);
      }
    }
    delay(25);
  }
}
