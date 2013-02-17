#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>
#include <Potentiometer.h>

SFEMP3Shield MP3player;

Potentiometer potentiometer1 = Potentiometer(A2); 
Potentiometer potentiometer2 = Potentiometer(A3); 

int redled = 11;        
int orangeled = 10; 
int brightness = 0;    
int fadeAmount = 5;   
int ghostradiovol = 0;
int ghostradiodif = 0;
int ghostradiovolcount = 0;
int ghostradiovolrange = 20;
int ghostradiotracknum = 40;
int ghostradiocurtrack = 23;
int ghostradiodial = 0;
int ghostradioplaychecker = 1;
int ghostradioischanging = 0;
int ghostradiostaticamt = 15;

void setup() {
  pinMode(redled, OUTPUT);
  pinMode(orangeled, OUTPUT);
  Serial.begin(9600);
  MP3player.begin();
  MP3player.playTrack(ghostradiocurtrack);
  ghostradiodial = potentiometer2.getValue()/5;
}
void loop() {
  ghostradiovol =  potentiometer1.getValue()/65;
  if((ghostradiodial!= ghostradiocurtrack) && (ghostradioischanging<1)){
    ghostradioischanging++;
    MP3player.stopTrack ();
    MP3player.playTrack(99);
  }
  if((ghostradiodial!= ghostradiocurtrack) && (ghostradioischanging>=1)){ 
    if((ghostradioischanging<ghostradiostaticamt)){
      ghostradioischanging++;
    } else {
      ghostradioischanging=0;
      ghostradiocurtrack = ghostradiodial;
      MP3player.stopTrack ();
      MP3player.playTrack(ghostradiocurtrack);
    }
  }
  if(((ghostradiodial>potentiometer2.getValue()/6)||(ghostradiodial>(potentiometer2.getValue()/6)))) {
     ghostradiodial = potentiometer2.getValue()/5;
     Serial.println("Correcting Drift");
     Serial.println(potentiometer2.getValue());
  }
  Serial.println(ghostradiodial);
  ghostradiovolcount++;
  if (ghostradiovolcount>=ghostradiovolrange) {
    ghostradiovolcount=0;
    ghostradiodif = ghostradiovol;
  }
  union twobyte mp3_vol; // create key_command existing variable that can be both word and double byte of left and right.
  mp3_vol.word = MP3player.GetVolume(); // 
  
  if(ghostradiovol!=ghostradiodif) {
    if (ghostradiovol<ghostradiodif) {
      if (mp3_vol.byte[1] >= 254) { // range check
          mp3_vol.byte[1] = 254;
        } else {
          mp3_vol.byte[1] += 2; // keep it simpler with whole dB's
        }
        MP3player.SetVolume(mp3_vol.byte[1], mp3_vol.byte[1]); // commit new volume
        ghostradiodif=ghostradiovol;
    }
    if (ghostradiovol>ghostradiodif) {
      if (mp3_vol.byte[1] <= 2) { // range check
          mp3_vol.byte[1] = 2;
        } else {
          mp3_vol.byte[1] -= 2;
        }
        MP3player.SetVolume(mp3_vol.byte[1], mp3_vol.byte[1]); // commit new volume
        ghostradiodif=ghostradiovol;
    }
 }
  
  analogWrite(redled, brightness);    
  analogWrite(orangeled, brightness);  
  brightness = brightness + fadeAmount;
  
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }      


  ghostradioplaychecker = MP3player.isPlaying();
  if (ghostradioplaychecker==0){
    MP3player.playTrack(ghostradiocurtrack);
  }
  
  delay(30);
}
