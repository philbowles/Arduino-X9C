/*
  X9C.h - Library for driving Intersil X9C series of digital potentiometers.
  Created by Phil Bowles, Jun 6 2017.
  Released into the public domain.
*/
#ifndef X9C_H
#define X9C_H
//
// direction "sense" is set between Vh/Rh (pin 3) and Vw/Rw (pin 5) i.e. with x9c104,
//		setPotMin will give abt 220R - 330R between these pins
//      setPotMax should give abt 100k
//
#include <Arduino.h>

#define X9C_UP LOW
#define X9C_DOWN HIGH
#define X9C_MAX 99
//
// stepPot explicilty does NOT save to NVRAM - allows reboot to old NVRAM value, with minor runtime tweaks
//
class X9C {
	public:
		X9C(){};
		~X9C(){};
		void begin(uint8_t cs,uint8_t inc,uint8_t ud);
		void setPot(uint8_t pos,bool save=true);
		void setPotMax(bool save=true);
	  	void setPotMin(bool save=true);
		void trimPot(uint8_t amt,uint8_t dir,bool save=true);
	private:
		uint8_t _cs, _inc, _ud;
		
		void _deselectAndSave();
		void _deselectNoSave();
		void _stepPot(uint8_t amt,uint8_t dir);
	};

#endif // X9C_H