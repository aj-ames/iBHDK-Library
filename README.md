# iBHDK-Library

Higher level wrapper class to simplify the learning curve for newbies.
Developed to be used for iB IoT HDK v1.
Based on ESP8266.
Consists of 10 onboard RGB lights.
Also consists of push button.

Function Explaination:

1. begin() - Used to initialize the RGB ring and setup WiFi if needed.

2. brightness(uint8_t) - To set brightness value of RGB ring and store the value in brightValue for further use.

3. RGBColor(uint32_t color, int delayValue) - To set color to the RGB ring.

4.void RGBlooper(uint32_t color, int delayValue, int cycles) - Loops A color and clear for entered number of cycles.

5. void RGBWipelooper(uint32_t color, int delayValue, int cycles) - Loops Wipe of a color for entered number of cycles.

6. void connectWiFi() - connectWiFi is used to setup a WiFi connection. User enters SSID and PSK and WiFi.begin(ssid,psk) is called.

7. String credentials() - credentials is used to input the ssid and psk string from the user.

8. void rainbow() - It displays rainbow colors on the RGB ring.

9. void RGBRandom() - Generates a random color on a random RGB.

10. void RGBFade(uint32_t color) - Fade pattern for RGB ring.

11. int readAnalog(int pin, bool displayLED) - It reads an Analog Value from A0 pin of the IoTHDK and makes its value to the RGB ring.

12. int readAnalog(int pin, bool displayLED, int logic) - Overload function. Similar to previous readAnalog, however this consists of logic parameter.
If Logic = 0, Low Color = Green, Mid Color = Yellow, High Color = Red
If Logic = 1, Low Color = Red, Mid Color = Yellow, High Color = Green




Developed at iBHubs.
