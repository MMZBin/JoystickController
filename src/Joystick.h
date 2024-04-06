/*
    MIT License

    Copyright (c) 2024 MOMIZICH

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef MMZ_JOYSTICK_H
#define MMZ_JOYSTICK_H

class Joystick {
public:
    enum class Dir : uint8_t {
        UP,         //338°~22°  (4方向モード:271°~45°)
        RIGHT_UP,   //23°~67°
        RIGHT,      //68°~112°  (4方向モード:46°~135°)
        RIGHT_DOWN, //113°~157°
        DOWN,       //158°~202° (4方向モード:136°~225°)
        LEFT_DOWN,  //203°~247°
        LEFT,       //248°~292° (4方向モード:226°~270°)
        LEFT_UP,    //293°~337°
        CENTER      //距離がdeadZone未満の場合
    };

    Joystick(const uint8_t xPin, const uint8_t yPin, const uint8_t swPin=0xFF, const uint8_t deadZone=10, const uint8_t rotate=0, const bool isFourSide=false);

    void calibrate(); //実行時にジョイスティックが中立状態である必要があります。

    int8_t getX() const;

    int8_t getY() const;

    bool getSW() const;

    uint16_t getAngle() const;

    uint8_t getDistance() const;

    Joystick::Dir getDirection() const;
    Joystick::Dir getDirection(const bool isFourSide) const;
    bool getDirection(const Dir dir) const;
    bool getDirection(const Dir dir, const bool isFourSide) const;

    bool isFourSideMode() const;
    void setFourSideMode(bool mode);

private:
    Joystick::Dir getDirEnum(const uint8_t index) const;

    static int8_t mapping(const uint16_t val, const int8_t error); //analogRead()の値をuint8_tの範囲にマッピングする

    const uint8_t X_PIN, Y_PIN, SW_PIN, DEAD_ZONE, ROTATE;
    int8_t xError_, yError_;

    bool isFourSide_;
};

#endif
