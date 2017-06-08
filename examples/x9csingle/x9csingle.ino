#include <X9C.h>

#define INC 2   // D1 Mini D4 - pulled up in H/W (10k) ->  chip pin 1
#define UD 15   // D1 Mini D8                          ->  chip pin 2
#define CS 16   // D1 Mini D0 - pulled up in H/W (10k) ->  2nd chip pin 7

// "up" and "down" make sense in relation to the wiper pin 5 [VW/RW] and the HIGH end of the pot
// i.e. pin 3 [VH/RH], leaving pin 6 [VL/RL] unused (floating). You can easily use pin 6 instead
// pin 3, but "min" will actually mean "max" and vice versa. Also, the "setPot" percentage will
// set the equivalent of 100-<value>, i.e. setPot(70) will set the resistance between pins 5 and 6 
// to 30% of the maximum. (Of course in that case,the "unused" resistance between 5 and 3 will be 70%)
// Nothing to stop you using it as a full centre-tap potentiometer, the above example giving
// pin 3[H] -- 70% -- pin 5[W] -- 30% -- pin 6[L]


X9C pot;                           // create a pot controller

void setup() {
  Serial.begin(115200);
  pot.begin(CS,INC,UD);

  pot.setPot(44,true);            // true=save, so pot will be about 44% max value after shutdown if you do nothing else...
  
  pot.setPotMin(false);           // don't save set to 0% max - actually 200R-300R on my samples 
  pot.trimPot(10,X9C_UP,false);   // temporarily about 10% max value
  pot.trimPot(3,X9C_DOWN,false);  // pot will now be at about 7% (+10-3) max value
//
// because none of the above "tweaks" saved their value, you should find pot set at about 44% after shutdown
// and of course, next time you run the sketch.
//  

}

void loop() {

}
