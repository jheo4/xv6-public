#include "types.h"
#include "stat.h"
#include "user.h"

int backtrace_func3() __attribute__((noinline));
int backtrace_func3() {
  int stacked_val;
  stacked_val = backtrace();
  return stacked_val + uptime();
}

int backtrace_func2() __attribute__((noinline));
int backtrace_func2() {
  int stacked_val;
  stacked_val = backtrace_func3();
  return stacked_val + uptime();
}

int backtrace_func1() __attribute__((noinline));
int backtrace_func1() {
  int stacked_val;
  stacked_val = backtrace_func2();
  return stacked_val + uptime();
}


int
main(int argc, char *argv[])
{
  if(argc > 1){
    printf(2, "usage: bt \n");
    exit();
  }

  backtrace_func1();
  exit();
}
