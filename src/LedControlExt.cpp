/**
 *
 * 2 functions added to LedControl:
 * - printChar
 * - printString
 *
 */

#ifndef LedControlExt_cpp
#define LedControlExt_cpp

#define private protected
#include <LedControlExt.h>
#include <LcExtFont.h>



void LedControlExt::printChar(byte matrixAddr, char shiftHorizontally, char symbol) {
  if (matrixAddr<0 || matrixAddr>=maxDevices)
    return;

  if (symbol<0 || symbol>=FONT_LEN)
    return;


  for(int row=0;row<8;row++) {
    setRow(matrixAddr, row, FONT[symbol][row]  >> shiftHorizontally);
  }
  
    
}


void LedControlExt::printString(String str, byte x, byte y=0) {
  if (x > maxDevices*8)
    return;

  byte strDotArray[maxDevices][8];
  for (int i=0; i<maxDevices; i++) {
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
    currentMatrix = maxDevices - currentX/8 - 1;
    for(int row=0; row<8; row++) {
      strDotArray[currentMatrix][row] = strDotArray[currentMatrix][row] | (symbol[row]  >> (currentX % 8));
      setRow(currentMatrix, row, strDotArray[currentMatrix][row]);
    }

    // rignt part
    currentX = currentX + 8;
    currentMatrix = maxDevices - currentX/8 - 1;
    for(int row=0; row<8; row++) {
      strDotArray[currentMatrix][row] = strDotArray[currentMatrix][row] | (symbol[row]  << (8 - currentX % 8));
      setRow(currentMatrix, row, strDotArray[currentMatrix][row]);
    }
    currentX = currentX - 2;
  }
  
    
}

void LedControlExt::clearCascade() {
    for(int i=0; i<maxDevices; i++) {
      clearDisplay(i);
    }
}



#endif

