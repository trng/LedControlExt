/**
 *
 * Add 2 functions to LedControl
 * printChar
 * printString
 *
 */


#ifndef LedControlExt_h
#define LedControlExt_h

#include <LedControl.h>
#include <avr/pgmspace.h>

class LedControlExt: public LedControl
{
    public:
        /*
         * Create a new controler
         * Params :
         * dataPin              pin on the Arduino where data gets shifted out
         * clockPin             pin for the clock
         * csPin                pin for selecting the device
         * numDevices           number of devices that can be controled (default - 1)
         */
        LedControlExt(int dataPin, int clkPin, int csPin, int numDevices=1):LedControl(dataPin, clkPin, csPin, numDevices){
          int devices = getDeviceCount();
          //we have to init all devices in a loop
          for(int address=0;address<devices;address++) {
            /*The MAX72XX is in power-saving mode on startup*/
            shutdown(address,false);
            /* Set the brightness to a medium values */
            setIntensity(address,4);
            /* and clear the display */
            clearDisplay(address);
          }


        }
        
        void printChar(byte matrixAddr, char shiftHorizontally, char symbol);

        void printString(String str, byte x, byte y=0);
        void clearCascade();
  
};

#endif
