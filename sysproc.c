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
sys_trace(void)
{
  int on;

  // Fetch the integer argument passed by the user
  if(argint(0, &on) < 0)
    return -1;

  // Enable or disable tracing
  myproc()->trace_on = on;

  return 0;
}

int
sys_vmmap(void)
{
  int va;
  uint pa, flags;
  struct proc *p = myproc();

  if(argint(0, &va) < 0 || va < 0)
    return -1;

  if((uint)va >= p->sz)
    return -1;

  if(vmmapinfo(p->pgdir, (uint)va, &pa, &flags) < 0)
    return -1;

  cprintf("VA=0x%x Page=0x%x PA=0x%x\n",
          (uint)va, PGROUNDDOWN((uint)va), pa);

  cprintf("P=%d W=%d U=%d\n",
          !!(flags & PTE_P),
          !!(flags & PTE_W),
          !!(flags & PTE_U));

  return 0;
}

