#include <iostream>

using namespace std;
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void *handleThread (void * arg)
{
  int num =1;
  
   while(1)
   {
    printf("num=%d", num);
    num+=2;
    sleep(2);
   }

}

void *handleThread2 (void * arg)
{
  int num =0;
  
   while(1)
   {
    printf("num=%d", num);
    num+=2;
    sleep(2);
   }

}


int main()
{

/*     pthread_t threadId = pthread_self();
  cout << "thread id :"<< threadId <<endl;

    pid_t pidId = getpid();
  cout << "pid id :"<< pidId<< endl; */

   //创建线程
   pthread_t threadId;
   auto ret = (&threadId, NULL, handleThread, NULL);
  if (ret != 0)
  {
    perror("thread create error");
    exit(-1);
  }

     pthread_t threadId2;
   ret = pthread_create(&threadId2, NULL, handleThread2, NULL);
  if (ret != 0)
  {
    perror("thread create error");
    exit(-1);
  }
   
   while(1)
   {
    printf("i am main process");
    sleep(1);
   }


    return 0;
}