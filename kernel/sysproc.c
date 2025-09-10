#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

// The number of calls made to getpid.
int getpid_count = 0;
// The number of systems calls made.
int syscalls_count = 0;
// The number of successful system calls made.
int succ_syscalls_count = 0;

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
  getpid_count++;
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

// Get the total number of getpid calls.
int sys_firstpart(void) {
  return getpid_count;
}
// Get the total number of system calls made.
int sys_secondpart(void) {
  return syscalls_count;
}
// Get the total number of successful system calls made.
int sys_thirdpart(void) {
  return succ_syscalls_count;
}
// Instructs QEMU to shutdown.
int sys_shutdown(void) {
  outw(0x604, 0x2000);
  return 0;
}
