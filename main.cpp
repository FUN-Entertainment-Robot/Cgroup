// 大きくゆっくり振る(喜び)
#include <Wire.h> //ライブラリのインクルード
#include <Adafruit_PWMServoDriver.h>
#include <M5Stack.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

int servoHandRight_PIN = 0;
int servoHandLeft_PIN = 1;
int servoInsideTail_PIN = 2;
int servoOutsideTail_PIN = 3;

int initialPositionHandRight = 70;
int initialPositionHandLeft = 10;
int initialPositionInsideTail = 85;
int initialPositionOutsideTail = 110;

int positionHandRight;
int positionHandLeft;
int positionInsideTail;
int positionOutsideTail;

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40); // PCA9685のI2Cアドレスを指定

#define SERVOMIN 110 // 最小パルス幅(~4096の範囲)
#define SERVOMAX 480 // 最大パルス幅(~4096の範囲)

#define MIC_Unit 36 // マイクのピン番号
#define Touch_SENSOR1 2
#define Touch_SENSOR2 5
#define Touch_SENSOR3 26

int angle;

void servo_move(int n, int angle)
{
  angle = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(n, 0, angle);
}

void resetPosition(int delayTime)
{
  servo_move(servoHandRight_PIN, initialPositionHandRight);
  servo_move(servoHandLeft_PIN, initialPositionHandLeft);
  servo_move(servoInsideTail_PIN, initialPositionInsideTail);
  servo_move(servoOutsideTail_PIN, initialPositionOutsideTail);
  delay(delayTime);
}

void initializeAngle()
{
  positionHandRight = initialPositionHandRight;
  positionHandLeft = initialPositionHandLeft;
  positionInsideTail = initialPositionInsideTail;
  positionOutsideTail = initialPositionOutsideTail;
}

void playMP3(const char *filename)
{
  file = new AudioFileSourceSD(filename);
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 1); // Output to builtInDAC
  out->SetOutputModeMono(true);
  out->SetGain(3.0);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
  while (mp3->isRunning())
  {
    if (!mp3->loop())
      mp3->stop();
  }
}

// 喜びの動き
void gladMove()
{
  initializeAngle();

  playMP3("/glad.mp3");
  positionInsideTail = 60; // 喜びのときのしっぽの初期位置60°
  positionHandRight = 0;
  servo_move(servoHandRight_PIN, positionHandRight);
  servo_move(servoHandLeft_PIN, positionHandLeft);
  servo_move(servoInsideTail_PIN, positionInsideTail);
  servo_move(servoOutsideTail_PIN, positionOutsideTail);
  delay(25);

  // しっぽの動き(左に寝かせてた場合)
  for (int count = 0; count < 4; count += 1) // しっぽ何往復させるか(一旦3回)
  {                                          // 初期値130°、動かす範囲は60°~0°(しっぽ)　50°~10°(左手)　0°~40°(右手)
    for (int count = 0; count < 10; count += 1)
    // しっぽを時計まわりの方向に動かす　右手を時計まわり　左手を半時計まわり
    {

      servo_move(servoHandRight_PIN, positionHandRight);
      servo_move(servoHandLeft_PIN, positionHandLeft);
      servo_move(servoInsideTail_PIN, positionInsideTail);
      servo_move(servoOutsideTail_PIN, positionOutsideTail);
      delay(25);
      positionInsideTail -= 6; // 角度を6°ずつ減らしてく(しっぽ)
      //positionOutsideTail += 8;
      positionHandRight += 4;  // 角度を4°ずつ増やしてく(右手)
      positionHandLeft += 4;   // 角度を4°ずつ減らしてく(左手)
    }                   // 戻るときのしっぽの初期位置0°
    for (int count = 0; count < 10; count += 1) // しっぽを半時計まわりの方向に動かす
    {
      servo_move(servoHandRight_PIN, positionHandRight);
      servo_move(servoHandLeft_PIN, positionHandLeft);
      servo_move(servoInsideTail_PIN, positionInsideTail);
      servo_move(servoOutsideTail_PIN, positionOutsideTail);
      delay(25);
      positionInsideTail += 6; // 角度を6°ずつ増やしてく(しっぽ)
      positionHandRight -= 4;  // 角度を4°ずつ減らしてく(右手)
      positionHandLeft -= 4;   // 角度を4°ずつ増やしてく(左手)
    }
  }
  resetPosition(100);
}

