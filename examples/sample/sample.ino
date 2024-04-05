#include <Joystick.h>

                          //Joystickオブジェクトを生成(X軸, Y軸, スイッチ)
Joystick joy(A0, A1, A2); //Generate a Joystick object (X-axis, Y-axis, Switch).

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

  Serial.print("Direction=");
  Serial.println(static_cast<uint8_t>(joy.getDirection()));

               //1秒待つ
  delay(1000); //Wait for 1 second.
}

