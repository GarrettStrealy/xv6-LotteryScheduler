#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "pstat.h"

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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

/* The following code is added by Garrett Strealy, GJS160430.
** set number of tickets for a process (lottery scheduler)
*/ 
int sys_settickets(void)
{
  int numberOfTickets;
  argint(0, &numberOfTickets);
  if (numberOfTickets < 1){
    return -1;
  }

  proc->tickets = numberOfTickets;
  return 0;
}
/* End of code added */

/* The following code is added by Garrett Strealy, GJS160430.
** get process info
*/ 
int
sys_getpinfo(void)
{
  struct pstat* ps;
  char *p;

  if (argptr(0, &p, sizeof(struct pstat)) < 0){
    return -1;
  }

  ps = (struct pstat *)p;
  if (ps == NULL){
    return -1;
  }

  return getpinfo(ps);
}
/* End of code added */
