#include <iostream>

using namespace std;
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
void painter(const char *str)
{
    if (str == NULL)
    {
        return;
    }
    while (*str != '\0')
    {
        cout << *str;
        fflush(stdout);
        sleep(1);
        // 指针移动
        str++;
    }
    cout<<endl;
    return;
}

void *thread_func1(void *arg)
{
    const char *str1 = "hello";
    pthread_mutex_lock(&mutex);
    painter(str1);
    // 解锁
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}
void *thread_func2(void *arg)
{
    const char *str2 = "world";
    pthread_mutex_lock(&mutex);
    painter(str2);
    // 解锁
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    // 创建线程1
    pthread_t threadId1;
    int ret = pthread_create(&threadId1, NULL, thread_func1, NULL);

    if (ret != 0)
    {
        perror("create error:");
        _exit(-1);
    }
    pthread_t threadId2;
    ret = pthread_create(&threadId2, NULL, thread_func2, NULL);

    if (ret != 0)
    {
        perror("create error:");
        _exit(-1);
    }
    pthread_join(threadId1, NULL);
    pthread_join(threadId2, NULL);

//释放🔓资源
pthread_mutex_destroy(&mutex);

    return 0;
}