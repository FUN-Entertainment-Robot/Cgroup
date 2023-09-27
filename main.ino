#include <M5Stack.h>

int led1 = 16;

//PWMの設定(SG90の仕様に合わせてPWMを50Hzに指定、指定する値の範囲は16bit(0～65535))
const double PWM_Hz = 50;   //PWM周波数
const uint8_t PWM_level = 16; //PWM 16bit(0～65535)

void setup() {
  Serial.begin(115200);
  m5.begin();
  pinMode(led1, OUTPUT);
  //モータのPWMのチャンネル、周波数の設定
  ledcSetup((uint8_t)1, PWM_Hz, PWM_level);

  //モータのピンとチャンネルの設定
  ledcAttachPin(led1, 1);
}

void loop() {
  for (int i = 2300; i <= 9000; i=i+200) { //+の次の数字を大きくすればするほど早くなる
    ledcWrite(1, i);
    delay(30);
    Serial.printf("%d\n", i);
  }
  for (int i = 9000; i > 2300; i=i-200) { //－の次の数字を大きくすればするほど早くなる
    ledcWrite(1, i);
    delay(30);
    Serial.printf("%d\n", i);
  }
}