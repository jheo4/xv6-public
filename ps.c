#include "types.h"
#include "user.h"
#include "uproc.h"

#define MAX_NUM_PROCS 72

int getprocinfo(void) __attribute__((noinline));
int
getprocinfo(void){
  struct uproc *uproc_table = malloc(MAX_NUM_PROCS * sizeof(struct uproc));
  if(!uproc_table){
    printf(2, "[ps.c] getprocinfo: table allocation error\n");
    exit();
  }
  getprocs(MAX_NUM_PROCS, uproc_table);
  return 0;
}

int
main(int argc, char *argv[])
{
  if(argc > 1){
    printf(2, "usage: ps \n");
    exit();
  }
  getprocinfo();
  exit();
}
