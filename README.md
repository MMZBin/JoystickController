This library uses English that has been machine-translated from Japanese.

# JoystickController

このライブラリはジョイスティックの制御を簡単にするためのものです。

This library is designed to simplify joystick control.

## 機能 Functions

#### `enum class Dir`
  - ジョイスティックが向いている方向を表します。 This indicates the direction the joystick is pointing.
    - UP
    - RIGHT_UP
    - RIGHT
    - RIGHT_DOWN
    - DOWN
    - LEFT_DOWN
    - LEFT
    - LEFT_UP
    - CENTER 
  - 例 example: `JoyStick::Dir::UP`

#### `Joystick(xPin, yPin, swPin, deadZone)`
  - Joystickオブジェクトを生成します。(x軸のピン, y軸のピン, スイッチのピン, デッドゾーン) Create a Joystick object. (x-axis pin, y-axis pin, switch pin, dead zone)
  - xPinとyPinはアナログ入力ピンに接続されている必要があります。 xPin and yPin should be connected to analog input pins.
  - デッドゾーンは省略可能で、その場合は10に設定されます。 The dead zone is optional, and if omitted, it will be set to 10.
  - 例 example: `JoyStick joy(A0, A1, 2, 50)`

#### `void calibrate()`
  - ジョイスティックの誤差を補正します。 Correct for any errors in the joystick.
  - 実行された時点でジョイスティックが中立状態にある必要があります。 The joystick should be in a neutral position when this is executed.
  - 例 example: `joy.calibrate()`

#### `int8_t getX()`
  - ジョイスティックのX軸方向の傾きを取得します。 Retrieve the tilt of the joystick in the X-axis direction.
    - 範囲:-128~127 Range: -128 to 127
  - 例 example: `int8_t x = joy.getX()`
   
#### `int8_t getY()`
  - ジョイスティックのY軸方向の傾きを取得します。 Retrieve the tilt of the joystick in the Y-axis direction.
    - 範囲:-128~127 Range: -128 to 127
  - 例 example: `int8_t y = joy.getY()`
   
#### `bool getSW()`
  - ジョイスティックの押し込みの状態を取得します。 Retrieve the state of the joystick button press.
    - 範囲:true/false Range: true/false
  - 例 example: `bool sw = joy.getSW()`
   
#### `uint16_t getAngle()`
  - ジョイスティックの角度を取得します。 Retrieve the angle of the joystick.
  - 中立状態では0°になります。 It is 0° when in the neutral position.
    - 範囲:0~360 Range: 0 to 360
  - 例 example: `uint16_t angle = joy.getAngle()`

#### `uint8_t getDistance()`
  - ジョイスティックの中心からの距離を取得します。 Retrieve the distance from the center of the joystick.
    - 範囲:0~181 Range: 0 to 181
  - 例 example: `uint8_t distance = joy.getDistance()`
   
#### `JoyStick::Dir getDirection(bool isFourSide)`
  - ジョイスティックが向いている方向を取得します。 Retrieves the direction in which the joystick is pointing.
  - 距離がデッドゾーン内だった場合はCENTERを返します。 Returns CENTER if the distance is within the dead zone.
  - 引数は省略可能で、省略した場合はfalse(8方向モード)になります。 The argument is optional, and if omitted, it defaults to false (8-direction mode).
    - isFourSide
      - trueを指定すると4方向モード(UP, DOWN, RIGHT, LEFT)になります。 Specifying true will set it to 4-direction mode (UP, DOWN, RIGHT, LEFT).
      - falseを指定すると8方向モードになります。  Specifying false will set it to 8-direction mode.
  - 例 example: `JoyStick::Dir direction = joy.getDirection()`
   
## 使用例 Usage Example

```
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

               //1秒待つ
  delay(1000); //Wait for 1 second.
}


```
