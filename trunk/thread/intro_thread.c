#include <pthread.h>
#include <stdio.h>


void *PrintHello(void *threadid)
{
     long tid;
     tid = (long)threadid;
     printf("Hello World! It's me, thread #%ld!\n", tid);
     pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
  //argv[0] = prog_name
  //argv[1] = 2nd arg
  //argv[2] = third arg

  const int nThread = 5;
  /*
  if(argc<2) {
    printf("Usage: Number of threads\n");
    return -1;
  }
  else {
    nThread = (int)argv[1];
  }
*/
     pthread_t threads[nThread];
     int rc;
     long t;
     for(t=0; t<nThread; t++){
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (rc){
           printf("ERROR; return code from pthread_create() is %d\n", rc);
           return -1;
        }
    }
  pthread_exit(NULL);
}
 
