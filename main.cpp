// 大きくゆっくり振る(喜び)
#include <Wire.h>                      //ライブラリのインクルード
#include <Adafruit_PWMServoDriver.h>
#include <M5Stack.h>

int servoHandRight_PIN = 0;
int servoHandLeft_PIN = 1;
int servoInsideTail_PIN = 2;
int servoOutsideTail_PIN = 3;

int initialPositionHandRight = 50;
int initialPositionHandLeft = 50;
int initialPositionInsideTail = 90;
int initialPositionOutsideTail = 30;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // PCA9685のI2Cアドレスを指定

#define SERVOMIN 110    // 最小パルス幅(~4096の範囲)
#define SERVOMAX 480    // 最大パルス幅(~4096の範囲)

int angle;

void servo_move(int n, int angle){
  angle = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(n, 0, angle);
}

void resetPosition(int delayTime){
  servo_move(servoHandRight_PIN, initialPositionHandRight);
  servo_move(servoHandLeft_PIN, initialPositionHandLeft);
  servo_move(servoInsideTail_PIN, initialPositionInsideTail);
  servo_move(servoOutsideTail_PIN, initialPositionOutsideTail);
  delay(delayTime);
}

void initializeAngle(){
  int positionHandRight = initialPositionHandRight;
  int positionHandLeft = initialPositionHandLeft;
  int positionInsideTail = initialPositionInsideTail;
  int positionOutsideTail = initialPositionOutsideTail;
}

//喜びの動き
void gladMove(){}

//驚きの動き
void surpriseMove(){}

//怒りの動き
void angerMovwe(){}

//威嚇
void Intimidation(){}

void setup()
{
  Serial.begin(115200);
  M5.begin();
  pwm.begin();
  pwm.setPWMFreq(50);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  M5.Lcd.setCursor(60, M5.Lcd.height() - 16); // 画面左下にカーソルを移動0
  M5.Lcd.print("A");

  M5.Lcd.setCursor(M5.Lcd.width() / 2 - 8, M5.Lcd.height() - 16); // 画面中央下にカーソルを移動
  M5.Lcd.print("B");

  M5.Lcd.setCursor(M5.Lcd.width() - 70, M5.Lcd.height() - 16); // 画面右下にカーソルを移動-16
  M5.Lcd.print("C");
  servo_move(servoHandRight_PIN, initialPositionHandRight);
  servo_move(servoHandLeft_PIN, initialPositionHandLeft);
  servo_move(servoInsideTail_PIN, initialPositionInsideTail);
  servo_move(servoOutsideTail_PIN, initialPositionOutsideTail);
  delay(1000);
}

void loop()
{
  M5.update();

  if (M5.BtnA.wasReleased()){}
}