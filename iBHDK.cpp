/*
Higher level wrapper class to simplify the learning curve for newbies.
Developed to be used for iB IoT HDK v1.
Based on ESP8266.
Consists of 10 onboard RGB lights.
Also consists of push button.


Developed at iBHubs.
*/
//Including the header
#include<iBHDK.h>

//Creating instance of Adafruit_NeoPixel library called 'pixels'
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(RGB_COUNT, RGB, NEO_GRB + NEO_KHZ800);

//Defining common colors
uint32_t red = pixels.Color(255,0,0);
uint32_t green = pixels.Color(0,255,0);
uint32_t blue = pixels.Color(0,0,255);
uint32_t yellow = pixels.Color(255,255,0);
uint32_t purple = pixels.Color(148,0,211);
uint32_t white = pixels.Color(255,255,255);
uint32_t black = pixels.Color(0,0,0);

/*Basic begin Function used to initialize iB HDK
  RGB ring is initialized here.
*/
  void iBHDK::begin() {
    pinMode(RGB,OUTPUT);
    pixels.begin();
    RGBColor(black, 0);
    Serial.println("****************************************");
    Serial.println("Initializing..");
    Serial.println("****************************************");
    //Welcome RGB Animation
    rainbow(5,5);
    RGBColor(black, 0);
    delay(10);
  }
/*Function used to initialize iB HDK
  begin() is called here. This function is used for
  SERIAL_IN enum where the WiFi Credentials are entered
  from Serial Monitor.
*/
  void iBHDK::begin(WiFiCONN_t connection) {
  begin();
  //WiFi Setup
  Serial.println();
  if(connection == SERIAL_IN)
    connectWiFi();
  else {
    Serial.println("Invalid Entry");
    RGBlooper(red,333,4);
  }
}//End of begin()

/*Function used to initialize iB HDK
begin() is called here. This function is used for PRE_DEFINED enumwhere the WiFi Credentials
are hard coded.
*/
void iBHDK::begin(WiFiCONN_t connection, String ssid, String pass) {
  begin();
  if(connection == PRE_DEFINED) {
    //Begin WiFi Connection
    WiFi.begin(ssid.c_str(), pass.c_str());
    //WiFi Connection RGB Animation
    WiFiConnectionRGB();
    //To display IP Address
    WiFiIP();
  }
  else {
    Serial.println("Invalid Entry");
    RGBlooper(red,333,4);
  }
}//End of begin()

/*Brightness function is used to set brightness of RGB's.
  This brightness value is stored in brightValue
*/
void iBHDK::brightness(uint8_t bright) {
    pixels.setBrightness(bright);
    brightValue = bright;
}//End of brightness

/*RGBColor function is used to set the RGB ring to one distinct color.
  Use delayValue if you want to set color to each RGB individially,
  else pass 0 to it
*/
void iBHDK::RGBColor(uint32_t color, int delayValue) {
  for(int i = 0; i < RGB_COUNT; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, color); // Moderately bright green color.
    pixels.show();
    delay(delayValue);
  }
}//End of RGBColor()

/*RGBLooper function is similar to RGBColor but uses cycles as well.
  It loops the display of color and no color (black)
*/
void iBHDK::RGBlooper(uint32_t color, int delayValue, int cycles) {
  for(int i = 0; i < cycles; i++) {
    for(int i = 0; i < RGB_COUNT; i++) {
      pixels.setPixelColor(i, color);
      pixels.show();
    }
    delay(delayValue);
    for(int i = 0; i < RGB_COUNT; i++) {
      pixels.setPixelColor(i, black);
      pixels.show();
    }
    delay(delayValue);
  }
}//End of RGBlooper()

/*RGBWipelooper function is used to loop some number of wipes.
*/
void iBHDK::RGBWipelooper(uint32_t color, int delayValue, int cycles) {
  for(int i = 0; i < cycles; i++) {
    for(int i = 0; i < RGB_COUNT; i++) {
      pixels.setPixelColor(i, color);
      pixels.show();
      delay(delayValue);
      pixels.setPixelColor(i, black);
      pixels.show();
    }
  }
}//End of RGBWipelooper()

/*RGBRandom generates a random color at a random RGBRandom
*/
void iBHDK::RGBRandom() {
  int rand = random(0,11);
  pixels.setPixelColor(rand, pixels.Color(random(0,256),random(0,256),random(0,256)));
  pixels.show();
  delay(50);
  pixels.setPixelColor(rand, black);
}//End of RGBRandom

/*RGBFade function is used to generate a fade of some color
*/
void iBHDK::RGBFade(uint32_t color) {
  for(uint8_t j = 1; j < 150; j++) {
    pixels.setBrightness(j);
    for(int i = 0; i < RGB_COUNT; i++) {
      pixels.setPixelColor(i, color);
      pixels.show();
    }
    delay(1);
  }
  pixels.setBrightness(brightValue);
}//End of RGBFade


