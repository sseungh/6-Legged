/*
  Controls servo position from 0-180 degrees and back
  https://wokwi.com/projects/350037178957431378
  by dlloydev, December 2022.
*/
//걷기
#include <pwmWrite.h>

Pwm pwm = Pwm();

const int servo[16] = {33, 32, 16, 17, 14, 12, 13, 4, 2, 15, 23, 22, 21, 19, 18, 5};
int pos = 0;
int stand[16] = {80, 100, 90, 90, 70, 70, 80, 80, 90, 90, 110, 110, 100, 100, 90, 90};


//1 2 5 구동 준비
int pos0[16] = {65, 100, 100, 100, 
        70, 70, 65, 80, 100, 80, 
        110, 110, 100, 115, 100, 80};

//1 2 5 구동 완료
int pos1[16] = {65, 100, 80, 80, 
        70, 70, 65, 80, 80, 100, 
        110, 110, 100, 115, 80, 100};

//3 4 6 구동 준비
int pos2[16] = {80, 115, 80, 80, 
        70, 70, 80, 65, 80, 100, 
        110, 110, 115, 100, 80, 100};

//3 4 6 구동 완료
int pos3[16] = {80, 115, 100, 100, 
        70, 70, 80, 65, 100, 80, 
        110, 110, 115, 100, 100, 80};


void setup() {
  //서보 채널 정해주기, 처음 들어오는 순서대로 0번
  idle();
}

void loop() {
  for(int i = 0; i < 20; i++){
    idle();
  }

  for(int i = 0; i < 50; i++){
    setMotors(pos0);
  }

  for(int i = 0; i < 50; i++){
    setMotors(pos1);
  }

  for(int i = 0; i < 50; i++){
    setMotors(pos2);
  }

  for(int i = 0; i < 50; i++){
    setMotors(pos3);
  }
}

void idle(){
  setMotors(stand);
}


void setMotors(int arr[]){
  pwm.writeServo(servo[0], arr[0]);   //3번 중간다리 33
  pwm.writeServo(servo[1], arr[1]);  //5번 중간다리 32
  pwm.writeServo(servo[2], arr[2]);   //3번 첫다리  16
  pwm.writeServo(servo[3], arr[3]);   //5번 첫다리  17
  pwm.writeServo(servo[4], arr[4]);   //4번 끝다리  14
  pwm.writeServo(servo[5], arr[5]);   //2번 끝다리  12
  pwm.writeServo(servo[6], arr[6]);   //4번 중간다리 13
  pwm.writeServo(servo[7], arr[7]);   //2번 중간다리 4
  pwm.writeServo(servo[8], arr[8]);   //4번 첫다리  2
  pwm.writeServo(servo[9], arr[9]);   //2번 첫다리  15
  pwm.writeServo(servo[10], arr[10]); //1번 끝다리  23
  pwm.writeServo(servo[11], arr[11]); //6번 끝다리  22
  pwm.writeServo(servo[12], arr[12]); //1번 중간다리 21
  pwm.writeServo(servo[13], arr[13]); //6번 중간다리 19
  pwm.writeServo(servo[14], arr[14]);  //1번 첫다리  18
  pwm.writeServo(servo[15], arr[15]);  //6번 첫다리  5
  delay(100);
}
