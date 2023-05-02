/* SQUEEZE: misc.c (Verschiedenes) */

#include "squeeze.h"
#include <stdio.h>
#include <stdlib.h>

void error(int msg)
{
  fprintf(stderr, "squeeze: error: ");

  switch (msg) {
    case ERR_USAGE:
      /* stupid user? */
      fprintf(stderr, "usage: squeeze { -c | -x }\n");
      fprintf(stderr, "-- for help: squeeze help");
      break;

    case ERR_RAM:
      /* not enough ram? */
      fprintf(stderr, "not enough ram!");
      break;

    case ERR_TREE:
      /* tree error */
      fprintf(stderr, "fatal -- tree confusion");
      break;

    default:
      /* This should not happen */
      fprintf(stderr, "fatal -- unknown error message!");
  }

  fputc('\n',stderr);
  exit(msg);
}
