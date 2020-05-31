struct lock_t{
  uint flag;
};

int thread_create(void *(*start_routine)(void*), void *arg);
int lock_init(struct lock_t *lk);
void lock_acquire(struct lock_t *lk);
void lock_release(struct lock_t *lk);
