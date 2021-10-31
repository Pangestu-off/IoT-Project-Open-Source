#include <LedControl.h>
#include <Wire.h>
#include <Time.h>
#include <TimeLib.h>


/*
  DIN connects to pin 12
  CLK connects to pin 10
  CS connects to pin 11
*/

LedControl lc = LedControl(12, 10, 11, 2);

byte mm1, mm5, h, m, s;
byte ultM = 10, ultH = 10;
byte hPin = 7, mPin = 6;
boolean ajustaH = true, ajustaM = true;


void setup() {
  lc.shutdown(0, false);      // power-saving mode on startup
  lc.setIntensity(0, 2);     // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display
  lc.shutdown(1, false);      // power-saving mode on startup
  lc.setIntensity(1, 2);     // Set the brightness to maximum value
  lc.clearDisplay(1);         // and clear the display




  Serial.begin(9600);
  pinMode(hPin, INPUT_PULLUP);
  pinMode(mPin, INPUT_PULLUP);
}

void Display() {
  /* here is the data for the characters */
  byte one[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x28};
  byte two[8] = {0x00, 0x00, 0x00, 0x74, 0x54, 0x5C, 0x00, 0x28};
  byte three[8] = {0x00, 0x00, 0x00, 0x44, 0x54, 0x7C, 0x00, 0x28};
  byte four[8] = {0x00, 0x00, 0x00, 0x1C, 0x10, 0x78, 0x00, 0x28};
  byte five[8] = {0x00, 0x00, 0x00, 0x5C, 0x54, 0x74, 0x00, 0x28};
  byte six[8] = {0x00, 0x00, 0x00, 0x7C, 0x54, 0x74, 0x00, 0x28};
  byte seven[8] = {0x00, 0x00, 0x00, 0x04, 0x04, 0x7C, 0x00, 0x28};
  byte eight[8] = {0x00, 0x00, 0x00, 0x7C, 0x54, 0x7C, 0x00, 0x28};
  byte nine[8] = {0x00, 0x00, 0x00, 0x5C, 0x54, 0x7C, 0x00, 0x28};
  byte ten[8] = {0x00, 0x7C, 0x00, 0x7C, 0x44, 0x7C, 0x00, 0x28};
  byte eleven[8] = {0x00, 0x00, 0x7C, 0x00, 0x00, 0x7C, 0x00, 0x28};
  byte twelve[8] = {0x00, 0x7C, 0x00, 0x74, 0x54, 0x5C, 0x00, 0x28};

  // 0-9
  byte zero2[8] = {0x00, 0x7C, 0x44, 0x7C, 0x00, 0x7C, 0x44, 0x7C}; //00
  byte one2[8] = {0x00, 0x7C, 0x44, 0x7C, 0x00, 0x00, 0x7C, 0x00}; //01
  byte two2[8] = {0x00, 0x7C, 0x44, 0x7C, 0x00, 0x74, 0x54, 0x5C}; //02
  byte three2[8] = {0x00, 0x7C, 0x44, 0x7C, 0x00, 0x44, 0x54, 0x7C}; //03
  byte four2[8] = {0x00, 0x7C, 0x44, 0x7C, 0x00, 0x1C, 0x10, 0x78}; //04
  byte five2[8] = {0x00, 0x7C, 0x44, 0x7C, 0x00, 0x5C, 0x54, 0x74}; //05
  byte six2[8] = {0x00, 0x7C, 0x44, 0x7C, 0x00, 0x7C, 0x54, 0x74}; //06
  byte seven2[8] = {0x00, 0x7C, 0x44, 0x7C, 0x00, 0x04, 0x04, 0x7C}; //07
  byte eight2[8] = {0x00, 0x7C, 0x44, 0x7C, 0x00, 0x7C, 0x54, 0x7C}; //08
  byte nine2[8] = {0x00, 0x7C, 0x44, 0x7C, 0x00, 0x5C, 0x54, 0x7C}; //09
  // 10-19
  byte ten2[8] = {0x00, 0x7C, 0x00, 0x7C, 0x44, 0x7C, 0x00, 0x00}; //10
  byte eleven2[8] = {0x00, 0x7C, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00}; //11
  byte twelve2[8] = {0x00, 0x7C, 0x00, 0x74, 0x54, 0x5C, 0x00, 0x00}; //12
  byte thirteen2[8] = {0x00, 0x7C, 0x00, 0x44, 0x54, 0x7C, 0x00, 0x00}; //13
  byte fourteen2[8] = {0x00, 0x7C, 0x00, 0x1C, 0x10, 0x78, 0x00, 0x00}; //14
  byte fifteen2[8] = {0x00, 0x7C, 0x00, 0x5C, 0x54, 0x74, 0x00, 0x00}; //15
  byte sixteen2[8] = {0x00, 0x7C, 0x00, 0x7C, 0x54, 0x74, 0x00, 0x00}; //16
  byte seventeen2[8] = {0x00, 0x7C, 0x00, 0x04, 0x04, 0x7C, 0x00, 0x00}; //17
  byte eighteen2[8] = {0x00, 0x7C, 0x00, 0x7C, 0x54, 0x7C, 0x00, 0x00}; //18
  byte nineteen2[8] = {0x00, 0x7C, 0x00, 0x5C, 0x54, 0x7C, 0x00, 0x00}; //19

  // 20-29
  byte twenty2[8] = {0x00, 0x74, 0x54, 0x5C, 0x00, 0x7C, 0x44, 0x7C}; //20
  byte twentyone2[8] = {0x00, 0x74, 0x54, 0x5C, 0x00, 0x00, 0x7C, 0x00}; //21
  byte twentytwo2[8] = {0x00, 0x74, 0x54, 0x5C, 0x00, 0x74, 0x54, 0x5C}; //22
  byte twentythree2[8] = {0x00, 0x74, 0x54, 0x5C, 0x00, 0x44, 0x54, 0x7C}; //23
  byte twentyfour2[8] = {0x00, 0x74, 0x54, 0x5C, 0x00, 0x1C, 0x10, 0x78}; //24
  byte twentyfive2[8] = {0x00, 0x74, 0x54, 0x5C, 0x00, 0x5C, 0x54, 0x74}; //25
  byte twentysix2[8] = {0x00, 0x74, 0x54, 0x5C, 0x00, 0x7C, 0x54, 0x74}; //26
  byte twentyseven2[8] = {0x00, 0x74, 0x54, 0x5C, 0x00, 0x7C, 0x54, 0x74}; //27
  byte twentyeight2[8] = {0x00, 0x74, 0x54, 0x5C, 0x00, 0x7C, 0x54, 0x7C}; //28
  byte twentynine2[8] = {0x00, 0x74, 0x54, 0x5C, 0x00, 0x5C, 0x54, 0x7C}; //29

  // 30-39
  byte thirty2[8] = {0x00, 0x44, 0x54, 0x7C, 0x00, 0x7C, 0x44, 0x7C}; //30
  byte thirtyone2[8] = {0x00, 0x44, 0x54, 0x7C, 0x00, 0x00, 0x7C, 0x00}; //31
  byte thirtytwo2[8] = {0x00, 0x44, 0x54, 0x7C, 0x00, 0x74, 0x54, 0x5C}; //32
  byte thirtythree2[8] = {0x00, 0x44, 0x54, 0x7C, 0x00, 0x44, 0x54, 0x7C}; //33
  byte thirtyfour2[8] = {0x00, 0x44, 0x54, 0x7C, 0x00, 0x1C, 0x10, 0x78}; //34
  byte thirtyfive2[8] = {0x00, 0x44, 0x54, 0x7C, 0x00, 0x5C, 0x54, 0x74}; //35
  byte thirtysix2[8] = {0x00, 0x44, 0x54, 0x7C, 0x00, 0x7C, 0x54, 0x74}; //36
  byte thirtyseven2[8] = {0x00, 0x44, 0x54, 0x7C, 0x00, 0x04, 0x04, 0x7C}; //37
  byte thirtyeight2[8] = {0x00, 0x44, 0x54, 0x7C, 0x00, 0x7C, 0x54, 0x7C}; //38
  byte thirtynine2[8] = {0x00, 0x44, 0x54, 0x7C, 0x00, 0x5C, 0x54, 0x7C}; //39


  // 40-49
  byte forty2[8] = {0x00, 0x1C, 0x10, 0x78, 0x00, 0x7C, 0x44, 0x7C}; //40
  byte fortyone2[8] = {0x00, 0x1C, 0x10, 0x78, 0x00, 0x00, 0x7C, 0x00}; //41
  byte fortytwo2[8] = {0x00, 0x1C, 0x10, 0x78, 0x00, 0x74, 0x54, 0x5C}; //42
  byte fortythree2[8] = {0x00, 0x1C, 0x10, 0x78, 0x00, 0x44, 0x54, 0x7C}; //43
  byte fortyfour2[8] = {0x00, 0x1C, 0x10, 0x78, 0x00, 0x1C, 0x10, 0x78}; //44
  byte fortyfive2[8] = {0x00, 0x1C, 0x10, 0x78, 0x00, 0x5C, 0x54, 0x74}; //45
  byte fortysix2[8] = {0x00, 0x1C, 0x10, 0x78, 0x00, 0x7C, 0x54, 0x74}; //46
  byte fortyseven2[8] = {0x00, 0x1C, 0x10, 0x78, 0x00, 0x04, 0x04, 0x7C}; //47
  byte fortyeight2[8] = {0x00, 0x1C, 0x10, 0x78, 0x00, 0x7C, 0x54, 0x7C}; //48
  byte fortynine2[8] = {0x00, 0x1C, 0x10, 0x78, 0x00, 0x5C, 0x54, 0x7C}; //49

  // 50-59
  byte fifty2[8] = {0x00, 0x5C, 0x54, 0x74, 0x00, 0x7C, 0x44, 0x7C}; //50
  byte fiftyone2[8] = {0x00, 0x5C, 0x54, 0x74, 0x00, 0x00, 0x7C, 0x00}; //51
  byte fiftytwo2[8] = {0x00, 0x5C, 0x54, 0x74, 0x00, 0x74, 0x54, 0x5C}; //52
  byte fiftythree2[8] = {0x00, 0x5C, 0x54, 0x74, 0x00, 0x44, 0x54, 0x7C}; //53
  byte fiftyfour2[8] = {0x00, 0x5C, 0x54, 0x74, 0x00, 0x1C, 0x10, 0x78}; //54
  byte fiftyfive2[8] = {0x00, 0x5C, 0x54, 0x74, 0x00, 0x5C, 0x54, 0x74}; //55
  byte fiftysix2[8] = {0x00, 0x5C, 0x54, 0x74, 0x00, 0x7C, 0x54, 0x74}; //56
  byte fiftyseven2[8] = {0x00, 0x5C, 0x54, 0x74, 0x00, 0x04, 0x04, 0x7C}; //57
  byte fiftyeight2[8] = {0x00, 0x5C, 0x54, 0x74, 0x00, 0x7C, 0x54, 0x7C}; //58
  byte fiftynine2[8] = {0x00, 0x5C, 0x54, 0x74, 0x00, 0x5C, 0x54, 0x7C}; //59

  // Setup of Hours & Minutes
  ajustaH = digitalRead(hPin);
  ajustaM = digitalRead(mPin);

  if (!ajustaH) {
    adjustTime(3600);
  }

  if (!ajustaM) {
    adjustTime(60);
  }

  h = hour();
  m = minute();
  Serial.print (hour());
  Serial.print(":");
  Serial.print (minute());
  Serial.print(":");
  Serial.print (second());
  Serial.println();

  delay(000);

  if ( h > 12)
  {
    h = (h - 12);
  }





  // now set hour
  if (h == 1)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, one[n]);
    }

  }

  if (h == 2)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, two[n]);
    }
  }
  if (h == 3)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, three[n]);
    }

  }

  if (h == 4)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, four[n]);
    }

  }
  if (h == 5)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, five[n]);
    }

  }

  if (h == 6)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, six[n]);
    }

  }

  if (h == 7)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, seven[n]);
    }

  }

  if (h == 8)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, eight[n]);
    }

  }
  if (h == 9)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, nine[n]);
    }

  }

  if (h == 10)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, ten[n]);
    }

  }

  if (h == 11)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, eleven[n]);
    }

  }

  if (h == 12)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(0, n, twelve[n]);
    }

  }


  // now set minute
  if (m == 0)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, zero2[n]);
    }

  }

  if (m == 1)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, one2[n]);
    }

  }

  if (m == 2)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, two2[n]);
    }

  }

  if (m == 3)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, three2[n]);
    }

  }

  if (m == 4)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, four2[n]);
    }

  }

  if (m == 5)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, five2[n]);
    }

  }

  if (m == 6)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, six2[n]);
    }

  }

  if (m == 7)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, seven2[n]);
    }

  }

  if (m == 8)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, eight2[n]);
    }

  }
  if (m == 9)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, nine2[n]);
    }

  }

  if (m == 10)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, ten2[n]);
    }

  }

  if (m == 11)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, eleven2[n]);
    }

  }

  if (m == 12)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twelve2[n]);
    }

  }

  if (m == 13)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirteen2[n]);
    }

  }

  if (m == 14)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fourteen2[n]);
    }

  }
  if (m == 15)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fifteen2[n]);
    }

  }
  if (m == 16)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, sixteen2[n]);
    }

  }

  if (m == 17)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, seventeen2[n]);
    }

  }

  if (m == 18)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, eighteen2[n]);
    }

  }

  if (m == 19)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, nineteen2[n]);
    }

  }

  if (m == 20)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twenty2[n]);
    }

  }

  if (m == 21)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twentyone2[n]);
    }

  }

  if (m == 22)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twentytwo2[n]);
    }

  }

  if (m == 23)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twentythree2[n]);
    }

  }

  if (m == 24)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twentyfour2[n]);
    }

  }

  if (m == 25)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twentyfive2[n]);
    }
  }

  if (m == 26)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twentysix2[n]);
    }

  }

  if (m == 27)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twentyseven2[n]);
    }

  }

  if (m == 28)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twentyeight2[n]);
    }

  }

  if (m == 29)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, twentynine2[n]);
    }

  }

  if (m == 30)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirty2[n]);
    }

  }

  if (m == 31)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirtyone2[n]);
    }

  }

  if (m == 32)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirtytwo2[n]);
    }

  }

  if (m == 33)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirtythree2[n]);
    }

  }

  if (m == 34)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirtyfour2[n]);
    }

  }

  if (m == 35)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirtyfive2[n]);
    }

  }

  if (m == 36)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirtysix2[n]);
    }

  }

  if (m == 37)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirtyseven2[n]);
    }

  }

  if (m == 38)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirtyeight2[n]);
    }

  }

  if (m == 39)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, thirtynine2[n]);
    }

  }

  if (m == 40)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, forty2[n]);
    }

  }

  if (m == 41)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fortyone2[n]);
    }

  }

  if (m == 42)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fortytwo2[n]);
    }

  }

  if (m == 43)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fortythree2[n]);
    }

  }

  if (m == 44)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fortyfour2[n]);
    }

  }

  if (m == 45)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fortyfive2[n]);
    }

  }

  if (m == 46)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fortysix2[n]);
    }

  }

  if (m == 47)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fortyseven2[n]);
    }

  }

  if (m == 48)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fortyeight2[n]);
    }

  }

  if (m == 49)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fortynine2[n]);
    }

  }

  if (m == 50)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fifty2[n]);
    }

  }

  if (m == 51)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fiftyone2[n]);
    }
  }

  if (m == 52)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fiftytwo2[n]);
    }

  }

  if (m == 53)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fiftythree2[n]);
    }

  }
  if (m == 54)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fiftyfour2[n]);
    }

  }

  if (m == 55)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fiftyfive2[n]);
    }

  }

  if (m == 56)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fiftysix2[n]);
    }

  }

  if (m == 57)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fiftyseven2[n]);
    }

  }
  if (m == 58)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fiftyeight2[n]);
    }

  }

  if (m == 59)
  {
    for (int n = 0; n < 8; n++) {
      lc.setRow(1, n, fiftynine2[n]);
    }

  }
}
void loop() {

  Display();
  delay(1000);

}
