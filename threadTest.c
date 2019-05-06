#include "types.h"
#include "user.h"
#include "pthread.h"
#include "x86.h"

#define NULL 0
#define THREADS 16

static volatile int counter = 0;

void* myThread(void *arg)
{
	int i;
  sleep(10);

	for (i = 0; i < 1000000; i++){
		counter = counter + 1;
	}

	pthread_exit(arg);
	return NULL;
}


int main()
{
  int i, r;
  void *retVal;

  pthread_t threads[THREADS];
  int *args[THREADS];

  for(i = 0; i < THREADS; i++){
    args[i] = (int *)malloc(sizeof(int));

    if(!args[i]){
      printf(1, "args alloc error(%d) \n", i);
      exit();
    }
    *args[i] = i;
  }

  printf(1, "main with %d threads\n", THREADS);

  printf(1, " start to create threads\n");
  for(i = 0; i < THREADS; i++)
    pthread_create(&threads[i], myThread, args[i]);
  printf(1, " end creating threads\n");

  printf(1, " join threads\n");
  for(i = 0; i < THREADS; i++){
    r = pthread_join(threads[i], &retVal);
    if(r < 0 || *(int*)retVal != i)
      printf(1, "   Join Failed\n");
  }
  printf(1, " all threads are joined\n");

  for(i = 0; i < THREADS; i++)
    free(args[i]);

  printf(1, "Final Value : %d\n", counter);
  exit();
}
