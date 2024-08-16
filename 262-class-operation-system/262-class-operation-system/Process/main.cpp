#include <iostream>

using namespace std;

#include <unistd.h>

int main()
{
    pid_t pid = getpid();
    cout<<"pid:"<< pid<<endl;

    /*获取当前调用的进程的父进程ID号*/

   pid_t ppid = getppid();
   cout<<"ppid:"<< ppid<<endl;

    while(1)
    {
        
        /*休眠一秒*/
        sleep(1);

    }
    return 0;
}


