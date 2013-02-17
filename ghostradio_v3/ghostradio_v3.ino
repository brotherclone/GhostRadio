#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>


SFEMP3Shield MP3player;


int redled = 11;        
int orangeled = 10; 
int brightness = 0;    
int fadeAmount = 5;   
int ghostradiotracknum = 40;
int ghostradiocurtrack = 1;
int ghostradioplaychecker =0;

void setup() {
  pinMode(redled, OUTPUT);
  pinMode(orangeled, OUTPUT);
  Serial.begin(9600);
  MP3player.begin();
  MP3player.playTrack(ghostradiocurtrack);
}


void loop() {
  analogWrite(redled, brightness);    
  brightness = brightness + fadeAmount;
  
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }      


  ghostradioplaychecker = MP3player.isPlaying();
  
  if (ghostradioplaychecker==0){
    ghostradiocurtrack++;
    analogWrite(orangeled, 255);
    delay(5);
    analogWrite(orangeled, 0);
    delay(5);
   analogWrite(orangeled, 255);
    delay(5);
    analogWrite(orangeled, 0);
      if(ghostradiocurtrack>ghostradiotracknum){
         ghostradiocurtrack = 1; 
      }
      MP3player.playTrack(ghostradiocurtrack);
    }
  
  delay(30);
}
