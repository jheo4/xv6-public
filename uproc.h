#ifndef UPROC
#define UPROC

#include "types.h"

#define MAX_STR_LENGTH 16 // proc name is 16 at proc.c

struct uproc{
  uint pid;
  uint uid;
  uint gid;
  uint ppid;
  char pname[MAX_STR_LENGTH];
  uint size;

  char state[MAX_STR_LENGTH];
  uint priority;
};

#endif
