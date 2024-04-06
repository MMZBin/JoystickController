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

#### `Joystick(uint8_t xPin, uint8_t yPin, uint8_t swPin, uint8_t deadZone, uint8_t rotate, bool isFourSide)`
  - Joystickオブジェクトを生成します。(x軸のピン, y軸のピン, スイッチのピン, デッドゾーン) Create a Joystick object. (x-axis pin, y-axis pin, switch pin, dead zone, rotate, four side mode)
  - xPinとyPinはアナログ入力ピンに接続されている必要があります。 xPin and yPin should be connected to analog input pins.
  - 第三引数以降は省略可能です。 The third argument onwards is optional.
    - `xPin`:ジョイスティックのX軸方向の傾きが入力されるピン Pin for input of the joystick's tilt in the X-axis direction.
    - `yPin`:ジョイスティックのY軸方向の傾きが入力されるピン  Pin for input of the joystick's tilt in the Y-axis direction.
    - `swPin`:ジョイスティックのスイッチ(存在しない場合は省略するか255を指定してください。) The joystick switch (if it doesn't exist, please either omit it or specify 255).
    - `deadZone`:ジョイスティックのデッドゾーン(中立範囲) デフォルト値は10です。  Dead zone (neutral range) of the joystick. Default value is 10.
    - `rotate`:ジョイスティックの向き(0=0°/1=90°/2=180°/3=270°) デフォルト値は0です。 Rotation of the joystick (0=0°/1=90°/2=180°/3=270°). Default value is 0.
    - `isFourSide`:方向を4方向で表現するか8方向で表現するかを指定します。 デフォルト値はfalseです。 Specifies whether to express the direction in 4 directions or 8 directions.  Default value is false.
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
    - isFourSide
      - 省略可能で、省略した場合は全体の設定が適用されます。 Optional, and if omitted, the overall settings will be applied.
      - trueを指定すると4方向モード(UP, DOWN, RIGHT, LEFT)になります。 Specifying true will set it to 4-direction mode (UP, DOWN, RIGHT, LEFT).
      - falseを指定すると8方向モードになります。  Specifying false will set it to 8-direction mode.
  - 例 example: `JoyStick::Dir direction = joy.getDirection()`

#### `bool getDirection(Dir dir, bool isFourSide)`
  - ジョイスティックが指定した方向を向いているか調べます。 Checks if the joystick is pointing in the specified direction.
  - 第二引数は省略可能で、省略した場合は全体の設定が適用されます。 The second argument is optional, and if omitted, the overall settings will be applied.
  - 他の仕様は上と同じです。 Other specifications are the same as above.
  - 例 example:`if (joy.getDirection(Joystick::Dir::UP)) {  }`

#### `bool isFourSideMode()`
  - 4方向モードが有効かどうかを調べます。 Checks if 4-direction mode is enabled.
    - 4方向モードならtrue, 8方向モードならfalseを返します。 Returns true if 4-direction mode is enabled, false if 8-direction mode is enabled.
  - 例 example:`bool mode = joy.isFourSideMode()`
   
#### `void setFourSideMode(bool mode)`
  - 4方向モードか8方向モードかを設定します。 Sets whether it's in 4-direction mode or 8-direction mode.
    - trueで4方向モード,falseで8方向モードに設定されます。 Sets to 4-direction mode if true, and 8-direction mode if false.
  - 例 example:`joy.setFourSideMode(true)`
   
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
