/* SQUEEZE: decompressor ... */

#include "squeeze.h"
#include <stdlib.h>
#include <stdio.h>

struct C_NODE *dhead;

void get_table(struct C_NODE **x)
{
  if (((*x)=(struct C_NODE *)malloc(sizeof(struct C_NODE)))==NULL)
     error(ERR_RAM);

  if (readbit()) {
    (*x)->type = byte;
    if (readbit())
      (*x)->data.byte = CH_SPECIAL;
    else
      (*x)->data.byte = readbyte();
  }
  else {
    (*x)->type = node;
    get_table(&((*x)->data.tree.x0));
    get_table(&((*x)->data.tree.x1));
  }
}

void use_table(void)
{
  BOOL fin = FALSE;
  while (!fin) {
    struct C_NODE *x = dhead;
    while (x->type == node) {
      if (readbit())
        x = x->data.tree.x1;
      else
        x = x->data.tree.x0;
    }
    if (x->data.byte == CH_SPECIAL)
      fin=TRUE;
    else
      putc(x->data.byte, stdout);
  }
}

void decompress(void)
{
  while (readbit()) {	/* There is one more block */
    get_table(&dhead);
    use_table();
    free_system(dhead);
  }
}
