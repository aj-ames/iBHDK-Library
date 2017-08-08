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

//To use Core ESP8266 functionality
#include<ESP8266WiFi.h>

//Including NeoPixel Library to use onboard RGB rings
#include<Adafruit_NeoPixel.h>
#define BUTTON 4 //Push Button
#define RGB 12 //RGB Pin
#define RGB_COUNT 10 //Number of RGB's

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
    void RGBFade(uint32_t color);
    int readAnalog(int pin, bool displayLED);
    int readAnalog(int pin, bool displayLED, int logic);

  private:
    //For WiFi Credentials
    String ssid = "";
    String pass = "";
    //Used for time delays
    long timer = 0;
    //To count number of button clicks
    int click = 0;
    //To store button press state
    bool buttonState = false;
    //To store color
    uint32_t color;
    //To store brightness value
    uint8_t brightValue = 255;
}; //End of class

#endif
