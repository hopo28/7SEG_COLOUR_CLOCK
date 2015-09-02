
//  - - - - - - - - - - - - EFFECTS  - - - - - - - - - - - 

void startUp()
{//do a startup sequence (quick)
  //LEDS.setBrightness(64);//reasonable for starters

  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = Wheel(i*(255/NUM_LEDS));
  }
  FastLED.show();
  delay(500);
  strandTest(CRGB::White,100);
  delay(500);
}

void strandTest(CRGB Color,int Delay)
{
   for(int i = 0; i < NUM_LEDS; i = i + 1)
   {
      leds[i] = Color;
      FastLED.show();
      delay(Delay);
      leds[i] = CRGB::Black;
   }
}

void wipeAcross(CRGB Colour, int Delay)
{//could be looped up but it works
  int i;
  i=0; leds[i] = Colour;      leds[i+1] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; FastLED.show(); 
  i=2; leds[i] = Colour;      leds[i+1] = Colour;      leds[i+2] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; leds[i+2] = CRGB::Black; FastLED.show();
  i=5; leds[i] = Colour;      leds[i+1] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; FastLED.show(); 
  
  i=7; leds[i] = Colour;      leds[i+1] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; FastLED.show(); 
  i=9; leds[i] = Colour;      leds[i+1] = Colour;      leds[i+2] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; leds[i+2] = CRGB::Black; FastLED.show();
  i=12;leds[i] = Colour;      leds[i+1] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; FastLED.show(); 

  i=14;leds[i] = Colour;      leds[i+1] = Colour; FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; FastLED.show(); 

  i=16;leds[i] = Colour;      leds[i+1] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; FastLED.show(); 
  i=18;leds[i] = Colour;      leds[i+1] = Colour;      leds[i+2] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; leds[i+2] = CRGB::Black; FastLED.show();
  i=21;leds[i] = Colour;      leds[i+1] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; FastLED.show(); 

  i=23;leds[i] = Colour;      leds[i+1] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; FastLED.show(); 
  i=25;leds[i] = Colour;      leds[i+1] = Colour;      leds[i+2] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; leds[i+2] = CRGB::Black; FastLED.show();
  i=28;leds[i] = Colour;      leds[i+1] = Colour;      FastLED.show(); delay(Delay);
       leds[i] = CRGB::Black; leds[i+1] = CRGB::Black; FastLED.show();  
}

void randomNumbers()
{ //random numbers, random location, random hues
  setChar(random(0,4), random(0,10), CHSV(random (0,255),255,255));
  if(random(0,5) == 0)//one in 5 chance
    setColon(CHSV(random (0,255),255,255));
  FastLED.show();  
}

void fastRandom()
{//set random segments to a random hue
  leds[random(0,NUM_LEDS)].setHue(random(0,255));
  //leds[random(0,NUM_LEDS)] = CRGB::Black;
  FastLED.show();
  delay(20);
}

void rainbowFade()
{//fade the lot
  static uint8_t hue = 0;
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].setHue(hue + (i * (255/(NUM_LEDS))));
  }
  hue++;
  FastLED.show();
  delay(20);
}

CRGB Wheel(byte WheelPos)
{//wrapper for colour wheel
  return CHSV(WheelPos, 255, 255);
}

void flickerToLife()
{//attempts to simulate flourecent tube flickering to life
  byte lux;
  byte max = 255;
  lux = BRIGHTNESS;
  LEDS.setBrightness(000); FastLED.show(); delay(000); //off
  LEDS.setBrightness(max); FastLED.show(); delay(010); 
  LEDS.setBrightness(000); FastLED.show(); delay(050); //off
  LEDS.setBrightness(max); FastLED.show(); delay(010); 
  LEDS.setBrightness(000); FastLED.show(); delay(200); //off
  LEDS.setBrightness(max); FastLED.show(); delay(010);
  LEDS.setBrightness(000); FastLED.show(); delay(300); //off
  LEDS.setBrightness(040); FastLED.show(); delay(040); 
  LEDS.setBrightness(max); FastLED.show(); delay(010); 
  LEDS.setBrightness(lux); FastLED.show(); delay(100); 
}
/*    OTHER EFFECTS FOR THE FUTURE
void pulse(int origBrightness, int targetBrightness, int times, int speed)
{
  for(int i = 0; i < times; i++)
  {
    for(int i = origBrightness; i < targetBrightness; i++)//up...
    {
      LEDS.setBrightness(i);
      FastLED.show();
      delay(speed);
    }
    for(int i = targetBrightness; i > origBrightness; i--)//and down...
    {
      LEDS.setBrightness(i);
      FastLED.show();
      delay(speed);
    }
  }
}
  
void runSparkle(CRGB myColour, int wait, int times) 
{
  for(int i = 0; i < times; i++)
  {
    sparkle(myColour.r,myColour.g ,myColour.b,wait);
  }
}
  
void sparkle(byte C0, byte C1, byte C2, int wait) 
{
  for(int i = 0; i < NUM_TOTAL_PEOPLE; i++)//make a strips-worth of data
  {
    byte whiteChance = random(0,256);
    byte FC0 = 0;
    byte FC1 = 0;
    byte FC2 = 0;
    if(whiteChance>252)//occasionally
    {
      FC0=255;
      FC1=255;
      FC2=255;
    }
    else
    {
      //dull down by a random ammount
      FC0=C0/(255/whiteChance);
      FC1=C1/(255/whiteChance);
      FC2=C2/(255/whiteChance);   
      //to dull down the colourd bit so the white looks brighter  
      FC0=FC0/4;
      FC1=FC1/4;
      FC2=FC2/4;
    }
    //leds[i] = CRGB(i,FC0,FC1,FC2);//shimmer effect
    leds[i] = CRGB(FC0,FC1,FC2);
  }
  delay(wait);
  LEDS.show();
}
 */

