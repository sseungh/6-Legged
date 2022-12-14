//State 생성 + 블루투스
#include <pwmWrite.h>
#include "BluetoothSerial.h"

Pwm pwm = Pwm();

enum {Idle, Walking};
int State;
int curWalk = 0;

const int servo[16] = {33, 32, 16, 17, 14, 12, 13, 4, 2, 15, 23, 22, 21, 19, 18, 5};
int stand[16] = {80, 100, 90, 90, 70, 70, 80, 80, 90, 90, 110, 110, 100, 100, 90, 90};
int walk[4][16] = {{60, 100, 100, 100, 70, 70, 60, 80, 100, 80, 110, 110, 100, 120, 100, 80}, //1 2 5 구동 준비
                   {60, 100, 80, 80, 70, 70, 60, 80, 80, 100, 110, 110, 100, 120, 80, 100},   //1 2 5 구동 완료
                   {80, 120, 80, 80, 70, 70, 80, 60, 80, 100, 110, 110, 120, 100, 80, 100},   //3 4 6 구동 준비
                   {80, 120, 100, 100, 70, 70, 80, 60, 100, 80, 110, 110, 120, 100, 100, 80}};//3 4 6 구동 완료

BluetoothSerial BT;
TaskHandle_t TaskBT;

void BT_set(void *parameter){
  BT.begin("AntLeg");
  
  for(;;){
    if(BT.available()){
      char ch = BT.read();
      if(ch == '1'){
        State = Walking;
        BT.println("walk transition");
      }else if(ch == '2'){
        State = Idle;
        BT.println("idle transition");
      }
    }
  }
}

void setup() {
  xTaskCreatePinnedToCore(
    BT_set,  //함수 이름
    "TaskBT",    //Task 이름
    10000,      //스택 사이즈
    NULL,       //파라미터
    1,          //priority
    &TaskBT,     //Task Handle, Task를 감시하기 위함
    1);         //Core 1에서 실행
  delay(500);
  
  for(int i =0; i < 10; i++){
    setMotors(stand);
  }
  State = Idle;
}

void loop() {
  if(State == Idle){
    setMotors(stand);
  }else if(State == Walking){
    setMotors(walk[curWalk]);
    curWalk = (curWalk+1)%4;
  }
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
