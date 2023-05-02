/* SQUEEZE: main*/

#include "squeeze.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STREQ(x,y) (strcmp((x),(y))==0)	/* Equal? */

int quiet_mode = TRUE;

void main ( int argc, char **argv )
{
  if (argc==1)
    error(ERR_USAGE);
  if (STREQ(argv[1], "-h") ||
      STREQ(argv[1], "help") ||
      STREQ(argv[1], "--help")) {
    fprintf(stderr,
            "squeeze: a file compressor by M. Molle\n"
            "--- Usage: squeeze { -c | -x }\n"
            "-c: compress\n"
            "-x: decompress\n");
    exit(0);
  }
  if (STREQ(argv[1], "-c"))
     compress();
  else if (STREQ(argv[1], "-x"))
     decompress();
  else error(ERR_USAGE);
}
