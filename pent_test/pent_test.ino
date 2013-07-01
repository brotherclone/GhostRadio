#include <Potentiometer.h>

Potentiometer potentiometer2 = Potentiometer(A0); 

void setup() {
  Serial.begin(9600);
}

void loop() {

 Serial.println("Potentiometer 2");
 Serial.print("potentiometer2.getValue() ");
 Serial.println(potentiometer2.getValue(),DEC);
 delay(200);

}
