/* This program is to inspect the CHAR - Trees built by SQUEEZE */

#include <stdio.h>
#include <ctype.h>
#include "squeeze.h"

char stack[100];
char sp = 0;

void writetree(void)
{
  char i;

  for (i=0; i<sp; i++)
    if (stack[i] == 1)
      printf(" |");
    else
      printf("  "); 
}

void tree(char x)
{
  BYTE byte;
  if (!readbit()) {	/* NODE */
    printf("#(%i)\n", sp+1);
    writetree();
    printf(" >0");
    stack[sp++] = 1;
    tree(1);
    sp--;
    writetree();
    printf(" \\1");
    stack[sp++] = 2;
    tree(0);
    sp--;
    if (x) { writetree(); printf("\n"); }
  }
  else	/* BYTE */
  if (readbit())	/* CH_SPECIAL */
    printf("CH_SPECIAL\n");
  else
    if (isprint(byte=readbyte()))
      printf("'%c'\n", byte);
    else
      printf("'\\x%02x'\n", byte);
}

void main(void)
{
  readbit(); 
  printf(" ");
  tree(0);
  printf("End of table: 0x%x", ftell(stdin)); 
}
