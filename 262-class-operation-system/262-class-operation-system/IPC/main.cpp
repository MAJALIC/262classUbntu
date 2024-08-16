#include <iostream>

using namespace std;

#include <unistd.h>

#include <string>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstring>
//ni ba


#define BUFFER_SIZE 32

int main()
{
    /*创建管道*/
    int pipefd[2];
    memset(pipefd, 0, sizeof(pipefd));
    /*创建子进程*/
    pid_t pid = fork();
    if (pid > 0)
    {
        // 关闭父进程读端
        close(pipefd[0]);

        int num = 666;
        cout << "i am parent process!" << endl;
        string res = "hello world!";
        //         父进程、负责写
        write(pipefd[1], res.c_str(), res.size());

        // 回收紫金城资源
        wait(NULL);
    }
    else if (pid == 0)
    {
        sleep(1);
        
        cout << "i am child process!" << endl;

        // 得到文件描述符的状态标记
        int flags = fcntl(pipefd[0], F_GETFL);
        cout << flags << endl;

        // 设置文件描述符为非阻塞
        fcntl(pipefd[0], F_SETFL, flags | O_NONBLOCK);

        // 子进程·负责读
        char buffer[BUFFER_SIZE] = {0};
        read(pipefd[0], buffer, sizeof(buffer));

        printf("hello world!\n");
        printf("buffer = %s\n", buffer);
    }
    else if (pid < 0)
    {
    }

    return 0;
}