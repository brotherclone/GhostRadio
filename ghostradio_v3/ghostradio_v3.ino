#include <Potentiometer.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>


SFEMP3Shield MP3player;


int redled = 13;        
int orangeled = 10;  
int brightness = 0; 
int fadeAmount = 5;
int ghostradiotracknum = 40;
int dialread = 1;
int sensitivity =5;
int intdialstate = 1;
int setinit = 0;
int ghostradiocurtrack = ghostradiotracknum;

Potentiometer dial = Potentiometer(A0); 

void setup() {
  int intialtrack = random(1,ghostradiotracknum);
  int ghostradiocurtrack = intialtrack;
  pinMode(redled, OUTPUT);
  pinMode(orangeled, OUTPUT);
  Serial.begin(9600);
  MP3player.begin();
  MP3player.playTrack(intialtrack);
  
}


void loop() { 
  dialread = dial.getValue();
  if(!setinit){
    int k = 1023/sensitivity;
    intdialstate = dialread/k;
    setinit = 1;
  }else{
      CheckforDial(dialread);
  }
  analogWrite(redled, brightness);    
  analogWrite(orangeled, brightness);
  brightness = brightness + fadeAmount;
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
  if (!MP3player.isPlaying()){
    if((ghostradiocurtrack+2)>=40){
      ghostradiocurtrack = ghostradiocurtrack+2;
      MP3player.playTrack(ghostradiocurtrack);
      int setinit = 1;
    }else{
      ghostradiocurtrack = 1;
      MP3player.playTrack(ghostradiocurtrack);
      int setinit = 1;
    }
  }  
  delay(30);
}

int CheckforDial(int dr){
 int x = 1023/ghostradiotracknum;
 int y = 1023/sensitivity;
 int channel = dr/x;
 int checkinit = dr/y;
 if (channel<=0){
   channel=1; 
 }
 if((channel!=ghostradiocurtrack)&&(checkinit!=intdialstate)){
    ChangeChannel(channel);
 }
}

int ChangeChannel (int newchan){
  ghostradiocurtrack = newchan;
  MP3player.stopTrack();
  MP3player.playTrack(ghostradiocurtrack);
}