// 怒りの動き
void angerMove()
{
  initializeAngle();
  positionHandRight = initialPositionHandRight - 30;
  positionHandLeft = initialPositionHandLeft + 30;
  positionInsideTail = initialPositionInsideTail - 85;
  positionOutsideTail += 35; 
  servo_move(servoHandRight_PIN, positionHandRight);
  servo_move(servoHandLeft_PIN, positionHandLeft);
  servo_move(servoInsideTail_PIN, positionInsideTail);
  servo_move(servoOutsideTail_PIN, positionOutsideTail);
  delay(100);
  positionHandRight += 30;
  positionHandLeft -= 30;
  positionOutsideTail -= 29;
  servo_move(servoHandRight_PIN, positionHandRight);
  servo_move(servoHandLeft_PIN, positionHandLeft);
  servo_move(servoInsideTail_PIN, positionInsideTail);
  servo_move(servoOutsideTail_PIN, positionOutsideTail);
  delay(150);
  playMP3("/anger.mp3");
  for (int count = 0; count < 3; count += 1)
  {
    for (int count = 0; count <= 2; count += 1)
    {
      servo_move(servoHandRight_PIN, positionHandRight);
      servo_move(servoHandLeft_PIN, positionHandLeft);
      servo_move(servoInsideTail_PIN, positionInsideTail);
      servo_move(servoOutsideTail_PIN, positionOutsideTail);
      delay(70);
      positionInsideTail += 13;
      positionOutsideTail += 3;
    }

    for (int count = 0; count <= 2; count += 1)
    {
      servo_move(servoHandRight_PIN, positionHandRight);
      servo_move(servoHandLeft_PIN, positionHandLeft);
      servo_move(servoInsideTail_PIN, positionInsideTail);
      servo_move(servoOutsideTail_PIN, positionOutsideTail);
      delay(70);
      positionInsideTail -= 13;
      positionOutsideTail -= 3;
    }
  }

  for (int count = 0; count < 85; count += 1)
  {
    servo_move(servoHandRight_PIN, positionHandRight);
    servo_move(servoHandLeft_PIN, positionHandLeft);
    servo_move(servoInsideTail_PIN, positionInsideTail);
    servo_move(servoOutsideTail_PIN, positionOutsideTail);
    delay(10);
    positionInsideTail += 1;
  }
  resetPosition(50);
}

// 威嚇
void Intimidation()
{
  initializeAngle();

  playMP3("/Intimidation.mp3");
  servo_move(servoHandRight_PIN, positionHandRight);
  servo_move(servoHandLeft_PIN, positionHandLeft);
  servo_move(servoInsideTail_PIN, positionInsideTail);
  servo_move(servoOutsideTail_PIN, positionOutsideTail);
  delay(100);
  positionHandRight -= 70;
  positionHandLeft += 70;
  positionInsideTail -= 85;

  for (int count = 0; count < 35; count += 1)
  {
    servo_move(servoHandRight_PIN, positionHandRight);
    servo_move(servoHandLeft_PIN, positionHandLeft);
    servo_move(servoInsideTail_PIN, positionInsideTail);
    servo_move(servoOutsideTail_PIN, positionOutsideTail);
    delay(40);
    positionHandRight += 2;
    positionHandLeft -= 2;
    positionInsideTail += 2;
  }
  resetPosition(100);
}

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
  resetPosition(1000);

  pinMode(MIC_Unit, INPUT);
  pinMode(Touch_SENSOR1, INPUT);
  pinMode(Touch_SENSOR2, INPUT);
  pinMode(Touch_SENSOR3, INPUT);
}

void loop()
{

  int value_m = analogRead(MIC_Unit);
  int value_t1 = digitalRead(Touch_SENSOR1);
  int value_t2 = digitalRead(Touch_SENSOR2);
  int value_t3 = digitalRead(Touch_SENSOR3);
  Serial.printf("%d\n", value_m);
  delay(1000);
  if (value_m >= 165)
  {
    M5.Lcd.setCursor(M5.Lcd.width() / 2, M5.Lcd.height() / 2); // 画面左下にカーソルを移動0
    M5.Lcd.print("Intimidation");
    Intimidation();
  }
  else if (value_t2 == HIGH)
  {
    M5.Lcd.setCursor(M5.Lcd.width() / 2, M5.Lcd.height() / 2); // 画面左下にカーソルを移動0
    M5.Lcd.print("Glad");
    gladMove();
  }
  else if (value_t1 == HIGH || value_t3 == HIGH)
  {
    M5.Lcd.setCursor(M5.Lcd.width() / 2, M5.Lcd.height() / 2); // 画面左下にカーソルを移動0
    M5.Lcd.print("Anger");
    angerMove();
  }
}