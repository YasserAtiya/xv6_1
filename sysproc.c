#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
//#include "uproc.h"
#include "proc.h"
//#include "stat.h"
//#include "fs.h"


int
sys_getprocs(void)    //Returns number of processes
{
  //This is the ptr to our userspace
  struct uproc *tempproc;

  int max;
  int numproc;

  //uses argint
  if(argint(0, &max) < 0)//the amount of uprocs allocated
    return -1; //Attaches top of stack to pid
  
  //the address of the uproc in the user space
  if(argptr(1, (void*)&tempproc, max*sizeof(struct uproc)) < 0)
    return -1;

  numproc = FetchProc(tempproc, max);//populate array element, fetch number of processes
    

  //return number of processes
  return numproc;
}

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

