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
//  lock_t lk;
  int tid;
  void* stack;

//  lock_init(&lk);
//  lock_acquire(&lk);
  stack = malloc(PGSIZE * 2);
//  lock_release(&lk);

  if((uint)stack % PGSIZE != 0){
    stack += PGSIZE - ((uint)stack % PGSIZE);
  }

  tid = clone(stack,PGSIZE);
  //printf(1,"tid = %d\n",tid);
  if(tid == 0){
    (*start_routine)(arg);
    exit();
  }
  return tid;
}

