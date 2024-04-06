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

#include <Arduino.h>
#include "Joystick.h"

#define TWICE_PI (3.1415926535897932384626433832795 * 2)

Joystick::Joystick(const uint8_t xPin, const uint8_t yPin, const uint8_t swPin, const uint8_t deadZone, const uint8_t rotate, const bool isFourSide)
 : X_PIN(xPin), Y_PIN(yPin), SW_PIN(swPin), DEAD_ZONE(deadZone), ROTATE(4 - (rotate % 4)), xError_(0), yError_(0), isFourSide_(isFourSide) {
    pinMode(X_PIN, INPUT);
    pinMode(Y_PIN, INPUT);
    if (swPin != 0xFF) { pinMode(SW_PIN, INPUT_PULLUP); }
}

void Joystick::calibrate() {
    //補正0で読み取った値を代入
    xError_ = mapping(analogRead(X_PIN), 0);
    yError_ = mapping(analogRead(Y_PIN), 0);
}

int8_t Joystick::getX() const { return mapping(analogRead(X_PIN), xError_); }
int8_t Joystick::getY() const { return mapping(analogRead(Y_PIN), yError_); }

bool Joystick::getSW() const { return (SW_PIN == 0xFF) ? false : !digitalRead(SW_PIN); }

uint16_t Joystick::getAngle() const {
    float r = atan2(getY(), getX());
    if (r < 0) { r += TWICE_PI; } //角度が負の場合は正の範囲に直す
    return r * 360 / TWICE_PI; //度数法に変換する
}

uint8_t Joystick::getDistance() const {
    int32_t x = getX();
    int32_t y = getY();
    return sqrt(x*x + y*y);
}

Joystick::Dir Joystick::getDirection() const { return getDirection(isFourSide_); }
Joystick::Dir Joystick::getDirection(const bool isFourSide) const {
    if (getDistance() < DEAD_ZONE) { return Dir::CENTER; }

    uint16_t angle = getAngle();

    //4方向モード(上下左右)の場合はこのブロックの中
    if (isFourSide) {
        //一方向あたり90°(正確には89°)
        //45°(Dir::UPの90°の半分)スタート+90°刻みで判定していく
        for (uint8_t i = 0; i < 4; i++) {
            if (angle < (45+(90*i))) {
                return getDirEnum(i * 2);
            }
        }

        return static_cast<Dir>(ROTATE*2);
    }

    //方向一つあたり45°(正確には44°)
    //22°(Dir::UPの45°の半分)スタート+45°刻みで判定していく
    for (uint8_t i = 0; i < 8; i++) {
        if (angle < (22+(45*i))) {
            return getDirEnum(i);
        }
    }
    return static_cast<Dir>(ROTATE*2);
}

bool Joystick::getDirection(const Dir dir) const { return getDirection(dir, isFourSide_); }
bool Joystick::getDirection(const Dir dir, const bool isFourSide) const {
    return getDirection(isFourSide) == dir;
}

bool Joystick::isFourSideMode() const { return isFourSide_; }
void Joystick::setFourSideMode(bool mode) { isFourSide_ = mode; }

Joystick::Dir Joystick::getDirEnum(const uint8_t index) const {
    return static_cast<Dir>((index + (ROTATE*2)) % 8);
}

int8_t Joystick::mapping(const uint16_t val, const int8_t error) {
    int16_t mappedVal = (val >> 2) - (128 + error); //4で割って0が中心になるようにオフセットする

    //値がint8_tの範囲を超えている場合はクリップする
    if (mappedVal > 127) { mappedVal = 127; }
    else if (mappedVal < -128) { mappedVal = -128; }

    return mappedVal;
}

#undef TWICE_PI
