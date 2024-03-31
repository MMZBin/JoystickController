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
    Joystick(uint8_t xPin, uint8_t yPin, uint8_t swPin);

    void calibrate(); //実行時にジョイスティックが中立状態である必要があります。

    int8_t getX();

    int8_t getY();

    bool getSW();

    uint16_t getAngle();

    uint8_t getDistance();
private:
    static int8_t mapping(uint16_t val, int8_t error); //analogRead()の値をuint8_tの範囲にマッピングする

    uint8_t xPin_, yPin_, swPin_;
    int8_t xError_, yError_;


    static constexpr float twicePi_ = 3.1415926535897932384626433832795 * 2;
};

#endif
