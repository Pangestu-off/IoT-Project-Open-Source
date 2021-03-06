[code]
/****************************************/
/************ A simple timer ************/
/**** with a user-friendly interface ****/
/****************************************/ 

/* Libraries and their licence files */
#include <LiquidCrystal.h>

// arduino-fsm is free software: you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// arduino-fsm is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with arduino-fsm.  If not, see <http://www.gnu.org/licenses/>.

#include <Fsm.h>

/*
  EEPROM.h - EEPROM library
  Original Copyright (c) 2006 David A. Mellis.  All right reserved.
  New version by Christopher Andrews 2015.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <EEPROM.h>

/* Hardware connections */
#define LCDRs 12
#define LCDEn 11
#define LCDD4 5
#define LCDD5 4
#define LCDD6 3
#define LCDD7 2
#define backLightPin 10
#define rotaryAPin 6
#define rotaryBPin 7
#define rotarySwitchPin 8
#define beeperPin A0

/* Global variables */
unsigned long remainingTime=0; // seconds
bool timerRunning=false;
int dimming, toneFrequencyIndex;
String lines[2];

/* Frequencies of notes from C4 to B7 */
int toneFrequencies[48]=
{
  262, 277, 294, 311, 330, 349, 370, 392, 415,
  440, 466, 494, 523, 554, 587, 622, 659, 698,
  740, 784, 831, 880, 932, 988, 1047, 1109,
  1175, 1245, 1319, 1397, 1480, 1568, 1661,
  1760, 1865, 1976, 2093, 2217, 2349, 2489,
  2637, 2794, 2960, 3136, 3332, 3520, 3729,
  3951
};

/* Addresses in the EEPROM */
enum EEPROMAddresses
{
  EEPROMId0,
  EEPROMId1,
  EEPROMId2,
  EEPROMDimming,
  EEPROMTone
};

/* Events generated by the rotary switch */
enum potentialEvents
{
  noEvent,
  cwRot, // clockwise rotation
  ccwRot, // counterclockwise rotation
  shortSwitchPress, longSwitchPress,
  timeOut
} event;

#define maxTime 30000
#define longPressTime 2500

LiquidCrystal lcd(LCDRs, LCDEn, LCDD4, LCDD5,
                  LCDD6, LCDD7);


/* Display objects and functions */

/* An object of the class flash can make an
   area of contiguous characters on a line
   of the LCD blink at any frequency and
   any duty cycle 
*/
class flash
{  
public :
  bool on;
  int line, row, number, period, cycle;
  void setFlash(bool flashOn,
                int flashLine=0,
                int flashRow=0,
                int flashNumber=0,
                int flashPeriod=800,
                int flashCycle=60)
  {
    on=flashOn;
    line=flashLine;
    row=flashRow;
    number=flashNumber;
    period=flashPeriod;
    cycle=flashCycle;    
  }
  
  flash() // Constructor
  {
    on=false;
  }
};

#define flashingAreasNumber 2
flash displayFlash[flashingAreasNumber];

/* The text to be displayed on the LCD is
   stored in the variables lines[0] and
   lines[1]. This fonction displays it
   on the LCD while blinking the areas
   defined in the objects of class flash.
*/
void LCDShow(void)
{
  String line;
  for(int i=0; i<2; i++)
  {
    line=lines[i];
    for(int j=0; j<flashingAreasNumber; j++)
    {
      if(displayFlash[j].on && 
         displayFlash[j].line==i &&
         (millis()%displayFlash[j].period >
           ((long)displayFlash[j].period *
            (long)displayFlash[j].cycle)/100))
      {
        for(int k=0; k<displayFlash[j].number; k++)
          line.setCharAt
           (displayFlash[j].row+k, ' ');
      }
    }
    lcd.setCursor(0, i);
    lcd.print(line);
  }
}

void clearDisplay(void)
{
  for(int i=0; i<flashingAreasNumber; i++)
    displayFlash[i].setFlash(false);
  lines[0]="                ";
  lines[1]="                ";
  LCDShow();
}

/* Functions called by the finite state
   machine. They display and set the different
   values accessible to the user : delay of
   the timer, brightness of the LCD and
   frequency of the beeper. Some values are
   stored into the EEPROM after setting.
*/

