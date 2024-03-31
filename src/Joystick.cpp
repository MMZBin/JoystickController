#include "Arduino.h"
#include "Joystick.h"

Joystick::Joystick(uint8_t xPin, uint8_t yPin, uint8_t swPin) : xPin_(xPin), yPin_(yPin), swPin_(swPin), xError_(0), yError_(0) {
    pinMode(xPin_, INPUT);
    pinMode(yPin_, INPUT);
    pinMode(swPin_, INPUT_PULLUP);
}

void Joystick::calibrate() {
    //補正0で読み取った値を代入
    xError_ = mapping(analogRead(xPin_), 0);
    yError_ = mapping(analogRead(yPin_), 0);
}

int8_t Joystick::getX() { return mapping(analogRead(xPin_), xError_); }
int8_t Joystick::getY() { return mapping(analogRead(yPin_), yError_); }

bool Joystick::getSW() { return !digitalRead(swPin_); }

uint16_t Joystick::getAngle() {
    float r = atan2(getY(), getX());
    if (r < 0) { r += twicePi_; } //角度が負の場合は正の範囲に直す
    return r * 360 / twicePi_; //度数法に変換する
}

uint8_t Joystick::getDistance() {
    int32_t x = getX();
    int32_t y = getY();
    return sqrt(x*x + y*y);
}

int8_t Joystick::mapping(uint16_t val, int8_t error) {
    int16_t mappedVal = (val / 4) - (128 + error);

    //値がint8_tの範囲を超えている場合はクリップする
    if (mappedVal > 127) { mappedVal = 127; }
    else if (mappedVal < -128) { mappedVal = -128; }

    return mappedVal;
}
