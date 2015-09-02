#include "FastLED.h"
#include <Time.h>  
#include <TimeAlarms.h>
#include <Wire.h>  
#include <DS1307RTC.h>

#define NUM_LEDS 30
#define DATA_PIN 3
#define BRIGHTNESS 255
#define BUT_PIN 4
#define PRESS_SHORT 30//in milliseconds, for debouncing

CRGB leds[NUM_LEDS];
static uint8_t clockHue = 0;

unsigned long buttonPressedTimer = 0;
int buttonPressed = 200;
boolean buttonPressedFlag = false;
byte buttonPressedOrigValue = 0;

boolean mode = true;//just 2 modes

void setup()
{
  // - - - SERIAL - - -
  Serial.begin(9600);
  // - - - RTC - - -
  setSyncProvider(RTC.get);   // the function to get the time from the RTC, gets time NOW
  setSyncInterval(300);  //default is 300 secs (5 mins)
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");
  // - - - PINS - - -
  pinMode(BUT_PIN, INPUT);           // set pin to input
  digitalWrite(BUT_PIN, HIGH);       // turn on pullup r
  // - - - LEDS - - -
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  //FastLED.clear();
  //FastLED.show();
  printMenu();
  //startUp();
  delay(500);//safety
  displayClock();
  flickerToLife();
}

void loop()
{ 
  //delay(500);  
  //fastRandom();
  //rainbowFade();
  //randomNumbers();delay(750);
  //delay(500);

  if (Serial.available() > 0)
  {
    doMenu(Serial.read());
  }
  checkChimes();
  displayClock();  
  checkButtons();
}

void displayClock()
{  
  for(int i = 0; i < NUM_LEDS; i++)//clear previous array data, FastLED.clear() may work instead
  {
      leds[i] = CRGB::Black;
  }

  byte char0,char1,char2,char3;
  int mins = minute();
  int hr = hour();
  int sec = second();
  CRGB secColour, minColour, hrColour, tickColour;
  
  //Hours
  if(hr<10)
  {
    char0 = 10; //10 is nothing
    char1 = hr + 0;
  }
  else
  {
    char0 = ((hr - (hr % 10))/10);
    char1 = (hr % 10);
  }
  //Mins
  if(mins<10)
  {
    char2 = 0;//preceding 0
    char3 = mins;
  }
  else
  {
    char2 = ((mins - (mins % 10)) /10);
    char3 = (mins % 10);
  }
//colours
  secColour = Wheel(sec*(255/60));
  minColour = Wheel(mins*(255/60));
  hrColour = Wheel(hr*(255/24));
//display
  if(mode)
  {
    setChar(0,char0, hrColour);
    setChar(1,char1, hrColour);
    setColon(secColour);
    setChar(2,char2, minColour);
    setChar(3,char3, minColour);
  }
  else
  {
    setRainbowChar(0,char0, hrColour);
    setRainbowChar(1,char1, hrColour);
    setRainbowColon(secColour);
    setRainbowChar(2,char2, minColour);
    setRainbowChar(3,char3, minColour);
    clockHue++;//cycle hue a bit
  }
  FastLED.show();
  delay(100);//for making the fading work at a reasonable speed
}

void checkButtons()
{
  if(!digitalRead(BUT_PIN))//if the one being checked is pressed
  {
    if(buttonPressedFlag == false)//if its first time press
    {
      //Serial.print("Button ");
      //Serial.println(" Pressed");
      
      //log details and start time
      buttonPressedFlag = true;
      buttonPressedTimer = millis();
    }
    else//(buttonPressedFlag == true)
    {//this means this button has been pressed before and is still being pressed
      //Serial.print(i);
      unsigned long timeTemp = (millis()-buttonPressedTimer);//how long it was pressed for
      if(timeTemp < PRESS_SHORT)
      {
        //Serial.println("INVALID");//do sod all          
      }
      else
      {
        //while being held
      }
    }
  }
  else//if the one being checked is NOT pressed
  {      
    if(buttonPressedFlag == true)//if it WAS pressed
    {
      //Serial.println("unpressed");
      mode=!mode;
      buttonPressedFlag = false;
    }
  }
}

void doMenu(char selection)
{
  switch(selection)
  {
    case 'G'://print time out
    digitalClockDisplay();
    break;
    case 'S'://set time menu
    setTimeMenu();
          printMenu();
    break;
    default:
    Serial.println("Unknown command");
    break;
  }
}

void checkChimes()
{
  if (minute() == 0 && second() == 0)//hourly chime
  {
    while(second() < 10)//for 10 seconds
    {
      rainbowFade();
    }
    delay(500);    
    wipeAcross(CRGB::White,100);
    delay(500);  
  }
  else if(second() == 0)//if min changing
  {
    delay(500);    
    wipeAcross(CRGB::White,100);
    delay(500);  
  }
}