/*Function is called while connection is established.
*/
void iBHDK::WiFiConnectionRGB() {
  int p = 4, q = 9;
  long timer = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - timer < 15000)) {
    pixels.setPixelColor(p, white);
    pixels.setPixelColor(q, white);
    pixels.show();
    delay(50);
    pixels.setPixelColor(p--, black);
    pixels.setPixelColor(q--, black);
    pixels.show();
    if(p == -1 && q == 4) {
      p = 4;
      q = 9;
    }
  }
}//End of WiFiConnectionRGB()

/*Function to display IP address if connection established
or red lights if Failed
*/
bool iBHDK::WiFiIP() {
  if(WiFi.status() == WL_CONNECTED) {
    //Connection Established. Display Green Lights.
    Serial.println("WiFi Connection Established");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    RGBlooper(green,333,4);
    return true;
  }
  else {
    //Connection not Established. Display Red Lights.
    Serial.println("WiFi Connection Failed");
    Serial.println("Reset to start again");
    Serial.println();
    if(error == 2)
      RGBlooper(red,333,4);
    else
      RGBlooper(red,150,2);
    return false;
  }
}

/*connectWiFi is used to establish WiFi connection by
accepting WiFi credentials from the Serial Monitor
*/
void iBHDK::connectWiFi() {
  Serial.println("****************************************");
  Serial.println("Use ~No line ending~ in Serial Monitor..");
  Serial.println();
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

  //Begin WiFi Connection
  WiFi.begin(ssid.c_str(), pass.c_str());

  //WiFi Connection RGB Animation
  WiFiConnectionRGB();
  //To display IP Address
  if(WiFiIP() == false) {
    error++;
    if(error < 2)
      Serial.println("Error in Credentials..");
      Serial.println("Make sure to turn on ~No Line Ending~");
      connectWiFi();
  }
  else {
    Serial.println("Done!");
    Serial.println();
  }
}//End of connectWiFi()

/*credentials function is used to accept a string from the user.
*/
String iBHDK::credentials() {
  bool flag = false;
  char ch = ' ';
  String str  = "";
  while(!flag) {
    RGBWipelooper(purple, 50, 1); //Display while entry is made.
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
}//End of credentials()

/*Function to display rainbow pattern.
  Source also found in Adafruit_NeoPixel
*/
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
}//End of Wheel()

/*Function to display rainbow pattern.
  Source also found in Adafruit_NeoPixel
*/
void iBHDK::rainbow(int delayValue, int cycles) {
  uint16_t i, j;                                                                    // Declare variable for parsing the RGB LEDs.
  for (j = 0; j < 256 * cycles; j++) {
    for (i = 0; i < pixels.numPixels(); i++)                                         // Loop to setup colour for each pixel
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    pixels.show();                                                                   // Display the set colours on the Pixels.
    delay(delayValue);
    }
}//End of rainbow()

/*readAnalog is used to read an Analog value and map it unto the RGB ring.
  If you don't want to use RGB ring, set displayLED to false.
*/
int iBHDK::readAnalog(int pin, RGBRING_t ring) {
  int value = 0;
  value = analogRead(pin);
  if(ring == RGB_TRUE) {
    RGBColor(black,0);
    //Gradient color change
    float num = value / 100;
    if(num <= 3)
      color = pixels.Color(0, (int)(85*num), 0);
    else if(num > 3 && num <= 6)
      color = pixels.Color((int)(85*num), 255, 0);
    else
      color = pixels.Color(255, 255 - (int)(85*(num - 3)), 0);
    for(int i = 0; i < num; i++) {
      pixels.setPixelColor(i, color);
      pixels.show();
    }
  }
  delay(10);
  return value;
}//End of readAnalog()

/*Function Overloaded readAnalog woth extra logic parameter.
  If Logic = 0, Low Color = Green, Mid Color = Yellow, High Color = Red
  If Logic = 1, Low Color = Red, Mid Color = Yellow, High Color = Green
*/
int iBHDK::readAnalog(int pin, RGBRING_t ring, LOGIC_t logic) {
  int value = 0;
  value = analogRead(pin);
  if(ring == RGB_TRUE) {
    //Gradient color change
    float num;
    num = value / 100;
    if(logic == GREEN_RED) {
      RGBColor(black,0);

      if(num <= 3)
        color = pixels.Color(0, (int)(85*num), 0);
      else if(num > 3 && num <= 6)
        color = pixels.Color((int)(85*num), 255, 0);
      else
        color = pixels.Color(255, 255 - (int)(85*(num - 6)), 0);
    }
    else if(logic == RED_GREEN) {
      RGBColor(black,0);
      if(num <= 3)
        color = pixels.Color((int)(85*num), 0, 0);
      else if(num > 3 && num <= 6)
        color = pixels.Color(255, (int)(85*num), 0);
      else
        color = pixels.Color(255 - (int)(85*(num - 3)), 255, 0);
    }
    for(int i = 0; i < num; i++) {
      pixels.setPixelColor(i, color);
      pixels.show();
    }
  }
  delay(10);
  return value;
}//End of readAnalog()
