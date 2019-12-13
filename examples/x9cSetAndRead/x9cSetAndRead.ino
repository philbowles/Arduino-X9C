/* 
   Digital potentiometer X9C103S control

   This example controls digital potentiometer X9C103S module by seting its
   wiper position from 0 till 99. At the same time Arduino reads wiper pin
   value using its analog pin.
   Program outputs calculated theoretical and read values.

   The circuit:
         Arduino    X9C103S module
              5V -> Vcc
             GND -> GND
   digital pin 5 -> INC increment input
   digital pin 6 -> U/D up/down input
   digital pin 7 -> CS  chip select input
              5V -> VH  high terminal
   analog pin A0 -> VW  wiper terminal
             GND -> VL  low terminal
 */

#include <X9C.h>

const int INC = 5; // Arduino digital pin 5 connected to module increment 
                   // input pin INC
const int UD = 6;  // Arduino digital pin 6 connected to module up/down
                   // input pin U/D
const int CS = 7;  // Arduino digital pin 7 connected to module chip select
                   // input pin CS
const int wiperPin = A0; // Arduino analog pin A0 connected to the module
                         // wiper pin Vw/Rw
const float Vcc = 4930.0f; // voltage between GND and Arduino Aref pin measured
                           // with voltmeter (mV)
const float VccDiv99 = Vcc/99.0f; // theoretical voltage increment per one
                                  // digital potentiometer step (mV)
const float VccDiv1024 = Vcc/1024.0f; // voltage step size for Arduino analog
                                      // pin (mv)

X9C pot; // create a pot controller
int sensorValue = 0; // variable to store the value coming from analog pin
                     // (range from 0 to 1023)
void setup() {
  Serial.begin(9600);
  while (!Serial);// wait for serial port to connect
  pot.begin(CS,INC,UD); //setup pot pins
  Serial.println("Pot_step A0_value PotSet_mV PotRead_mV");
  for(uint8_t potStep=0;potStep<100;potStep++){
    if(potStep==0){
      pot.setPotMin(false); //begin with known position
    }else{
      pot.trimPot(1,X9C_UP); // increment pot value
    }
    sensorValue = analogRead(wiperPin); // read real pot value
    //report
    Serial.print(potStep);
    Serial.print(" ");
    Serial.print(sensorValue);
    Serial.print(" ");
    Serial.print(((float)potStep)*VccDiv99);
    Serial.print(" ");
    Serial.println(((float)sensorValue)*VccDiv1024);    
    delay(200);
  }
}

void loop(){
}
