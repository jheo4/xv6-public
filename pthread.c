#include "pthread.h"
#include "user.h"

#define NULL 0
#define PGSIZE (4096)

int pthread_create(pthread_t *thread, void* (*func) (void *), void *arg){

  void *stack = malloc(PGSIZE);

  if((unsigned int)stack <= 0){
    printf(1, "fail to alloc new stack\n");
    return -1;
  }

  thread->pid = clone(func, arg, stack);
  return 0;
}


int pthread_join(pthread_t thread, void **retVal){
  void *stack;
  join(thread.pid, &stack, retVal);

  if(*retVal < 0){
    if(stack) free(stack);
    return -1;
  }

  free(stack);

  return 0;
}

int pthread_exit(void *retVal){
  texit(retVal);
  return 0;
}

int pthread_mutex_init(pthread_mutex_t *mutex){
  int id = mutex_init();
  mutex->id = id;
  return id;
}

int pthread_mutex_lock(pthread_mutex_t *mutex){
  mutex_lock(mutex->id);
  return 0;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex){
  mutex_unlock(mutex->id);
  return 0;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex){
  return mutex_destroy(mutex->id);
}
