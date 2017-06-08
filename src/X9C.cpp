/*
  X9C.cpp - Library for driving Intersil X9C series of digital potentiometers.
  Created by Phil Bowles, Jun 6 2017.
  Released into the public domain.
*/

#include <X9C.h>

void X9C::_deselectAndSave(){
  digitalWrite(_cs,HIGH);             // unselect chip and write current value to NVRAM
}

void X9C::_deselectNoSave(){
  digitalWrite(_inc,LOW);  
  digitalWrite(_cs,HIGH);             // unselect chip
  digitalWrite(_inc,HIGH);            // always leave inc high - makes coding cleaner / easier
}

void X9C::_stepPot(uint8_t amt,uint8_t dir){
  uint8_t cnt=(amt > X9C_MAX) ? X9C_MAX:amt;
  digitalWrite(_ud,dir);              // set direction
  digitalWrite(_cs,LOW);              // select chip
  while(cnt--){
    digitalWrite(_inc,LOW);           // falling pulse triggers wiper change (xN = cnt)
    delayMicroseconds(1);       
    digitalWrite(_inc,HIGH);
    delayMicroseconds(1);
  }
  delayMicroseconds(100);             // let new value settle; (datasheet P7 tIW)
}

void X9C::begin(uint8_t cs,uint8_t inc,uint8_t ud){
		_cs=cs;
    _inc=inc;
    _ud=ud;
    
    pinMode(_cs,OUTPUT);
    pinMode(_inc,OUTPUT);
    pinMode(_ud,OUTPUT);
}

void X9C::setPot(uint8_t pos,bool save){
  _stepPot(X9C_MAX+1,X9C_DOWN);       // crank it back to (beyond!) "zero" (usu. abt 300R for a 100k [104] pot)
  _stepPot(pos,X9C_UP);       	      // put it at abs value of where we want it...
  save ? _deselectAndSave():_deselectNoSave();
}

void X9C::setPotMax(bool save){
  _stepPot(X9C_MAX+1,X9C_UP);         // crank it up to (beyond!) max
  save ? _deselectAndSave():_deselectNoSave();
}
  
void X9C::setPotMin(bool save){
  _stepPot(X9C_MAX+1,X9C_DOWN);       // crank it back to (beyond!) "zero" (usu. abt 300R for a 100k [104] pot)
  save ? _deselectAndSave():_deselectNoSave();  
}
  
void X9C::trimPot(uint8_t amt,uint8_t dir,bool save){
  _stepPot(amt,dir);
  save ? _deselectAndSave():_deselectNoSave();
}

