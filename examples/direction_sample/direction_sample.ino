#include <Joystick.h>

Joystick joy(A0, A1, A2);

void setup() {
  joy.calibrate();

  pinMode(13, OUTPUT);
}

void loop() {
  Joystick::Dir direction = joy.getDirection();

  if (direction == Joystick::Dir::UP) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  //このように書くこともできます。
  //You can also write it like this.
  /*
    if (joy.getDirection(Joystick::Dir::UP)) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
  */
}
