// 大きくゆっくり振る(喜び)
#include <M5Stack.h>

int led1 = 16;

// PWMの設定
const double PWM_Hz = 50;     // PWM周波数
const uint8_t PWM_level = 16; // PWM 16bit(0～65535)

void setup()
{
  Serial.begin(115200);
  m5.begin();
  pinMode(led1, OUTPUT);
  // モータのPWMのチャンネル、周波数の設定
  ledcSetup((uint8_t)1, PWM_Hz, PWM_level);

  // モータのピンとチャンネルの設定
  ledcAttachPin(led1, 1);
}

void loop()
{
  M5.update();

  M5.Lcd.setCursor(60, M5.Lcd.height() - 16); // 画面左下にカーソルを移動0
  M5.Lcd.print("A");

  M5.Lcd.setCursor(M5.Lcd.width() / 2 - 8, M5.Lcd.height() - 16); // 画面中央下にカーソルを移動
  M5.Lcd.print("B");

  M5.Lcd.setCursor(M5.Lcd.width() - 70, M5.Lcd.height() - 16); // 画面右下にカーソルを移動-16
  M5.Lcd.print("C");
  if (M5.BtnA.wasPressed()) // 人感センサで動かなかったとき、ボタンで動かす。
  {
    M5.Lcd.setCursor(M5.Lcd.width() / 2, M5.Lcd.height() / 2); // 画面左下にカーソルを移動0
    M5.Lcd.print("Pressed");                                   // デバック用
    for (int i = 0; i < 5; i++)
    {
      for (int i = 3000; i <= 8000; i = i + 150)
      {
        ledcWrite(1, i);
        delay(30);
        Serial.printf("%d\n", i);
      }
      for (int i = 8000; i > 3000; i = i - 150)
      {
        ledcWrite(1, i);
        delay(30);
        Serial.printf("%d\n", i);
      }
    }
  }
}