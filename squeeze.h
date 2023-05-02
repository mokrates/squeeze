/* SQUEEZE: Header */

/* definitions */
#ifndef BOOL	/* definition of BOOL - Type */
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif

typedef unsigned char BYTE;

#define ERR_USAGE 1
#define ERR_RAM 2
#define ERR_TREE 3

#define check_ptr_ok(x) if ((x)==NULL) error(ERR_RAM);
#define get_ram(x,y)    check_ptr_ok((y)=(x *)malloc(sizeof(x)))

#define COMPRESS_BLOCK 20000	/* length of the block to be compressed */
#define CH_SPECIAL 256

/* data declarations */
extern int quiet_mode;	/* quiet mode? */

/* function prototypes */
void decompress(void);  /* decompressed stdin to stdout */
void compress(void);	/* compresses stdin to stdout */

void error(int);	/* Prints error messages and exits */

BOOL readbit(void);	/* reads a bit from stdin */
void writebit(BOOL);	/* writes a bit to stdout */
BYTE readbyte(void);	/* reads a byte from stdin */
void writebyte(BYTE);	/* writes a byte to stdout */

/* data-types */

/* The following struct is used to build the binary tree ... */
struct C_NODE {
  union {
    struct {
      struct C_NODE *x1;
      struct C_NODE *x0;
    } tree;
    int byte;
  } data;
  enum { node, byte } type;
  enum { nothing, _0, _1 } value;
  int count;
  struct C_NODE *back;
};

void free_system(struct C_NODE *);
