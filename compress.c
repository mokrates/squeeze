/* SQUEEZE: File - compressor ( Compress algorithm ) */

#include "squeeze.h"
#include <stdlib.h>
#include <stdio.h>

unsigned char c_block[COMPRESS_BLOCK];
unsigned int  c_block_length;
struct C_NODE *sort_array[257];
struct C_NODE *char_array[257];
struct C_NODE *head;

void clear_all(void)
{
  int i;
  for (i=0;i<257;i++) char_array[i]=NULL;
  c_block_length =0;
}

void read_block(void)
{
  int i, x;
  for (i=0;i<COMPRESS_BLOCK && !feof(stdin); i++) 
    if ((x=fgetc(stdin))!=EOF) {
      c_block[i]=x;
      c_block_length++;
    }
}

void count_chars(void)
{
  struct C_NODE *special;
  int count[257];
  int i;

  for (i=0;i<256;i++) count[i]=0;
  for (i=0;i<c_block_length;i++)
    count[c_block[i]]++;
  
  count[CH_SPECIAL] = 1;

  for (i=0;i<257;i++) {
    if (count[i]>0) {
      get_ram(struct C_NODE, char_array[i]);
      char_array[i]->type = byte;
      char_array[i]->data.byte = i;
      char_array[i]->back = NULL;
      char_array[i]->count = count[i];
      char_array[i]->value = nothing;
    }
    sort_array[i]=char_array[i];
  }
}

/* This function builds an binary tree up from bottom ... puh! */
void build_system(void)
{
  int remaining = 0;
  int i;
  int x1;
  int x0;
  struct C_NODE *new_node;

  do {
    x0=x1= -1;
    remaining = 0;

    for (i=0;i<257;i++)
      if (sort_array[i]!=NULL) {
	if (x0 == -1)
	  x0=i;
	else if ( x1 == -1 )
	  if ( sort_array[i]->count >= sort_array[x0]->count )
	    x1 = i;
	  else
	    { x1 = x0; x0 = i; }
	else if ( sort_array[i]->count <= sort_array[x0]->count )
	  { x1 = x0; x0 = i; }
        remaining++;
      }

    get_ram(struct C_NODE, new_node);
    new_node->type = node;
    new_node->count = sort_array[x0]->count + sort_array[x1]->count;
    new_node->back = NULL;
    new_node->value = nothing;
    new_node->data.tree.x0 = sort_array[x0];
    new_node->data.tree.x1 = sort_array[x1];
    sort_array[x0]->back = sort_array[x1]->back = new_node;
    sort_array[x0]->value = _0;
    sort_array[x1]->value = _1;
    sort_array[x1]=NULL;
    sort_array[x0]=new_node;

  } while (remaining>2);
  /* so, now is only one NODE remaining ... */
  for (i=0;i<257;i++)
    if (sort_array[i]!=NULL)	/* This last node is saved in head */
      head=sort_array[i];
}

void write_tree(struct C_NODE *x)
{
  if (x->type == byte) {
    writebit(1);
    if (x->data.byte == CH_SPECIAL)
      writebit(1);
    else {
      writebit(0);
      writebyte(x->data.byte);
    }
  }
  else if (x->type==node) {
    writebit(0);
    write_tree(x->data.tree.x0);
    write_tree(x->data.tree.x1);
  }
  else
    error(ERR_TREE);
}

void use_system(void)
{
  int i;
  /* At first, there must be written
     the binary tree with the 'morse'-codes */
  write_tree(head);

  /* and now: compress the file ... */
  for (i=0;i<=c_block_length;i++) {
    BOOL stack [60];
    int  sp=0;
    struct C_NODE *x;
    x = char_array[
      (i<c_block_length)  ?  c_block[i]  :  CH_SPECIAL
      ];
    while (x->value!=nothing) {
      if (x->value==_1)
        stack[sp++]=TRUE;
      else
        stack[sp++]=FALSE;
      x = x->back;
    }
    while (sp--)
      writebit(stack[sp]);
  }
}

void free_system(struct C_NODE *x)
{
  if (x->type == node) {
    free_system(x->data.tree.x0);
    free_system(x->data.tree.x1);
    free(x);
  }
  else
    free(x);
}

void compress(void)
{
  while (!feof(stdin)) {
    writebit(1);	/* There is a compressed block */
    clear_all();        /* clear the c_block array and the count array */
    read_block();       /* fill c_block */

    if (c_block_length==0)
      break;
         
    count_chars();      /* count every different char in c_block */
    build_system();     /* build 'morse'-table */
    use_system();       /* the 'really' compressing algorithm */
    free_system(head);	/* unbuild the 'morse'-table */
  }
  writebyte(0);
}
