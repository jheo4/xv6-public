#ifndef POSIX_THREAD
#define POSIX_THREAD

#define NULL 0
#define PGSIZE (4096)

typedef struct{
  int pid;
} pthread_t;

typedef struct{
  int id;
} pthread_mutex_t;;

int pthread_create(pthread_t *thread, void* (*func) (void*), void *arg);
int pthread_join(pthread_t thread, void **retVal);
int pthread_exit(void *retVal);

int pthread_mutex_init(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutext);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

#endif