void timerDisplay(void)
{
  int hour, minute, second;
  
  hour=remainingTime/3600;
  minute=(remainingTime-hour*3600L)/60;
  second=remainingTime%60;
  
  lines[0]="Timer           ";
  lines[1]="   ";
  if(hour<10) lines[1]+=" ";
  lines[1]+=String(hour);
  lines[1]+=":";
  if(minute<10) lines[1]+="0";
  lines[1]+=String(minute);
  lines[1]+=":";
  if(second<10) lines[1]+="0";
  lines[1]+=String(second);
  LCDShow();
}

void dimmingDisplay(void)
{
  lines[0]="Brightness      ";
  lines[1]="      "+String(dimming);
  LCDShow();
}

void toneDisplay(void)
{
  lines[0]="Tone            ";
  lines[1]="    ";
  if (toneFrequencies[toneFrequencyIndex]<1000)
    lines[1]+=" ";
  lines[1]+=String(toneFrequencies
                   [toneFrequencyIndex]);
  lines[1]+=" Hz      ";
  LCDShow();
}

void timerHourSetEnter(void)
{
  clearDisplay();
/*
  The two following lines just for showing
  that it is possible to program two areas
  blinking at different frequencies.
 */
  displayFlash[0].setFlash(true, 0, 0, 5, 1000,
                           50);
  displayFlash[1].setFlash(true, 1, 3, 2);
  timerDisplay();
  timerRunning=false;                          
}

void timerHourSet(void)
{
  int hour;
  hour=remainingTime/3600; 
  if (event==cwRot && hour<23) hour++;
  else
    if (event==ccwRot && hour>0) hour--;
  remainingTime=remainingTime%3600+hour*3600L;
  timerDisplay();
}

void timerMinuteSetEnter(void)
{
  clearDisplay();
  displayFlash[0].setFlash(true, 0, 0, 5, 1000,
                           50);
  displayFlash[1].setFlash(true, 1, 6, 2);
  timerDisplay();                          
}

void timerMinuteSet(void)
{
  int minute;
  minute=(remainingTime%3600)/60;
  if (event==cwRot && minute<59) minute++;
  else
    if (event==ccwRot && minute>0) minute--;
  remainingTime=(remainingTime/3600)*3600+
                remainingTime%60 +
                minute*60L;
  timerDisplay();
}

void timerSecondSetEnter(void)
{
  clearDisplay();
  displayFlash[0].setFlash(true, 0, 0, 5, 1000,
                           50);
  displayFlash[1].setFlash(true, 1, 9, 2);
  timerDisplay();                          
}

void timerSecondSet(void)
{
  int second;
  second=remainingTime%60;
  if (event==cwRot && second<59) second++;
  else
    if (event==ccwRot && second>0) second--;
  remainingTime=(remainingTime/60)*60+second;
  timerDisplay();
}

void timerSecondSetExit(void)
{
  if (remainingTime!=0) timerRunning=true;  
}

/* This function stops the beeper when it is
   beeping, and suspends or restarts the
   counting of the timer.
*/
void toggleTimerRunning(void)
{
  if (remainingTime==0)
  {
    timerRunning=false;
    noTone(beeperPin);
  }
  else timerRunning=!timerRunning;
}

void dimmingSetEnter(void)
{
  displayFlash[0].setFlash(true, 1, 6, 1);
  dimmingDisplay();
}

void dimmingSet(void)
{
  if(event==cwRot && dimming<9) dimming++;
  else
    if(event==ccwRot && dimming>0) dimming--;
  dimmingDisplay();
}

void dimmingSetExit(void)
{
  EEPROM.update(EEPROMDimming, dimming);
}

void toneSetEnter(void)
{
  displayFlash[0].setFlash(true, 1, 4, 4);
  toneDisplay();
  noTone(beeperPin);
  tone(beeperPin,
       toneFrequencies[toneFrequencyIndex]);
}

