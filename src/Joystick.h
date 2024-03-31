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
