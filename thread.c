#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "mmu.h"
#include "thread.h"
#define PGSIZE 4096


int
lock_init(struct lock_t *lk)
{
  lk->flag = 0;
  return 0;
}

void
lock_acquire(struct lock_t *lk)
{
  while(xchg(&lk->flag,1) !=0);
}

void
lock_release(struct lock_t *lk)
{
  xchg(&lk->flag,0);
}

int
thread_create(void* (*start_routine)(void*), void *arg)
{
  int tid;
  void* stack;

  stack = malloc(PGSIZE * 2);

  if((uint)stack % PGSIZE != 0){
    stack += PGSIZE - ((uint)stack % PGSIZE);
  }

  tid = clone(stack,PGSIZE);
  if(tid == 0){
    (*start_routine)(arg);
    exit();
  }
  return tid;
}

