#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


int
sys_backtrace(void)
{
  // trap frame layout of xv6
  cprintf("trapframe registers============================================\n");
  cprintf("eax: 0x%x    ebx: 0x%x   ecx: 0x%x   edx: 0x%x\n",
      myproc()->tf->eax, myproc()->tf->ebx,
      myproc()->tf->ecx, myproc()->tf->edx);
  cprintf("eip: 0x%x    ebp: 0x%x   esp: 0x%x\n", myproc()->tf->eip,
      myproc()->tf->ebp, myproc()->tf->esp);
  cprintf("===============================================================\n\n"
      );

  // system call arguments are accessed by esp of the user stack in the trap frame
  uint arg0 = *(uint *)(myproc()->tf->esp + 0);
  uint arg1 = *(uint *)(myproc()->tf->esp + 16);
  uint arg2 = *(uint *)(myproc()->tf->esp + 32);
  uint arg3 = *(uint *)(myproc()->tf->esp + 64);
  cprintf("input parameters===============================================\n");
  cprintf("arg0: 0x%x   arg1: 0x%x    arg2: 0x%x    arg3: 0x%x\n",
      arg0, arg1, arg2, arg3);
  cprintf("===============================================================\n\n"
      );

  return 0;
}


int
sys_getprocs(void)
{
  struct uproc *temp = 0;
  return getprocs(64, temp);
}


int
sys_clone(void)
{
  int func, arg, stack;

  if(argint(0, &func) < 0)
    return -1;
  if(argint(1, &arg) < 0)
    return -1;
  if(argint(2, &stack) < 0)
    return -1;

  return clone((void *)func, (void *)arg, (void *)stack);
}


int
sys_join(void)
{
  int pid, stack, retVal;

  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &stack) < 0)
    return -1;
  if(argint(2, &retVal) < 0)
    return -1;

  join(pid, (void **)stack, (void **)retVal);
  return 0;
}


int
sys_texit(void)
{
  int retVal;
  if(argint(0, &retVal) < 0)
    return -1;

  texit((void *)retVal);
  return 0;
}


int
sys_mutex_init(void)
{
  return mutex_init();
}


int
sys_mutex_destroy(void)
{
  int mutex;
  if(argint(0, &mutex) < 0)
    return -1;
  if(mutex < 0 || mutex > 31)
    return -2;
  return mutex_destroy(mutex);
}


int
sys_mutex_lock(void)
{
  int mutex_id;
  if(argint(0, &mutex_id) < 0)
    return -1;
  if(mutex_id < 0 || mutex_id > 31)
    return -2;
  if(myproc()->mtableShared[mutex_id].isFree)
    return -3;

  mutex_lock(mutex_id);
  return 0;
}


int
sys_mutex_unlock(void)
{
  int mutex_id;
  if(argint(0, &mutex_id) < 0)
    return -1;
  if(mutex_id < 0 || mutex_id > 31)
    return -2;
  if(myproc()->mtableShared[mutex_id].isFree)
    return -3;

  mutex_unlock(mutex_id);
  return 0;
}
