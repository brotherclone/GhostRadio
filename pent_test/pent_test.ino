#include <Potentiometer.h>
Potentiometer potentiometer1 = Potentiometer(A2); 
Potentiometer potentiometer2 = Potentiometer(A3); 

void setup() {
  Serial.begin(9600);
}

void loop() {
 Serial.println("Potentiometer 1");
 Serial.print("potentiometer1.getValue() ");
 Serial.println(potentiometer1.getValue(),DEC);
 Serial.println("Potentiometer 2");
 Serial.print("potentiometer2.getValue() ");
 Serial.println(potentiometer2.getValue(),DEC);
 delay(2000);

}
