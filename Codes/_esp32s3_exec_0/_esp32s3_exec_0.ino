/*
  Controls servo position from 0-180 degrees and back
  https://wokwi.com/projects/350037178957431378
  by dlloydev, December 2022.
*/
//일어서기
#include <pwmWrite.h>

Pwm pwm = Pwm();

const int servo[16] = {33, 32, 16, 17, 14, 12, 13, 4, 2, 15, 23, 22, 21, 19, 18, 5};
int pos = 0;
void setup() {
  //서보 채널 정해주기, 처음 들어오는 순서대로 0번
  pwm.writeServo(servo[0], 80);   //3번 중간다리 33
  pwm.writeServo(servo[1], 100);  //5번 중간다리 32
  pwm.writeServo(servo[2], 90);   //3번 첫다리  16
  pwm.writeServo(servo[3], 90);   //5번 첫다리  17
  pwm.writeServo(servo[4], 70);   //4번 끝다리  14
  pwm.writeServo(servo[5], 70);   //2번 끝다리  12
  pwm.writeServo(servo[6], 80);   //4번 중간다리 13
  pwm.writeServo(servo[7], 80);   //2번 중간다리 4
  pwm.writeServo(servo[8], 90);   //4번 첫다리  2
  pwm.writeServo(servo[9], 90);   //2번 첫다리  15
  pwm.writeServo(servo[10], 110); //1번 끝다리  23
  pwm.writeServo(servo[11], 110); //6번 끝다리  22
  pwm.writeServo(servo[12], 100); //1번 중간다리 21
  pwm.writeServo(servo[13], 100); //6번 중간다리 19
  pwm.writeServo(servo[14], 90);  //1번 첫다리  18
  pwm.writeServo(servo[15], 90);  //6번 첫다리  5
  delay(25);
}

void loop() {
  pwm.writeServo(servo[0], 80);   //3번 중간다리 33
//  delay(25);
  pwm.writeServo(servo[1], 100);  //5번 중간다리 32
//  delay(25);
  pwm.writeServo(servo[2], 90);   //3번 첫다리  16
//  delay(25);
  pwm.writeServo(servo[3], 90);   //5번 첫다리  17
//  delay(25);
  pwm.writeServo(servo[4], 70);   //4번 끝다리  14
//  delay(25);
  pwm.writeServo(servo[5], 70);   //2번 끝다리  12
//  delay(25);
  pwm.writeServo(servo[6], 80);   //4번 중간다리 13
//  delay(25);
  pwm.writeServo(servo[7], 80);   //2번 중간다리 4
//  delay(25);
  pwm.writeServo(servo[8], 90);   //4번 첫다리  2
//  delay(25);
  pwm.writeServo(servo[9], 90);   //2번 첫다리  15
//  delay(25);
  pwm.writeServo(servo[10], 110); //1번 끝다리  23
//  delay(25);
  pwm.writeServo(servo[11], 110); //6번 끝다리  22
//  delay(25);
  pwm.writeServo(servo[12], 100); //1번 중간다리 21
//  delay(25);
  pwm.writeServo(servo[13], 100); //6번 중간다리 19
//  delay(25);
  pwm.writeServo(servo[14], 90);  //1번 첫다리  18
//  delay(25);
  pwm.writeServo(servo[15], 90);  //6번 첫다리  5
  delay(100);
}
