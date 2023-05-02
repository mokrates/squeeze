/* SQUEEZE: input/output */

#include "squeeze.h"
#include <stdio.h>

/* This function reads sequentially the bits from stdin */
BOOL readbit(void)
{
  static int pos = 8;
  static BYTE byte = '\0';

  if (pos==8) {
    byte = fgetc(stdin);
    pos = 0;
  }
  return ((byte<<(pos++))&128)?TRUE:FALSE;
}

/* This function writes sequentially bits into stdout */
void writebit(BOOL bit)
{
  static int pos = 1;
  static BYTE byte = 0;

  byte+=(bit?1:0);
  if (pos==8) {
    pos=0;
    putc(byte,stdout);
    byte=0;
  }
  byte<<=1;
  pos++;
}

/* This function reads a byte even if it's not on byte-borders */
BYTE readbyte(void)
{
  BYTE ret=0;
  int i;

  for (i=0;i<8;i++) { ret<<=1; ret|=readbit(); }
  return ret;
}

/* This function writes a byte even if it's not on byte-borders */
void writebyte(BYTE byte)
{
  int i;
  for (i=0;i<8;i++) { writebit(byte&128); byte<<=1; }
}
