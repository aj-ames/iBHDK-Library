/*
Higher level wrapper class to simplify the learning curve for newbies.
Developed to be used for iB IoT HDK v1.
Based on ESP8266.
Consists of 10 onboard RGB lights.
Also consists of push button.


Developed at iBHubs.
*/

#include<iBHDK.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(RGB_COUNT, RGB, NEO_GRB + NEO_KHZ800);
uint32_t red = pixels.Color(255,0,0);
uint32_t green = pixels.Color(0,255,0);
uint32_t blue = pixels.Color(0,0,255);
uint32_t yellow = pixels.Color(255,255,0);
uint32_t purple = pixels.Color(148,0,211);
uint32_t white = pixels.Color(255,255,255);
uint32_t black = pixels.Color(0,0,0);

void iBHDK::begin() {
  pinMode(RGB,OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pixels.begin();
  RGBColor(black, 0);
  Serial.println("****************************************");
  Serial.println("Initializing..");
  Serial.println("****************************************");
  rainbow();
  RGBColor(black, 0);
  delay(10);
  Serial.println("****************************************");
  Serial.println("Click button once to setup WiFi");
  Serial.println("Press button twice to skip WiFi setup");
  Serial.println("****************************************");
  Serial.println();
  timer = millis();
  while(millis() - timer < 5000) {
    RGBlooper(blue, 50, 1);
    if(digitalRead(4) == HIGH)
      buttonState = true;
    if(buttonState == true && digitalRead(4) == LOW) {
      click++;
      buttonState = false;
    }
    if(click > 1)
      break;
    delay(10);
  }
  if(click == 1)
    connectWiFi();
}//End of begin()

void iBHDK::brightness(uint8_t bright) {
    pixels.setBrightness(bright);
}

void iBHDK::RGBColor(uint32_t color, int delayValue) {
  for(int i=0;i<10;i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, color); // Moderately bright green color.
    pixels.show();
    delay(delayValue);
  }
}

void iBHDK::RGBlooper(uint32_t color, int delayValue, int cycles) {
  for(int i = 0; i < cycles; i++) {
    for(int i=0;i<10;i++) {
      pixels.setPixelColor(i, color);
      pixels.show();
    }
    delay(delayValue);
    for(int i=0;i<10;i++) {
      pixels.setPixelColor(i, black);
      pixels.show();
    }
    delay(delayValue);
  }
}

void iBHDK::RGBWipelooper(uint32_t color, int delayValue, int cycles) {
  for(int i = 0; i < cycles; i++) {
    for(int i=0;i<10;i++) {
      pixels.setPixelColor(i, color);
      pixels.show();
      delay(delayValue);
      pixels.setPixelColor(i, black);
      pixels.show();
    }
  }
}

void iBHDK::connectWiFi() {
  Serial.println("****************************************");
  Serial.println("Enter SSID and Password");
  Serial.println("SSID: ");
  ssid = credentials();
  Serial.println("PASSWORD: ");
  pass = credentials();
  Serial.println("****************************************");
  Serial.println();

  Serial.println("Beginning WiFI..");
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid.c_str(), pass.c_str());

  int p = 4, q = 5;
  timer = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - timer < 15000)) {
    pixels.setPixelColor(p, white);
    pixels.setPixelColor(q, white);
    pixels.show();
    delay(100);
    pixels.setPixelColor(p--, black);
    pixels.setPixelColor(q++, black);
    pixels.show();
    if(p == -1 && q == 10) {
      p = 4;
      q = 5;
    }
  }

  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    RGBlooper(green,333,4);
  }
  else {
    Serial.println("WiFi Failed");
    Serial.println("Reset to start again");
    RGBlooper(red,333,4);
  }
}

String iBHDK::credentials() {
  bool flag = false;
  char ch = ' ';
  String str  = "";
  while(!flag) {
    RGBWipelooper(purple, 50, 1);
    if(Serial.available()) {
      while(Serial.available()) {
        ch = Serial.read();
        str += ch;
        delay(5);
        flag = true;
      }
    }
  }
  return str;
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void iBHDK::rainbow() {
  uint16_t i, j;                                                                    // Declare variable for parsing the RGB LEDs.
  for (j = 0; j < 256 * 5; j++) {
    for (i = 0; i < pixels.numPixels(); i++)                                         // Loop to setup colour for each pixel
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    pixels.show();                                                                   // Display the set colours on the Pixels.
    delay(1);
    }
}

int iBHDK::readAnalog(int pin, bool displayLED) {
  int value = 0;
  value = analogRead(pin);
  if(displayLED) {
    RGBColor(black,0);
    int num = value / 100;
    if(num <= 3)
      color = green;
    else if(num > 3 && num <= 7)
      color = yellow;
    else
      color = red;
    for(int i = 0; i < num; i++) {
      pixels.setPixelColor(i, color);
      pixels.show();
    }
  }
  delay(10);
  return value;
}
