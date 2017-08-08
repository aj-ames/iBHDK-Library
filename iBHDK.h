/*
Higher level wrapper class to simplify the learning curve for newbies.
Developed to be used for iB IoT HDK v1.
Based on ESP8266.
Consists of 10 onboard RGB lights.
Also consists of push button.


Developed at iBHubs.
*/

#ifndef IBHDK_H
#define IBHDK_H

#include<ESP8266WiFi.h>

#include<Adafruit_NeoPixel.h>
#define BUTTON 4
#define RGB 12
#define RGB_COUNT 10

class iBHDK {
  public:
    void begin();
    void brightness(uint8_t bright);
    void RGBColor(uint32_t color, int delayValue);
    void RGBlooper(uint32_t color, int delayValue, int cycles);
    void RGBWipelooper(uint32_t color, int delayValue, int cycles);
    void connectWiFi();
    String credentials();
    void rainbow();
    void RGBRandom();
    void RGBFade();
    int readAnalog(int pin, bool displayLED);
    int readAnalog(int pin, bool displayLED, int logic);

  private:
    String ssid = "";
    String pass = "";
    long timer = 0;
    int click = 0;
    bool buttonState = false;
    uint32_t color;
    uint8_t brightValue = 255;

};

#endif
