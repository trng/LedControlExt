/**
 *
 * 2 functions added to LedControl:
 * - printChar
 * - printString
 *
 */

#ifndef LedControlExt_cpp
#define LedControlExt_cpp


#include <LedControlExt.h>
#include <LcExtFont.h>


void LedControlExt::printChar(byte matrixAddr, char shiftHorizontally, char symbol) {
  byte devices = getDeviceCount();
  if (matrixAddr<0 || matrixAddr>=devices)
    return;

  if (symbol<0 || symbol>=FONT_LEN)
    return;


  for(int row=0;row<8;row++) {
    setRow(matrixAddr, row, FONT[symbol][row]  >> shiftHorizontally);
  }
  
    
}


void LedControlExt::printString(String str, byte x, byte y=0) {
  byte totlalDevices=getDeviceCount();
  if (x > totlalDevices*8)
    return;

  byte strDotArray[totlalDevices][8];
  for (int i=0; i<totlalDevices; i++) {
    for (int j=0; j<8; j++) {
      strDotArray[i][j] = 0;
    }
  }
  
  unsigned int charsTotal = str.length();
  byte currentX = x;
  byte fontIdx = 0;
  byte currentMatrix;
  unsigned char symbol[8];
  for(int n=0; n<charsTotal; n++) {
    fontIdx = str.charAt(n) - 0x20;
    memcpy_P(symbol, FONT[fontIdx], 8);
    // left part
    currentMatrix = totlalDevices - currentX/8 - 1;
    for(int row=0; row<8; row++) {
      strDotArray[currentMatrix][row] = strDotArray[currentMatrix][row] | (symbol[row]  >> (currentX % 8));
      setRow(currentMatrix, row, strDotArray[currentMatrix][row]);
    }

    // rignt part
    currentX = currentX + 8;
    currentMatrix = totlalDevices - currentX/8 - 1;
    for(int row=0; row<8; row++) {
      strDotArray[currentMatrix][row] = strDotArray[currentMatrix][row] | (symbol[row]  << (8 - currentX % 8));
      setRow(currentMatrix, row, strDotArray[currentMatrix][row]);
    }
    currentX = currentX -2;
  }
  
    
}

#endif

