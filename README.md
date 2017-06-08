# Arduino-X9C
Library for Intersil X9C series of digital potentiometers on Arduino and ESP8266 platforms

The X9C series are digitally-controlled potentiometers which are cheap and easy to use with Arduino and/or ESP8266 requiring only three lines: CS (chip select), INC (incremement) and UD (up/down).

(see datasheet: https://www.intersil.com/content/dam/Intersil/documents/x9c1/x9c102-103-104-503.pdf)

A key feature is to save the current value to non-volatile RAM (NVRAM) so that the chip boots with the last saved value. Once set, it does not need to be re-set each time the sketch loads. This library facilitates simple usage of the chip.

The main interface is:
```
void setPot(uint8_t pos,bool save=true);
```
"pos" is the percentage position of the "wiper" and "save"will save that position to NVRAM if true. Valid values are 0-99. NB the percentage value is approximate: the response curve is not absolutely linear. Thus on "pos" can be considered as an "absolute" value, i.e. a value of 50 on a -104 [10k] model will give close to 50k. Importantly, 0% is not zero ohms (on the -104 [100k] models I have tested, it's about 200-300 ohms). The exact value depends - in a complex fashion - with how many increments were taken to get to the current value and how rapidly they were performed. For practical purposes it's close: you may need to experiment with...
```		
void trimPot(uint8_t amt,uint8_t dir,bool save=true);
```
...which varies the current postion up or down by an amount which is one "click" or wiper position

Convenience methods are provided which should be obvious:
```
void setPotMax(bool save=true);  // equivalent to: setPot(99);

void setPotMin(bool save=true);  // equivalent to: setPot(0);
```
Prior to using any of the above, the initialisation function "begin" must be called to specify the CS, INC and UD hardware pins:
```
void begin(uint8_t cs,uint8_t inc,uint8_t ud);
```
IMPORTANT NOTES:

1. If none of the functions used has a save=true option specified, the chip will start up with whatever value was previously stored in NVRAM. This will require the user to setPot to the required operating value. For many applications, this will only ever need to be done once. Applications which require that the resistance is varied frequently or widely should guard against using the save=true option unless it absolutely certain that the current value is the one that will be required at next boot.

2. The NVRAM save operation takes 20ms (this is a fixed hardware feature). Users must take care not to rely on the value being valid until that time has elapsed, BUT 20ms is the exact time recommended in ESP8266 literature beyond which a delay() call is likely to cause a WDT reboot, hence care with timing may be required.
