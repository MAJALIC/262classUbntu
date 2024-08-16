#include <iostream>
#include  <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t g_sem; //信号量

void printer(char *str)
{
    if(str == NULL)
    {
        return;
    }
    
    sem_wait(&g_sem);//减一
    while (*str !='\0')
    {
       cout<<*str;
        fflush(stdout);

        str++;
        sleep(1);
    }
    printf("\n");
    sem_post(&g_sem);//加一
}

void *thread_fun1(void *arg)
{
    char *str1 = "hello";
    printer(str1);
}

void *thread_fun2(void *arg)
{
    char *str2 = "world";
    printer(str2);
}

int main(void)
{
    pthread_t tid1, tid2;

    sem_init(&g_sem, 0, 1); //初始化信号量，初始值为 1

    //创建 2 个线程
    int ret = pthread_create(&tid1, NULL, thread_fun1, NULL);
      if (ret != 0)
  {
    perror("thread create error");
    exit(-1);
  }
    pthread_create(&tid2, NULL, thread_fun2, NULL);

    //等待线程结束，回收其资源
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
int cnt = 100;
while(cnt--)
{
    sleep(1);
}

    sem_destroy(&g_sem); //销毁信号量

    return 0;
}