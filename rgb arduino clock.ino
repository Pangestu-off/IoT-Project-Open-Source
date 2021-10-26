#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


#include <Adafruit_NeoPixel.h>
#include <DS3231.h>


DS3231  rtc(SDA, SCL);


Time  t;
#ifdef __AVR__
  #include <avr/power.h>
#endif


#define PIN             4
#define PIN2            5
#define PIN3            6
#define PIN4            7
#define PIN5            8
#define PIN6            9
#define PIN7            10
#define NUMPIXELS       7
Adafruit_NeoPixel pixels  = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4 = Adafruit_NeoPixel(NUMPIXELS, PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels5  = Adafruit_NeoPixel(NUMPIXELS, PIN5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels6  = Adafruit_NeoPixel(NUMPIXELS, PIN6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels7  = Adafruit_NeoPixel(NUMPIXELS, PIN7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(7, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(7, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(7, PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(7, PIN5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(7, PIN6, NEO_GRB + NEO_KHZ800);


byte sevendisplay[19][7]= {

                            {1,1,1,1,1,1,0},//0
                            {0,0,1,1,0,0,0},//1
                            {0,1,1,0,1,1,1},//2
                            {0,1,1,1,1,0,1},//3
                            {1,0,1,1,0,0,1},//4
                            {1,1,0,1,1,0,1},//5
                            {1,1,0,1,1,1,1},//6
                            {0,1,1,1,0,0,0},//7
                            {1,1,1,1,1,1,1},//8
                            {1,1,1,1,1,0,1},//9
                            {1,1,0,0,1,1,0},//C 10
                            {1,1,1,0,0,0,1},//' 11
                            {1,0,1,1,0,1,1},//H 12
                            {1,0,0,0,1,1,0},//L 13
                            {1,1,0,0,0,1,0},//T2 14
                            {1,1,0,0,1,1,1},//E  15
                            {0,0,0,0,0,0,0},//bo 16
                            {1,1,1,1,0,1,0},//N     17
                            {1,1,1,0,0,1,1},//P     18
                            
                            
  };
byte animation[7][7]= {

                            {1,0,0,0,0,0,0},//0
                            {0,1,0,0,0,0,0},//1
                            {0,0,1,0,0,0,0},//2
                            {0,0,0,1,0,0,0},//3
                            {0,0,0,0,1,0,0},//4
                            {0,0,0,0,0,1,0},//5
                            {0,0,0,0,0,0,1},//6
                           
                            
                            
                            
  };


  byte color[10][3]= {

                            {0,0,255},
                            {0,225,0},
                            {0,255,255},
                            {255,0,0},
                            {255,0,255},
                            {255,255,0},
                            {255,255,255},
                            {100,150,250},
                            {255,50,30},
                            {100,0,200},
                          
                            
                            
                            
  };

// Buzzer
int speakerPin = 13;
int alarmPin = 12;
int x=0;
int sayac=0;
int dg1=0;
int dg2=0;
int dg3=0;
int dg4=0;
int d0=0;
int d1=0;
int d2=0;
int d3=0;
int d4=0;
int d5=0;
String data= "hello";
int alarmSaat=0;
int alarmDak=0;
byte alarmDurumu=0;

// Leds


void setup() {
    pinMode(speakerPin, OUTPUT);
    pinMode(alarmPin, INPUT);

rtc.begin();
//rtc.setTime(20, 19, 40);
//rtc.setDate(3, 10, 2018);


    #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  strip.begin();
  strip.show();

  pixels.begin(); 
  pixels2.begin(); 
  pixels3.begin(); 
  pixels4.begin(); 
  pixels5.begin(); 
  pixels6.begin(); 
  pixels7.begin(); 


  Serial.begin(9600);
 

  
 
    
}

void loop() {
  t = rtc.getTime();
  if(Serial.available()) // Eer Bluetooth balants varsa kodalar altrr
{
  /*
 
 */
  
data = Serial.readStringUntil('.');
Serial.println(data);
if(data=="tarih")
{
String  gun = Serial.readStringUntil('.');
String ay = Serial.readStringUntil('.');
String yil = Serial.readStringUntil('.');
  int newd=gun.toInt();
  int newm= ay.toInt();
  int newy= yil.toInt();
rtc.setDate(newd,newm,newy);
data="date";
}



if(data=="saat")
{
String  saat = Serial.readStringUntil('.');
String dak = Serial.readStringUntil('.');

  int news=saat.toInt();
  int newd= dak.toInt();
  
rtc.setTime(news, newd, 00);
data="clock";
}

if(data=="alarm")
{
String  asaat = Serial.readStringUntil('.');
String adak = Serial.readStringUntil('.');

  alarmSaat=asaat.toInt();
  alarmDak= adak.toInt();
  alarmDurumu=1;
  data="clock";


}

}
  if(alarmDurumu==1&&alarmSaat==t.hour&&alarmDak==t.min)
    {
        for(int k=0; k<7;k++)
        {
      pixels.setPixelColor(k, pixels.Color(0,0,0));
      pixels2.setPixelColor(k, pixels.Color(0,0,0));
      pixels3.setPixelColor(k, pixels.Color(0,0,0));
      pixels4.setPixelColor(k, pixels.Color(0,0,0));
      pixels4.setPixelColor(k, pixels.Color(0,0,0));
      pixels5.setPixelColor(k, pixels.Color(0,0,0));
      pixels6.setPixelColor(k, pixels.Color(0,0,0));
      pixels7.setPixelColor(k, pixels.Color(0,0,0));
      pixels.show();
      pixels2.show();
      pixels3.show();
      pixels4.show();
      pixels5.show();
      pixels6.show();
      pixels7.show();
        }
    alarmDurumu==0;
    GameOfThrones();
    
    
  }
  




  int k=1;
  if(x==0)
  {
   pixels7.setPixelColor(0, pixels7.Color(color[dg4][0],color[dg4][1],color[dg4][2])); 
   pixels7.setPixelColor(1, pixels7.Color(color[dg4][0],color[dg4][1],color[dg4][2])); 
   pixels7.show();
  }
  if(x==1)
  {
   pixels7.setPixelColor(0, pixels7.Color(0,0,0)); 
   pixels7.setPixelColor(1, pixels7.Color(0,0,0)); 
   pixels7.show();
  }
   x=x+1;
   delay(500);
   if(x==2)
   {
    x=0;
    };
if(data=="d1")
{
  data=" ";

  dg1++;
  if(dg1==10)
  {dg1=0;}
  yaz();
  
  }


  if(data=="d2")
{
  data=" ";

  dg2++;
  if(dg2==10)
  {dg2=0;}
  yaz();
  }
  if(data=="d3")
{
  data=" ";

  dg3++;
  if(dg3==10)
  {dg3=0;}
  yaz();
  }

      if(data=="d4")
{
  data=" ";

  dg4++;
  if(dg4==10)
  {dg4=0;}
  yaz();
  }
 if(data=="all")
{sayac++;
if(sayac==10)
{sayac=0;}
dg1=sayac;
dg2=sayac;
dg3=sayac;
data=" ";
yaz();
  }
if(data=="hello")
{
 d0=12;
 d1=15;
 d2=13;
 d3=13;
 d4=0;
 d5=16;
yaz();
}

//clock

if(data=="clock")
{
d0=(t.hour)/10;
d1=(t.hour)%10;
d2=(t.min)/10;
d3=(t.min)%10;
d4=(t.sec)/10;
d5=(t.sec)%10;
yaz();
}


if(data=="date")
{
 d0=(t.date)/10;
 d1=(t.date)%10;
 d2=(t.mon)/10;
 d3=(t.mon)%10;
 d5=(t.year)%100;
 d4=(d5)/10;
 d5=(d5)%10;
  yaz();
}
if(data=="temp")
{
int sayi=(rtc.getTemp())*100;
d0=sayi/1000;
d1=sayi%1000;
d1=d1/100;
d2=sayi%100;
d2=d2/10;
d3=(sayi)%10;
d4=10;
d5=11;
yaz();
  
  }

if(data=="animation")
{
  





  
  
for(int g=0;g<NUMPIXELS;g++)
  { delay(500);
for(int i=0;i<NUMPIXELS;i++)
  {  

    if(animation[g][i]==1)
    {
    pixels.setPixelColor(i, pixels.Color(color[dg1][0],color[dg1][1],color[dg1][2])); 
    pixels.show(); 
    }
    else
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0)); 
    pixels.show();
      }
      
    if(animation[g][i]==1)
    {
    pixels2.setPixelColor(i, pixels2.Color(color[dg1][0],color[dg1][1],color[dg1][2])); 
    pixels2.show();
    }
     else
    {
      pixels2.setPixelColor(i, pixels2.Color(0,0,0)); 
    pixels2.show();
      }




    
   if(animation[g][i]==1)
    {
    pixels3.setPixelColor(i, pixels3.Color(color[dg2][0],color[dg2][1],color[dg2][2])); 
    pixels3.show();
    }
    else
    {
      pixels3.setPixelColor(i, pixels3.Color(0,0,0)); 
    pixels3.show();
      }

      if(animation[g][i]==1)
    {
    pixels4.setPixelColor(i, pixels4.Color(color[dg2][0],color[dg2][1],color[dg2][2])); 
    pixels4.show(); 
    }
    else
    {
      pixels4.setPixelColor(i, pixels4.Color(0,0,0)); 
    pixels4.show(); 
      
    }



     if(animation[g][i]==1)
    {
    pixels5.setPixelColor(i, pixels5.Color(color[dg3][0],color[dg3][1],color[dg3][2])); 
    pixels5.show();
    }
    else
    {
      pixels5.setPixelColor(i, pixels5.Color(0,0,0)); 
    pixels5.show();
      }

      if(animation[g][i]==1)
    {
    pixels6.setPixelColor(i, pixels6.Color(color[dg3][0],color[dg3][1],color[dg3][2])); 
    pixels6.show(); 
    }
    else
    {
      pixels6.setPixelColor(i, pixels6.Color(0,0,00)); 
    pixels6.show(); 
      
    }
  }

}
  
 
  colorWipe(strip.Color(255, 0, 0), 100); // Red
  colorWipe(strip2.Color(0, 255, 0), 100); // Green
  colorWipe(strip3.Color(0, 0, 255), 100); // Blue
  colorWipe(strip4.Color(0, 0, 0, 255), 100); // White RGBW
  

  rainbow(50);

yaz();




data=" ";
}

  
}





















void yaz()
{
for(int i=0;i<NUMPIXELS;i++)
  {

    if(sevendisplay[d0][i]==1)
    {
    pixels.setPixelColor(i, pixels.Color(color[dg1][0],color[dg1][1],color[dg1][2])); 
    pixels.show(); 
    }
    else
    {
      pixels.setPixelColor(i, pixels.Color(0,0,0)); 
    pixels.show();
      }
      
    if(sevendisplay[d1][i]==1)
    {
    pixels2.setPixelColor(i, pixels2.Color(color[dg1][0],color[dg1][1],color[dg1][2])); 
    pixels2.show();
    }
     else
    {
      pixels2.setPixelColor(i, pixels2.Color(0,0,0)); 
    pixels2.show();
      }




    
   if(sevendisplay[d2][i]==1)
    {
    pixels3.setPixelColor(i, pixels3.Color(color[dg2][0],color[dg2][1],color[dg2][2])); 
    pixels3.show();
    }
    else
    {
      pixels3.setPixelColor(i, pixels3.Color(0,0,0)); 
    pixels3.show();
      }

      if(sevendisplay[d3][i]==1)
    {
    pixels4.setPixelColor(i, pixels4.Color(color[dg2][0],color[dg2][1],color[dg2][2])); 
    pixels4.show(); 
    }
    else
    {
      pixels4.setPixelColor(i, pixels4.Color(0,0,0)); 
    pixels4.show(); 
      
    }



     if(sevendisplay[d4][i]==1)
    {
    pixels5.setPixelColor(i, pixels5.Color(color[dg3][0],color[dg3][1],color[dg3][2])); 
    pixels5.show();
    }
    else
    {
      pixels5.setPixelColor(i, pixels5.Color(0,0,0)); 
    pixels5.show();
      }

      if(sevendisplay[d5][i]==1)
    {
    pixels6.setPixelColor(i, pixels6.Color(color[dg3][0],color[dg3][1],color[dg3][2])); 
    pixels6.show(); 
    }
    else
    {
      pixels6.setPixelColor(i, pixels6.Color(0,0,00)); 
    pixels6.show(); 
      
    }
  }

}














void ilumina(int note){
  if(note == NOTE_G4 || note == NOTE_G3 || note == NOTE_GS3) {
   pixels.setPixelColor(0, pixels.Color(250,0,0)); 
   pixels.show();
   pixels2.setPixelColor(0, pixels2.Color(250,0,0)); 
   pixels2.show();
   pixels3.setPixelColor(0, pixels3.Color(250,0,0)); 
   pixels3.show();
   pixels4.setPixelColor(0, pixels4.Color(250,0,0)); 
   pixels4.show();
   pixels5.setPixelColor(0, pixels5.Color(250,0,0)); 
   pixels5.show();
   pixels6.setPixelColor(0, pixels6.Color(250,0,0)); 
   pixels6.show();






   
  } else if (note == NOTE_C4) {
    pixels.setPixelColor(1, pixels.Color(0,250,0)); 
    pixels.show();
    pixels2.setPixelColor(1, pixels2.Color(0,250,0)); 
    pixels2.show();
   pixels3.setPixelColor(1, pixels3.Color(0,250,0)); 
    pixels3.show();
    pixels4.setPixelColor(1, pixels4.Color(0,250,0)); 
    pixels4.show();
    pixels5.setPixelColor(1, pixels5.Color(0,250,0)); 
    pixels5.show();
    pixels6.setPixelColor(1, pixels6.Color(0,250,0)); 
    pixels6.show();
    
  } else if(note == NOTE_AS3) {
    pixels.setPixelColor(2, pixels.Color(0,0,250)); 
    pixels.show();
    pixels2.setPixelColor(2, pixels2.Color(0,0,250)); 
    pixels2.show();
    pixels3.setPixelColor(2, pixels3.Color(0,0,250)); 
    pixels3.show();
    pixels4.setPixelColor(2, pixels4.Color(0,0,250)); 
    pixels4.show();
    pixels5.setPixelColor(2, pixels5.Color(0,250,0)); 
    pixels5.show();
    pixels6.setPixelColor(2, pixels6.Color(0,250,0)); 
    pixels6.show();
    
  } else if (note == NOTE_DS4) {
    pixels.setPixelColor(3, pixels.Color(250,0,0)); 
    pixels.show();
    pixels3.setPixelColor(3, pixels3.Color(250,0,0)); 
    pixels3.show();
    pixels2.setPixelColor(3, pixels2.Color(250,0,0)); 
    pixels2.show();
    pixels4.setPixelColor(3, pixels4.Color(250,0,0)); 
    pixels4.show();

     pixels5.setPixelColor(3, pixels5.Color(250,0,0)); 
    pixels5.show();
     pixels6.setPixelColor(3, pixels6.Color(250,0,0)); 
    pixels6.show();



    
  } else if (note == NOTE_D4) {
    pixels.setPixelColor(4, pixels.Color(0,250,0)); 
    pixels.show();
    pixels2.setPixelColor(4, pixels2.Color(0,250,0)); 
    pixels2.show();
     pixels3.setPixelColor(4, pixels3.Color(0,250,0)); 
    pixels3.show();
     pixels4.setPixelColor(4, pixels4.Color(0,250,0)); 
    pixels4.show();

    pixels5.setPixelColor(4, pixels5.Color(0,250,0)); 
    pixels5.show();
    pixels6.setPixelColor(4, pixels6.Color(0,250,0)); 
    pixels6.show();

    
  } else if (note == NOTE_F4) {
    pixels.setPixelColor(5, pixels.Color(0,0,250)); 
    pixels.show();
    pixels3.setPixelColor(5, pixels3.Color(0,0,250)); 
    pixels3.show();
     pixels2.setPixelColor(5, pixels2.Color(0,0,250)); 
    pixels2.show();
    pixels4.setPixelColor(5, pixels4.Color(0,0,250)); 
    pixels4.show();

    pixels5.setPixelColor(5, pixels5.Color(0,0,250)); 
    pixels5.show();
    pixels6.setPixelColor(5, pixels6.Color(0,0,250)); 
    pixels6.show();
  } else if (note == NOTE_F3) {
    pixels.setPixelColor(7, pixels.Color(250,0,0)); 
    pixels.show();
  } else if(note == NOTE_E4) {
   pixels.setPixelColor(6, pixels.Color(0,0,250)); 
    pixels.show();
    pixels3.setPixelColor(6, pixels3.Color(0,0,250)); 
    pixels3.show();
    pixels2.setPixelColor(6, pixels2.Color(0,0,250)); 
    pixels2.show();
    pixels4.setPixelColor(6, pixels4.Color(0,0,250)); 
    pixels4.show();


    pixels5.setPixelColor(6, pixels5.Color(0,0,250)); 
    pixels5.show();
    pixels6.setPixelColor(6, pixels6.Color(0,0,250)); 
    pixels6.show();
  }
}

void apaga(int note){
  if(note == NOTE_G4 || note == NOTE_G3 || note == NOTE_GS3) {
   pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.show();
    pixels3.setPixelColor(0, pixels3.Color(0,0,0)); 
    pixels3.show();
    pixels4.setPixelColor(0, pixels4.Color(0,0,0)); 
    pixels4.show();
    pixels2.setPixelColor(0, pixels2.Color(0,0,0)); 
    pixels2.show();



    pixels5.setPixelColor(0, pixels5.Color(0,0,0)); 
    pixels5.show();
    pixels6.setPixelColor(0, pixels6.Color(0,0,0)); 
    pixels6.show();
  } else if (note == NOTE_C4) {
    pixels.setPixelColor(1, pixels.Color(0,0,0)); 
    pixels.show();
     pixels3.setPixelColor(1, pixels3.Color(0,0,0)); 
    pixels3.show();
     pixels4.setPixelColor(1, pixels4.Color(0,0,0)); 
    pixels4.show();
    pixels2.setPixelColor(1, pixels2.Color(0,0,0)); 
    pixels2.show();

      pixels5.setPixelColor(1, pixels5.Color(0,0,0)); 
    pixels5.show();
    pixels6.setPixelColor(1, pixels6.Color(0,0,0)); 
    pixels6.show();
  } else if(note == NOTE_AS3) {
    pixels.setPixelColor(2, pixels.Color(0,0,0)); 
    pixels.show();
    pixels2.setPixelColor(2, pixels2.Color(0,0,0)); 
    pixels2.show();
    pixels3.setPixelColor(2, pixels3.Color(0,0,0)); 
    pixels3.show();
    pixels4.setPixelColor(2, pixels4.Color(0,0,0)); 
    pixels4.show();



      pixels5.setPixelColor(2, pixels5.Color(0,0,0)); 
    pixels5.show();
    pixels6.setPixelColor(2, pixels6.Color(0,0,0)); 
    pixels6.show();
  } else if (note == NOTE_DS4) {
    pixels.setPixelColor(3, pixels.Color(0,0,0)); 
    pixels.show();
    pixels2.setPixelColor(3, pixels2.Color(0,0,0)); 
    pixels2.show();
    pixels3.setPixelColor(3, pixels3.Color(0,0,0)); 
    pixels3.show();
    pixels4.setPixelColor(3, pixels4.Color(0,0,0)); 
    pixels4.show();

      pixels5.setPixelColor(3, pixels5.Color(0,0,0)); 
    pixels5.show();
    pixels6.setPixelColor(3, pixels6.Color(0,0,0)); 
    pixels6.show();
  } else if (note == NOTE_D4) {
   pixels.setPixelColor(4, pixels.Color(0,0,0)); 
    pixels.show();
    pixels2.setPixelColor(4, pixels2.Color(0,0,0)); 
    pixels2.show();
    pixels3.setPixelColor(4, pixels3.Color(0,0,0)); 
    pixels3.show();
    pixels4.setPixelColor(4, pixels4.Color(0,0,0)); 
    pixels4.show();
    pixels5.setPixelColor(4, pixels5.Color(0,0,0)); 
    pixels5.show();
    pixels6.setPixelColor(4, pixels6.Color(0,0,0)); 
    pixels6.show();
    
  } else if (note == NOTE_F4) {
    pixels.setPixelColor(5, pixels.Color(0,0,0)); 
    pixels.show();
    pixels2.setPixelColor(5, pixels2.Color(0,0,0)); 
    pixels2.show();
    pixels3.setPixelColor(5, pixels3.Color(0,0,0)); 
    pixels3.show();
    pixels4.setPixelColor(5, pixels4.Color(0,0,0)); 
    pixels4.show();
    pixels5.setPixelColor(5, pixels5.Color(0,0,0)); 
    pixels5.show();
    pixels6.setPixelColor(5, pixels6.Color(0,0,0)); 
    pixels6.show();
  } else if (note == NOTE_F3) {
    pixels.setPixelColor(7, pixels.Color(0,0,0)); 
    pixels.show();
  } else if(note == NOTE_E4) {
    pixels.setPixelColor(6, pixels.Color(0,0,0)); 
    pixels.show();
    
    pixels2.setPixelColor(6, pixels2.Color(0,0,0)); 
    pixels2.show();
    pixels3.setPixelColor(6, pixels3.Color(0,0,0)); 
    pixels3.show();
    pixels4.setPixelColor(6, pixels4.Color(0,0,0)); 
    pixels4.show();
    pixels5.setPixelColor(6, pixels5.Color(0,0,0)); 
    pixels5.show();
    pixels6.setPixelColor(6, pixels6.Color(0,0,0)); 
    pixels6.show();
  }
}














void GameOfThrones() {
  for(int i=0; i<4; i++) {
    tone(speakerPin, NOTE_G4);
    ilumina(NOTE_G4);
    delay(500);
    noTone(speakerPin);
    apaga(NOTE_G4);

    tone(speakerPin, NOTE_C4);
    ilumina(NOTE_C4);
    delay(500);
    noTone(speakerPin);
    apaga(NOTE_C4);

    tone(speakerPin, NOTE_DS4);
    ilumina(NOTE_DS4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_DS4);

    tone(speakerPin, NOTE_F4);
    ilumina(NOTE_F4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_F4);
  }

  for(int i=0; i<4; i++){
    tone(speakerPin, NOTE_G4);
    ilumina(NOTE_G4);
    delay(500);
    noTone(speakerPin);
    apaga(NOTE_G4);

    tone(speakerPin, NOTE_C4);
    ilumina(NOTE_C4);
    delay(500);
    noTone(speakerPin);
    apaga(NOTE_C4);

    tone(speakerPin, NOTE_E4);
    ilumina(NOTE_E4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_E4);

    tone(speakerPin, NOTE_F4);
    ilumina(NOTE_F4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_F4);
  }

    tone(speakerPin, NOTE_G4);
    ilumina(NOTE_G4);
    delay(1500);
    noTone(speakerPin);
    apaga(NOTE_G4);

    tone(speakerPin, NOTE_C4);
    ilumina(NOTE_C4);
    delay(1500);
    apaga(NOTE_C4);

//
    tone(speakerPin, NOTE_E4);
    ilumina(NOTE_E4);
    delay(250);
    apaga(NOTE_C4);

    tone(speakerPin, NOTE_F4);
    ilumina(NOTE_F4);
    delay(250);
    apaga(NOTE_C4);
//
    tone(speakerPin, NOTE_G4);
    ilumina(NOTE_G4);
    delay(1000);
    noTone(speakerPin);
    apaga(NOTE_G4);

    tone(speakerPin, NOTE_C4);
    ilumina(NOTE_C4);
    delay(1000);
    apaga(NOTE_C4);

    tone(speakerPin, NOTE_DS4);
    ilumina(NOTE_DS4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_DS4);

    tone(speakerPin, NOTE_F4);
    ilumina(NOTE_F4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_F4);
    
  for(int i=0; i<3; i++) {
    
    tone(speakerPin, NOTE_D4);
    ilumina(NOTE_D4);
    delay(500);
    noTone(speakerPin);
    apaga(NOTE_D4);
    
    tone(speakerPin, NOTE_G3);
    ilumina(NOTE_G3);
    delay(500);
    noTone(speakerPin);
    apaga(NOTE_G3);

    tone(speakerPin, NOTE_AS3);
    ilumina(NOTE_AS3);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_AS3);

    tone(speakerPin, NOTE_C4);
    ilumina(NOTE_C4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_C4);
    
    
  }
  


      tone(speakerPin, NOTE_D4);
      ilumina(NOTE_D4);
      delay(1500);
      noTone(speakerPin);
      apaga(NOTE_D4);
      
      tone(speakerPin, NOTE_F4);
      ilumina(NOTE_F4);
      delay(1500);
      noTone(speakerPin);
      apaga(NOTE_F4);

      tone(speakerPin, NOTE_AS3);
      ilumina(NOTE_AS3);
      delay(1000);
      noTone(speakerPin);
      apaga(NOTE_AS3);

      tone(speakerPin, NOTE_DS4);
      ilumina(NOTE_DS4);
      delay(250);
      noTone(speakerPin);
      apaga(NOTE_DS4);

      tone(speakerPin, NOTE_D4);
      ilumina(NOTE_D4);
      delay(250);
      noTone(speakerPin);
      apaga(NOTE_D4);

      tone(speakerPin, NOTE_F4);
      ilumina(NOTE_F4);
      delay(1000);
      noTone(speakerPin);
      apaga(NOTE_F4);

      tone(speakerPin, NOTE_AS3);
      ilumina(NOTE_AS3);
      delay(1000);
      noTone(speakerPin);
      apaga(NOTE_AS3);

      tone(speakerPin, NOTE_DS4);
      ilumina(NOTE_DS4);
      delay(250);
      noTone(speakerPin);
      apaga(NOTE_DS4);

      tone(speakerPin, NOTE_D4);
      ilumina(NOTE_D4);
      delay(250);
      noTone(speakerPin);
      apaga(NOTE_D4);

      tone(speakerPin, NOTE_C4);
      ilumina(NOTE_C4);
      delay(500);
      noTone(speakerPin);
      apaga(NOTE_C4);

  for(int i=0; i<3; i++) {
      tone(speakerPin, NOTE_GS3);
      ilumina(NOTE_GS3);
      delay(250);
      noTone(speakerPin);
      apaga(NOTE_GS3);

      tone(speakerPin, NOTE_AS3);
      ilumina(NOTE_AS3);
      delay(250);
      noTone(speakerPin);
      apaga(NOTE_AS3);

      tone(speakerPin, NOTE_C4);
      ilumina(NOTE_C4);
      delay(500);
      noTone(speakerPin);
      apaga(NOTE_C4);

      tone(speakerPin, NOTE_F3);
      ilumina(NOTE_F3);
      delay(500);
      noTone(speakerPin);
      apaga(NOTE_F3);
  }

    tone(speakerPin, NOTE_G4);
    ilumina(NOTE_G4);
    delay(1000);
    noTone(speakerPin);
    apaga(NOTE_G4);

    tone(speakerPin, NOTE_C4);
    ilumina(NOTE_C4);
    delay(1000);
    noTone(speakerPin);
    apaga(NOTE_C4);

    tone(speakerPin, NOTE_DS4);
    ilumina(NOTE_DS4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_DS4);

    tone(speakerPin, NOTE_F4);
    ilumina(NOTE_F4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_F4);

    tone(speakerPin, NOTE_G4);
    ilumina(NOTE_G4);
    delay(1000);
    noTone(speakerPin);
    apaga(NOTE_G4);

    tone(speakerPin, NOTE_C4);
    ilumina(NOTE_C4);
    delay(1000);
    noTone(speakerPin);
    apaga(NOTE_C4);

    tone(speakerPin, NOTE_DS4);
    ilumina(NOTE_DS4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_DS4);

    tone(speakerPin, NOTE_F4);
    ilumina(NOTE_F4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_F4);

    tone(speakerPin, NOTE_D4);
    ilumina(NOTE_D4);
    delay(500);
    noTone(speakerPin);
    apaga(NOTE_D4);

  for(int i=0; i<4; i++) {
    tone(speakerPin, NOTE_G3);
    ilumina(NOTE_G3);
    delay(500);
    noTone(speakerPin);
    apaga(NOTE_G3);

    tone(speakerPin, NOTE_AS3);
    ilumina(NOTE_AS3);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_AS3);

    tone(speakerPin, NOTE_C4);
    ilumina(NOTE_C4);
    delay(250);
    noTone(speakerPin);
    apaga(NOTE_C4);

    tone(speakerPin, NOTE_D4);
    ilumina(NOTE_D4);
    delay(500);
    noTone(speakerPin);
    apaga(NOTE_D4);
  }
}





void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
     strip2.setPixelColor(i, c);
      strip3.setPixelColor(i, c);
       strip4.setPixelColor(i, c);
       strip5.setPixelColor(i, c);
       strip6.setPixelColor(i, c);
    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
      strip2.setPixelColor(i, Wheel((i+j) & 255));
      strip3.setPixelColor(i, Wheel((i+j) & 255));
      strip4.setPixelColor(i, Wheel((i+j) & 255));
      strip5.setPixelColor(i, Wheel((i+j) & 255));
      strip6.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      strip2.setPixelColor(i, Wheel(((i * 256 / strip2.numPixels()) + j) & 255));
      strip3.setPixelColor(i, Wheel(((i * 256 / strip3.numPixels()) + j) & 255));
      strip4.setPixelColor(i, Wheel(((i * 256 / strip4.numPixels()) + j) & 255));
      strip5.setPixelColor(i, Wheel(((i * 256 / strip5.numPixels()) + j) & 255));
      strip6.setPixelColor(i, Wheel(((i * 256 / strip6.numPixels()) + j) & 255));
      
    }
    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        strip2.setPixelColor(i+q, Wheel( (i+j) % 255)); 
        strip3.setPixelColor(i+q, Wheel( (i+j) % 255)); 
        strip4.setPixelColor(i+q, Wheel( (i+j) % 255)); 
        strip5.setPixelColor(i+q, Wheel( (i+j) % 255)); 
        strip6.setPixelColor(i+q, Wheel( (i+j) % 255)); 
      }
      strip.show();
      strip2.show();
      strip3.show();
      strip4.show();
      strip5.show();
      strip6.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
        
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
