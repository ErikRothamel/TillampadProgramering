/*
* Name: clock and temp project
* Author: Victor Huke
* Date: 2024-10-10
* Description: This project uses a ds3231 to measure time and displays the time to an 1306 oled display,
* Further, it measures temprature with a analog temprature module and allows for the setting of an alarm
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include <U8glib.h>

// Init constants
const int tmpPin = A0;
const int piezoPin = 9;
const int buttonPin = 8;
const int potPin = A1;

// Init global variables
int setTime;
int ledState = HIGH;
String minute;
String second;
float temp;
int page = 1;
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 10;

// construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup() {
  // init communication
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();

  // Init Hardware
  pinMode(piezoPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Settings
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  u8g.setFont(u8g_font_unifont);
}

void loop() {
  DateTime now = rtc.now();
  if (page == 1) { // if-satsen byter mellan sidorna och tillåter ställning av klockan.
    oledWrite(getTime(), String(int(temp)) + char(176) + "C");
  } else {
    setTime = map(potMeter(), 0, 1023, 0, 59);
    oledWrite(String(setTime), "");
  }
  if (setTime == now.minute()){ // If-satsen startat piezon när tider är samma som har blivit intälld
    tone(9, 2000, 5000);
  }
  temp = getTemp();
  page = button();

  delay(50);
}


/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime() {
  DateTime now = rtc.now();
  if (now.minute() <= 9) {  // if-satserna lägger till en nolla framför minut eller sekund om de är mindre eller lika med 9. Detta är endast estetiskt.
    minute = "0";
  } else {
    minute = "";
  }
  if (now.second() <= 9) {
    second = "0";
  } else {
    second = "";
  }
  return String(now.hour()) + ":" + minute + String(now.minute()) + ":" + second + String(now.second());  //
}

/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp
*Parameters: Void
*Returns: temprature as float
*/
float getTemp() {
  int Vo;
  float R1 = 10000;  // value of R1 on board
  float logR2, R2, T;
  float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;  //steinhart-hart coeficients for thermistor

  Vo = analogRead(tmpPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);  //calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));  // temperature in Kelvin
  T = T - 273.15;                                              //convert Kelvin to Celcius

  return T;
}

/*
* This function takes a string and draws it to an oled display
*Parameters: - text: String to write to display
*Returns: void
*/
void oledWrite(String txt1, String txt2) {
  u8g.firstPage();
  do {
    u8g.drawStr(30, 33, txt1.c_str());
    u8g.drawStr(46, 50, txt2.c_str());

  } while (u8g.nextPage());
}

/*
* This function stats the button that allows for the switching of pages.
*/

int button() {

  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }


  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  return (ledState);
}

// This function reads the potentiometer.

int potMeter(){
  return analogRead(potPin);
}
