#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>
#include <Potentiometer.h>

// Below is not needed if interrupt driven. Safe to remove if not using.
#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
  #include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
  #include <SimpleTimer.h>
#endif

SFEMP3Shield MP3player;

Potentiometer potentiometer1 = Potentiometer(A0); 
Potentiometer potentiometer2 = Potentiometer(A1); 

int ledPin1 = 10;                 
int ledPin2 = 11; 

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);
  //start the shield
  MP3player.begin();
  //start playing track 1
  MP3player.playTrack(1);
}
void loop() {
  digitalWrite(ledPin1, HIGH); 
  digitalWrite(ledPin2, HIGH); 
  Serial.println("Potentiometer 1");
  Serial.print(potentiometer1.getValue());
  Serial.println("Potentiometer 2");
  Serial.print(potentiometer2.getValue());
  delay(2000);
  digitalWrite(ledPin1, LOW); 
  digitalWrite(ledPin2, LOW); 

}
