#ifndef THREAD_HPP
#define THREAD_HPP

#include<pthread.h>
#include<sys/time.h>

static void* ThreadFunction(void* Object);

class Thread{
  public:
    friend void* ThreadFunction(void* Object);
    
    //initializes the thread variables
    Thread()
    :Started(false), Detached(false)
    { }

    //forcefully stop the thread if it is still executing
    virtual ~Thread()
    {
      Stop();
    }
    
    //
    int Start(void* param)
    {
      if(!Started){
        pthread_attr_t attributes;
        pthread_attr_init(&attributes);
        if(Detached)
          pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED);
        Param = param;
        ThreadID = 0;
        if(pthread_create(&ThreadHandle, &attributes, ThreadFunction, this)==0)
          Started = true;
        pthread_attr_destroy(&attributes);
      }
      return Started;
    }


    void Detach()
    {
      if(Started && !Detached)
        pthread_detach(ThreadHandle);
      Detached = true;
    }
    
    //the wait function automatically detaches the thread
    void* Wait()
    {
      void* status = NULL;
      if(Started && !Detached){
        pthread_join(ThreadHandle, &status);
        Detached = true;
      }
      return status;
    }

    //the stop function abruptly terminates the thread.
    void Stop()
    {
      if(Started && !Detached){
        pthread_cancel(ThreadHandle);
        pthread_detach(ThreadHandle);
        Detached = true;
      }
    }
    
    //POSIX does not have a compliant interface for this...
    //so for the time being, just returning the NULL
    unsigned int GetThreadID()
    {
      return ThreadID;
    }

    static unsigned int GetCurrentThreadID()
    {
      return 0;
    }
    
    //implemented by causing the select function to timeout
    //after a specified period of time
    static void Sleep(int delay)
    {
      timeval timeout = {(delay/1000), ((delay*1000)%1000000)};
      select(0, (fd_set*)NULL, (fd_set*)NULL,(fd_set*)NULL, &timeout);
    }

  protected:
    //The run function received the void* pointer passed to the Start() function
    //This pointer may be used to individualize the function actions of different threads.
    virtual void* Run(void*)
    { return NULL; }
  private:
    pthread_t ThreadHandle;
    unsigned int ThreadID;
    bool Started;
    bool Detached;
    void* Param;
};

static void* ThreadFunction(void* Object)
{
  Thread* t = (Thread*) Object;
  return t->Run(t->Param);
}

#endif //THREAD_HPP
