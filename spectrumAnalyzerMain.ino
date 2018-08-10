#include "fix_fft.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

char im[128], data[128];
char x=10, ylim=40;
int i=0, val;
  
void setup(){
 Serial.begin(9600);
 display.begin(SSD1306_SWITCHCAPVCC,0x3C);
 display.setTextSize(0);
 display.setTextColor(WHITE);
 display.clearDisplay();
 analogReference(DEFAULT);
};

void loop()  {
 int min=1024, max=0;
 for(i=0;i<128;i++)
 {
   val=analogRead(A0);
   data[i]=val/4 - 128;
   im[i]=0;
   if(val>max) 
     max=val;
   if(val<min)  
     min=val; 
  };
  fix_fft(data,im,7,0);
    
  display.clearDisplay();
  for(i=1;i<64;i++)
  {
    int dat=sqrt(data[i]*data[i]+ im[i]*im[i]);
    display.drawLine(i*2+x,ylim,i*2+x,ylim-dat,WHITE);
   };
     
   display.setCursor(0,0);
   display.print("Spectrum Analyzer");
   display.display();
};



  
