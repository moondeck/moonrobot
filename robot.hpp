/*
 * robot control firmware - robot.hpp
 * 2017 moondeck - MIT license
 */

#ifndef robot_h
#define robot_h

#define DIR_FORWARD   1
#define DIR_BACKWARD  2
#define DIR_LEFT      3
#define DIR_RIGHT     4

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

class Robot {
  public:
    Robot(int RIGHT_BW,int RIGHT_FW,int LEFT_BW,int LEFT_FW,int USTRIGG,int USECHO);
    void robotInit();
    void stopall();
    void goDirection(int dir);
    void turn(int dir);
    void wifiConnect(char ssid[], char pass[]);
    unsigned int senseDistance();
    void handleClient();
    void setStatusLED(uint8_t red, uint8_t green, uint8_t blue);
  private:
    int _RIGHT_BW;
    int _RIGHT_FW;
    int _LEFT_BW;
    int _LEFT_FW;

    int _USTRIGG;
    int _USECHO;

    int _PIXELPIN;
};

#endif