void toneSet(void)
{
  if(event==cwRot && toneFrequencyIndex<47)
    toneFrequencyIndex++;
  else
    if (event==ccwRot && toneFrequencyIndex>0)
      toneFrequencyIndex--;
  toneDisplay();
  if(event==cwRot || event==ccwRot)
  {
    noTone(beeperPin);
    tone(beeperPin,
       toneFrequencies[toneFrequencyIndex]);
  }
}

 void toneSetExit(void)
{
  noTone(beeperPin);
  EEPROM.update(EEPROMTone,
    toneFrequencyIndex);
}

/*
  States of the finite state machine
*/
State timerDisplayState(&clearDisplay,
                        &timerDisplay, NULL);
State dimmingDisplayState(&clearDisplay,
                          &dimmingDisplay,
                          NULL);
State toneDisplayState(&clearDisplay,
                       &toneDisplay,
                       NULL);
State timerHourSetState(&timerHourSetEnter,
                        &timerHourSet,
                        NULL);
State timerMinuteSetState(&timerMinuteSetEnter,
                          &timerMinuteSet,
                          NULL);
State timerSecondSetState(&timerSecondSetEnter,
                          &timerSecondSet,
                          &timerSecondSetExit);
State dimmingSetState(&dimmingSetEnter,
                      &dimmingSet,
                      &dimmingSetExit);
State toneSetState(&toneSetEnter,
                   &toneSet,
                   &toneSetExit);

Fsm UIFsm(&timerDisplayState);

/*
   This function defines all the transitions
   between the different states of the
   finite state machine.
 */
void setTransitions(void)
{
  UIFsm.add_transition(&timerDisplayState,
                       &dimmingDisplayState,
                       cwRot, NULL);
  UIFsm.add_transition(&dimmingDisplayState,
                       &toneDisplayState,
                       cwRot, NULL);
  UIFsm.add_transition(&toneDisplayState,
                       &timerDisplayState,
                       cwRot, NULL);

  UIFsm.add_transition(&timerDisplayState,
                       &toneDisplayState,
                       ccwRot, NULL);
  UIFsm.add_transition(&toneDisplayState,
                       &dimmingDisplayState,
                       ccwRot, NULL);
  UIFsm.add_transition(&dimmingDisplayState,
                       &timerDisplayState,
                       ccwRot, NULL);

  UIFsm.add_transition(&timerDisplayState,
                       &timerHourSetState,
                       longSwitchPress, NULL);
  UIFsm.add_transition(&timerHourSetState,
                       &timerMinuteSetState,
                       shortSwitchPress, NULL);
  UIFsm.add_transition(&timerHourSetState,
                       &timerDisplayState,
                       timeOut, NULL);
  UIFsm.add_transition(&timerMinuteSetState,
                       &timerSecondSetState,
                       shortSwitchPress, NULL);
  UIFsm.add_transition(&timerMinuteSetState,
                       &timerDisplayState,
                       timeOut, NULL);
  UIFsm.add_transition(&timerSecondSetState,
                       &timerDisplayState,
                       shortSwitchPress, NULL);

  UIFsm.add_transition(&dimmingDisplayState,
                       &dimmingSetState,
                       longSwitchPress, NULL);
  UIFsm.add_transition(&dimmingSetState,
                       &dimmingDisplayState,
                       shortSwitchPress, NULL);
  UIFsm.add_transition(&dimmingSetState,
                       &dimmingDisplayState,
                       timeOut, NULL);

  UIFsm.add_transition(&toneDisplayState,
                       &toneSetState,
                       longSwitchPress, NULL);
  UIFsm.add_transition(&toneSetState,
                       &toneDisplayState,
                       shortSwitchPress, NULL);
  UIFsm.add_transition(&toneSetState,
                       &toneDisplayState,
                       timeOut, NULL);
/*
  This is a special transition. It does not
  change the current state, but it calls the
  function toggleTimerRunning when the
  current state is timerDisplayState and the
  user shortly presses the rotary switch. This
  is done to suspend or restart the count 
  when the timer is counting, and to stop the
  beeper after the end of the count.
*/
  UIFsm.add_transition(&timerDisplayState,
                       &timerDisplayState,
                       shortSwitchPress,
                       &toggleTimerRunning);
}

