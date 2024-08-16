#include <iostream>

using namespace std;
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
// 读写🔓
pthread_rwlock_t g_rwlock;
int g_num = 100;
void *threadFunc1(void *arg)
{

    pthread_rwlock_rdlock(&g_rwlock);

    for (int idx = 0; idx < 10; idx++)
    {
        cout << "threadfunc1:" << g_num << endl;
        usleep(1000);
    }

    // 解锁
    pthread_rwlock_unlock(&g_rwlock);

    // 线程退出
    pthread_exit(NULL);
}

void *threadFunc2(void *arg)
{

    pthread_rwlock_rdlock(&g_rwlock);

    for (int idx = 0; idx < 10; idx++)
    {
        cout << "threadfunc1:" << g_num << endl;
        usleep(1000);
    }

    // 解锁
    pthread_rwlock_unlock(&g_rwlock);

    // 线程退出
    pthread_exit(NULL);
}

//写🔓
void *threadFunc3(void *arg)
{

    pthread_rwlock_wrlock(&g_rwlock);

    for (int idx = 0; idx < 10; idx++)
    {
        cout << "threadfunc1:" << g_num << endl;
        usleep(1000);
    }

    // 解锁
    pthread_rwlock_unlock(&g_rwlock);

    // 线程退出
    pthread_exit(NULL);
}




int main()
{
    pthread_rwlock_init(&g_rwlock, NULL);
    // 创建线程1
    pthread_t threadId1;
    int ret = pthread_create(&threadId1, NULL, threadFunc1, NULL);

    if (ret != 0)
    {
        perror("create error:");
        _exit(-1);
    }
    pthread_t threadId2;
    ret = pthread_create(&threadId2, NULL, threadFunc2, NULL);

    if (ret != 0)
    {
        perror("create error:");
        _exit(-1);
    }

    pthread_join(threadId1, NULL);
    pthread_join(threadId2, NULL);

    // 释放🔓资源

    return 0;
}