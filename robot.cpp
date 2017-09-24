/*
 * moonrobot control firmware - robot.cpp
 * 2017 moondeck - MIT license
 */


#include "robot.hpp"

int curr_direction = 0;

/*
 * Initialization function:
 */

WiFiServer robotServer(23);
WiFiClient serverClient;

#define PIXELPIN D2

/*
 * please dont use values over 32 as it hurts to look at
 * also, brightness limiting doesnt work for some reason
 */

#define STATUS_CONNECTING 0,0,32
#define STATUS_CONNECTED 0,32,0

Adafruit_NeoPixel statusPixel = Adafruit_NeoPixel(1, PIXELPIN, NEO_GRB + NEO_KHZ800);

Robot::Robot(int RIGHT_BW, int RIGHT_FW, int LEFT_BW, int LEFT_FW, int USTRIGG, int USECHO) {
  pinMode(RIGHT_BW, OUTPUT);
  pinMode(RIGHT_FW, OUTPUT);
  pinMode(LEFT_BW, OUTPUT);
  pinMode(LEFT_FW, OUTPUT);

  //robot motor controller pins

  _RIGHT_BW = RIGHT_BW;
  _RIGHT_FW = RIGHT_FW;
  _LEFT_BW = LEFT_BW;
  _LEFT_FW = LEFT_FW;

  //robot ultrasonic sensor pins

  pinMode(USTRIGG, OUTPUT);
  pinMode(USECHO, INPUT);

  _USTRIGG = USTRIGG;
  _USECHO = USECHO;

  //NeoPixel (AKA WS2812B) pins

  pinMode(PIXELPIN, OUTPUT);
  
  statusPixel.begin();
  
}

/*
 * Robot::stopall() - Stops all motors
 */

void Robot::setStatusLED(uint8_t red, uint8_t green, uint8_t blue) {
  statusPixel.setPixelColor(0, statusPixel.Color(red, green, blue));
  statusPixel.show();
  
}

void Robot::stopall() {
  curr_direction = 0;
  
  digitalWrite(_LEFT_FW, LOW);
  digitalWrite(_RIGHT_FW, LOW);
  digitalWrite(_LEFT_BW, LOW);
  digitalWrite(_RIGHT_BW, LOW);
}

/*
 * Robot::goDirection(dir) - makes the robot go in dir direction
 * Stops all previous movement
 */

void Robot::goDirection(int dir) {
  stopall();
  
  switch (dir) {
    case DIR_FORWARD:
      digitalWrite(_LEFT_FW, HIGH);
      digitalWrite(_RIGHT_FW, HIGH);
      break;
    case DIR_BACKWARD:
      digitalWrite(_LEFT_BW, HIGH);
      digitalWrite(_RIGHT_BW, HIGH);
      break;
    case DIR_LEFT:
      digitalWrite(_LEFT_BW, HIGH);
      digitalWrite(_RIGHT_FW, HIGH);
      break;
    case DIR_RIGHT:/*
 * robot control firmware
 * 2017 moondeck - MIT license
 */
      digitalWrite(_LEFT_FW, HIGH);
      digitalWrite(_RIGHT_BW, HIGH);
      break;
      
  }

  curr_direction = dir;
  
}

/*
 * Robot::turn(dir) - turns the robot towards dir WHILE its driving
 * TODO: use degrees instead of fixed time
 */
/*
 * robot control firmware
 * 2017 moondeck - MIT license
 */
void Robot::turn(int dir) {
  
}

/*
 * Robot::wifiConnect(ssid, pass) - Connects the ESP8266 SoC to WiFi network "ssid" using password "pass"
 */

void Robot::wifiConnect(char ssid[], char pass[]) {
  setStatusLED(STATUS_CONNECTING);
  Serial.printf("\n\rattempting wireless connection to ssid: ");
  Serial.printf(ssid);
  Serial.printf(" with password: ");
  Serial.printf(pass);


  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(3000);
  }

  Serial.println("\n\rCONNECTION SUCCESSFUL");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.print(ip);
  Serial.print(" MAC: ");
  Serial.println(WiFi.macAddress());
  setStatusLED(STATUS_CONNECTED);
}

unsigned int Robot::senseDistance() {
  digitalWrite(_USTRIGG, LOW);
  delay(100);
  digitalWrite(_USTRIGG, HIGH);
  delayMicroseconds(5);
  digitalWrite(_USTRIGG, LOW);

  unsigned int US_time = pulseIn(_USECHO, HIGH); // pulseIn waits for the pulse, measures it, and then returns its length in ms. The last argument is timeout in ms

  unsigned int cm = (US_time / 58);

  
  Serial.printf("Ultrasonic sensed distance (cm) :  ");
  Serial.println(cm);
  delay(100);
  
  
  return cm;

}

void Robot::handleClient() {
  
}