/*
  This function manages the counting of the 
  timer and the beep when the count has
  reached zero.
*/
void timerManagement(void)
{
  static unsigned long memoTime, actualTime;
  static bool toneStarted=false;

  if (timerRunning)
  {
    if(remainingTime==0)
    {
      if((millis()%1000)>500)
      {
        if(toneStarted==false)
        {
          tone(beeperPin,
          toneFrequencies[toneFrequencyIndex]);
          toneStarted=true;
        }
      }
      else
      {
        if(toneStarted==true)
        {
          noTone(beeperPin);
          toneStarted=false;
        }
      }
    }
    else  // remaining time not zero
    {
      actualTime=millis();
      if(actualTime-memoTime>=1000)
      {
        memoTime=actualTime;
        remainingTime--;
      }
    }
  }
}

/*
  This function reads the actions of the user
  on the rotary switch and converts them into
  events.
 */
void rotaryEncoderRead(void)
{
  unsigned long pressedSwitchDelay=0;
  unsigned long pressedSwitchTime=0;
  static unsigned long lastEventTime;
  static bool longPressTreated=false;

  event=noEvent;
  if(digitalRead(rotaryAPin)==LOW)
  {
    if(digitalRead(rotaryBPin)==LOW)
      event=ccwRot;
    else
      event=cwRot;
    while(digitalRead(rotaryAPin)==LOW);
    lastEventTime=millis();
  }
  
  if(digitalRead(rotarySwitchPin)==LOW)
  {
    if (!longPressTreated)
    {
      pressedSwitchTime=millis();
      while(digitalRead(rotarySwitchPin)==LOW
            && (millis()-pressedSwitchTime)<
             longPressTime);
      lastEventTime=millis();
      pressedSwitchDelay=millis()-
                         pressedSwitchTime;
      if(pressedSwitchDelay>=longPressTime)
      {
        event=longSwitchPress;
        longPressTreated=true;
      }
      else if(pressedSwitchDelay>50)
        event=shortSwitchPress;
    }
  }
  else
    longPressTreated=false;
  if(millis()-lastEventTime>maxTime)
    event=timeOut;
}

/*
  The settings of brightness and tone frquency
  are stored into the EEPROM to be kept when
  the power is off. This function is called at
  power on to get these values back. To be sure
  that they are the right ones, the first
  three bytes of the EEPROM must contain "tim".
  If it is not the case, the values are
  replaced by the default values.  
*/
void readEEPROM(void)
{
  if(EEPROM.read(EEPROMId0)==short('t') &&
     EEPROM.read(EEPROMId1)==short('i') &&
     EEPROM.read(EEPROMId2)==short('m'))
  {
    dimming=EEPROM.read(EEPROMDimming);
    toneFrequencyIndex=EEPROM.read(EEPROMTone);
  }
  else
  {   
    EEPROM.update(EEPROMId0, 't');
    EEPROM.update(EEPROMId1, 'i');
    EEPROM.update(EEPROMId2, 'm');
    dimming=5;
    EEPROM.update(EEPROMDimming, dimming);
    toneFrequencyIndex=21;
    EEPROM.update(EEPROMTone,
                  toneFrequencyIndex);
  }
}

void setup()
{
  pinMode(rotaryAPin, INPUT);
  pinMode(rotaryBPin, INPUT);
  pinMode(rotarySwitchPin, INPUT_PULLUP);
  pinMode(beeperPin, OUTPUT);
  digitalWrite(beeperPin, LOW);
  lines[0].reserve(17);
  lines[1].reserve(17);
  lcd.begin(16, 2);
  lcd.clear();
/*
  If the rotary switch is pressed during power
  on, the values in the EEPROM are replaced
  by the default values. This is achived by
  deleting the chain "tim" in the first
  three bytes of the EEPROM.
*/
  if(digitalRead(rotarySwitchPin)==LOW)
  {
    EEPROM.update(EEPROMId0, 0xFF);
    EEPROM.update(EEPROMId1, 0xFF);
    EEPROM.update(EEPROMId2, 0xFF);
  }
  readEEPROM();
  setTransitions();
}

void loop()
{
  rotaryEncoderRead();
  timerManagement();
  UIFsm.run_machine();
  UIFsm.trigger(event);
  analogWrite(backLightPin, dimming*27);
}
[/code]
