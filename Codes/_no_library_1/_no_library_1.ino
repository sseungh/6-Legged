const int ledPin = 35;  // corresponds to GPIO 15

// setting PWM properties
const int ledChannel = 0;
const int freq = 50;
const int resolution = 16;

int deg, duty;

void setup()
{
  // PWM Setup
  ledcSetup(0, freq, resolution);  // PWM CH0, Frequncy 50 Hz, 16bit resolution
  ledcAttachPin(25, 0);        // PWM CH0을 GPIO 15번으로 출력
  //ledcAttachPin(26, 0);
}

void loop()
{
  for (deg = 0;deg <= 180; deg++) {
  servoWrite(ledChannel, deg);
  }
  for (deg = 180;deg >= 0; deg--) {
  servoWrite(ledChannel, deg);
  }
}

// deg는 0~180도 까지
void servoWrite(int ch, int deg)
{
    duty = map(deg, 0, 180, 1638, 8192);
    ledcWrite(ch, duty);
    delay(15);                             // delay를 줄이면 180도가 완전히 돌지 않음
}
