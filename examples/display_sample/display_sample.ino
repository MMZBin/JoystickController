#include <Joystick.h>

const uint8_t xPin = A0;
const uint8_t yPin = A1;
const uint8_t swPin = A2;

const uint8_t deadZone = 10;   //距離が10以内なら中立として扱う
const uint8_t rotate = 0;      //ジョイスティックの向きを90°単位で設定(0~3)
const bool isFourSide = false; //ジョイスティックの向きを8方向で表現する

//Joystickオブジェクトを生成(X軸, Y軸, スイッチ, デッドゾーン, ジョイスティックの向き(0~3), 4方向モードかどうか)
//Generate a Joystick object (X-axis, Y-axis, Switch, dead zone, The orientation of the joystick(0~3), Whether it is in 4-direction mode or not).
Joystick joy(xPin, yPin, swPin, deadZone, rotate, isFourSide);

void setup() {
                      //シリアル通信を開始(表示用)
  Serial.begin(9600); //Start serial communication (for display).

                   //ジョイスティックの補正(必須ではありません)
  joy.calibrate(); //Calibrate the joystick (optional).
}

void loop() {
  //X軸の値を表示(-128~127)
  //Display X-axis value (-128 to 127).
  Serial.print("X=");
  Serial.println(joy.getX());

  //Y軸の値を表示(-128~127)
  //Display Y-axis value (-128 to 127).
  Serial.print("Y=");
  Serial.println(joy.getY());

  //スイッチの状態を表示(true/false)
  //Display Switch state (true/false).
  Serial.print("SW=");
  Serial.println(joy.getSW());

  //ジョイスティックの角度を表示(0~360)
  //Display joystick angle (0 to 360).
  Serial.print("Angle=");
  Serial.println(joy.getAngle());

  //ジョイスティックが中心からどれだけ離れているかを表示(0~180)
  //Display how far the joystick is from the center (0 to 180).
  Serial.print("Distance=");
  Serial.println(joy.getDistance());

  //ジョイスティックが向いている方向を表示(数値型に変換しているので0~8の整数で表示されます。)
  //Displaying the direction in which the joystick is pointing (as it's being converted to a numerical type, it will be displayed as an integer from 0 to 8).
  Serial.print("Direction=");
  Serial.println(static_cast<uint8_t>(joy.getDirection()));

               //1秒待つ
  delay(1000); //Wait for 1 second.
}

