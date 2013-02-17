
int redled = 11;           // the pin that the LED is attached to
int orangeled = 10; 
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by


void setup()  { 

  pinMode(redled, OUTPUT);
  pinMode(orangeled, OUTPUT);
} 


void loop()  { 

  analogWrite(redled, brightness);    
  analogWrite(orangeled, brightness);  
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}