/*------------------------------------------- PRINTY THINGS -------------------------------------------*/

void printMenu()
{
  Serial.println(" -- Hopo's LED Clock -- ");
  digitalClockDisplay();
  Serial.println(" - MENU - ");
  Serial.println(" G = Get Settings");
  Serial.println(" S = Set Date/Time");
}

void setTimeMenu()
{
  int timeDatArray[6] = {0,0,0,0,0,0};
 
  Serial.println("Enter Year (YY)");
  timeDatArray[5] = get2DigitFromSerial();
  Serial.println("Enter Month (MM)");
  timeDatArray[4] = get2DigitFromSerial();
  Serial.println("Enter Day (DD)");
  timeDatArray[3] = get2DigitFromSerial();
  Serial.println("Enter Hour (hh)");
  timeDatArray[0] = get2DigitFromSerial();
  Serial.println("Enter Minute (mm)");
  timeDatArray[1] = get2DigitFromSerial();
  Serial.println("Enter Second (ss)");
  timeDatArray[2] = get2DigitFromSerial();

  setTime(timeDatArray[0],
          timeDatArray[1],
          timeDatArray[2],
          timeDatArray[3],
          timeDatArray[4],
          timeDatArray[5]);

  time_t t = now();
  RTC.set(t);  
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(" Time:  ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

/*------------------------------------------- INPUT THINGS -------------------------------------------*/

int get2DigitFromSerial()
{
  int retVal = 0;
  while (!(Serial.available() > 0));
  {
    retVal += (10 * (Serial.read() - '0'));
  }
  while (!(Serial.available() > 0));
  {
    retVal += (Serial.read() - '0');
  }
  return retVal;
}

int get3DigitFromSerial()
{
  int retVal = 0;
  while (!(Serial.available() > 0));
  {
    retVal += (100 * (Serial.read() - '0'));
  }
  while (!(Serial.available() > 0));
  {
    retVal += (10 * (Serial.read() - '0'));
  }
  while (!(Serial.available() > 0));
  {
    retVal += (Serial.read() - '0');
  }
  return retVal;
}

//  - - - - - - - - - - - - FONT  - - - - - - - - - - - 

/*
 __5__
|     |
6     1
|__4__|
|     |
7     2
|__3__|
0 not used as no decimal point
*/

static const unsigned char font[] = {
  0b01110111,//0
  0b01100000,//1
  0b01011101,//2
  0b01111100,//3
  0b01101010,//4
  0b00111110,//5
  0b00111111,//6
  0b01100100,//7
  0b01111111,//8
  0b01111110,//9
  0b00000000//nothing
};

//  - - - - - - - - - - - - DISPLAY  - - - - - - - - - - - 

void setRainbowColon(CRGB colour)
{
  leds[14].setHue(clockHue + (14 * (255/(NUM_LEDS*2))));
  leds[15].setHue(clockHue + (15 * (255/(NUM_LEDS*2))));
}

void setColon(CRGB colour)
{
  leds[14] = colour;
  leds[15] = colour;
}

void setRainbowChar(int8_t pos, int8_t number, CRGB colour)
{
  if(pos == 0)pos = 0;
  if(pos == 1)pos = 7;
  if(pos == 2)pos = 16;
  if(pos == 3)pos = 23;

  uint8_t line;
  line = font[number];
  for (int8_t j = 0; j<7; j++)
  {
    if (line & 0b1)
    {
      leds[j+pos].setHue(clockHue + ((j+pos) * (255/(NUM_LEDS*2))));
    }
    else
    {
     leds[j+pos] = CRGB::Black; 
    }
    line >>= 1;
  }
}

void setChar(int8_t pos, int8_t number, CRGB colour)
{  
  if(pos == 0)pos = 0;
  if(pos == 1)pos = 7;
  if(pos == 2)pos = 16;
  if(pos == 3)pos = 23;
  
  uint8_t line;
  line = font[number];
  for (int8_t j = 0; j<7; j++)
  {
    if (line & 0b1)
    {
      leds[j+pos] = colour;
    }
    else
    {
     leds[j+pos] = CRGB::Black; 
    }
    line >>= 1;
  }
}
