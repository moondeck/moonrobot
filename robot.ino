/*
 * moonrobot control firmware
 * 2017 moondeck - MIT license
 */

#include "robot.hpp"

#define RIGHT_BACKWARD D0
#define RIGHT_FORWARD  D5

#define LEFT_BACKWARD  D7
#define LEFT_FORWARD   D6

#define ULTRATRIGG     D2
#define ULTRAECHO      D1

char bootmessage[] = "moonrobot firmware rev 2309, 2017 moondeck";


Robot robot(RIGHT_BACKWARD, RIGHT_FORWARD, LEFT_BACKWARD, LEFT_FORWARD, ULTRATRIGG, ULTRAECHO);

void setup() {
  Serial.begin(115200);
  Serial.printf("\n\n\n");
  Serial.println(bootmessage);
  robot.wifiConnect("freewlan", "k*o*s*k*i");
}

void loop() {
  robot.handleClient();

}
