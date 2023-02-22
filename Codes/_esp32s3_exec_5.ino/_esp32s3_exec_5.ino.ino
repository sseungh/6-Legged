//여러 행태의 움직임
#include <pwmWrite.h>
#include "BluetoothSerial.h"

Pwm pwm = Pwm();

enum {Idle, Walking, Hello, Back, Left, Right};
int State;
int curWalk = 0;
int curHello = 0;
int curBack = 0;
int curLeft = 0;
int curRight = 0;

const int servo[16] = {33, 32, 16, 17, 14, 12, 13, 4, 2, 15, 23, 22, 21, 19, 18, 5};
int stand[16] = {130, 50, 90, 90, 110, 120, 130, 130, 90, 90, 70, 70, 50, 50, 90, 90};

int walk[4][16] = {{110, 50, 110, 110, 90, 120, 110, 130, 110, 70, 70, 90, 50, 70, 110, 70},//1 2 5 구동 준비
                   {110, 50, 70 , 70 , 90, 120, 110, 130, 70 , 110, 70, 90, 50, 70, 70, 110},//1 2 5 구동 완료
                   {130, 70, 70 , 70, 110, 100, 130, 110, 70, 110, 90, 70, 70, 50, 70, 110}, //3 4 6 구동 준비
                   {130, 70, 110, 110, 110, 100, 130, 110, 110, 70, 90, 70, 70, 50, 110, 70}};//3 4 6 구동 완료

int turn[4][16] = {{110, 50, 70, 110, 90, 120, 110, 130, 70, 110, 70, 90, 50, 70, 110, 70}, // 1,2,5 구동 준비
                   {110, 50, 110, 70, 90, 120, 110, 130, 110, 70, 70, 90, 50, 70, 70, 110}, // 1,2,5 구동 완료
                   {130, 70, 110, 70, 110, 100, 130, 110, 110, 70, 90, 70, 70, 50, 70, 110}, //3,4,6 구동 준비
                   {130, 70, 70, 110, 110, 100, 130, 110, 70, 110, 90, 70, 70, 50, 110, 70}}; //3,4,6 구동 완료


int hello[2][16] =   {{80, 100, 90, 90, 70, 140, 80, 70, 90, 90, 110, 0, 100, 170, 90, 90},
                      {80, 100, 90, 90, 70, 170, 80, 10, 90, 90, 110, 30, 100, 110, 90, 90}};


BluetoothSerial BT;
TaskHandle_t TaskBT;

void BT_set(void *parameter){
  BT.begin("AntLeg");
  
  for(;;){
    if(BT.available()){
      char ch = BT.read();
      if(ch == '1'){
        State = Walking;
        curWalk = 0;
        BT.println("walk transition");
      }else if(ch == '2'){
        State = Idle;
        BT.println("idle transition");
      }else if(ch == '3'){
        State =  Hello;
        curHello = 0;
        BT.println("hello transition");
      }else if(ch == '4'){
        State = Back;
        curBack = 0;
        BT.println("back transition");
      }else if(ch == '5'){
        State = Left;
        curLeft = 0;
        BT.println("left turn transition");
      }else if(ch == '6'){
        State = Right;
        curRight = 0;
        BT.println("right turn transition");
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
    setMotors(stand, 200);
  }
  State = Idle;
}

void setMotors(int arr[] , int dtime){
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
  delay(dtime);
}

void loop() {
  if(State == Idle){
    setMotors(stand, 200);
  }else if(State == Walking){
    if(curWalk%2 == 0){
      setMotors(walk[curWalk], 100);
    }else if(curWalk == 1){
      int *temp = new int[16];
      memcpy(temp, walk[0], sizeof(int)*16);
      for(int i = 0; i < 20; i++){
        temp[2]-=2;
        temp[3]-=2;
        temp[8]-=2;
        temp[9]+=2;
        temp[14]-=2;
        temp[15]+=2;
        setMotors(temp, 50);
      }
      delete []temp;
    }else{
      int *temp = new int[16];
      memcpy(temp, walk[2], sizeof(int)*16);
      for(int i = 0; i < 20; i++){
        temp[2]+=2;
        temp[3]+=2;
        temp[8]+=2;
        temp[9]-=2;
        temp[14]+=2;
        temp[15]-=2;
        setMotors(temp, 50);
      }
      delete []temp;
    }
    curWalk = (curWalk+1)%4;
  }else if(State == Back){
    if((3-curBack)%2 == 1){
      setMotors(walk[(3-curBack)], 100);
    }else if((3-curBack) == 2){
      int *temp = new int[16];
      memcpy(temp, walk[3], sizeof(int)*16);
      for(int i = 0; i < 20; i++){
        temp[2]-=2;
        temp[3]-=2;
        temp[8]-=2;
        temp[9]+=2;
        temp[14]-=2;
        temp[15]+=2;
        setMotors(temp, 50);
      }
      delete []temp;
    }else{
      int *temp = new int[16];
      memcpy(temp, walk[1], sizeof(int)*16);
      for(int i = 0; i < 20; i++){
        temp[2]+=2;
        temp[3]+=2;
        temp[8]+=2;
        temp[9]-=2;
        temp[14]+=2;
        temp[15]-=2;
        setMotors(temp, 50);
       }
       delete []temp;
    }
    curBack = (curBack+1)%4;
  }else if(State == Hello){
    setMotors(hello[curHello], 1000);
    curHello = (curHello+1)%2;
  }else if(State == Left){
    if(curLeft%2 == 0){
      setMotors(turn[curLeft], 100);
    }else if(curLeft == 1){
      int *temp = new int[16];
      memcpy(temp, turn[0], sizeof(int)*16);
      for(int i = 0; i < 20; i++){
        temp[2]+=2;
        temp[3]-=2;
        temp[8]+=2;
        temp[9]-=2;
        temp[14]-=2;
        temp[15]+=2;
        setMotors(temp, 50);
      }
      delete []temp;
    }else{
      int *temp = new int[16];
      memcpy(temp, turn[2], sizeof(int)*16);
      for(int i = 0; i < 20; i++){
        temp[2]-=2;
        temp[3]+=2;
        temp[8]-=2;
        temp[9]+=2;
        temp[14]+=2;
        temp[15]-=2;
        setMotors(temp, 50);
      }
      delete []temp;
    }
    curLeft = (curLeft+1)%4;
  }else if(State == Right){
    if((3-curRight)%2 == 1){
      setMotors(turn[curRight], 100);
    }else if((3-curRight) == 2){
      int *temp = new int[16];
      memcpy(temp, turn[3], sizeof(int)*16);
      for(int i = 0; i < 20; i++){
        temp[2]+=2;
        temp[3]-=2;
        temp[8]+=2;
        temp[9]-=2;
        temp[14]-=2;
        temp[15]+=2;
        setMotors(temp, 50);
      }
      delete []temp;
    }else{
      int *temp = new int[16];
      memcpy(temp, turn[1], sizeof(int)*16);
      for(int i = 0; i < 20; i++){
        temp[2]-=2;
        temp[3]+=2;
        temp[8]-=2;
        temp[9]+=2;
        temp[14]+=2;
        temp[15]-=2;
        setMotors(temp, 50);
      }
      delete []temp;
    }
    curRight = (curRight+1)%4;
  }
}
