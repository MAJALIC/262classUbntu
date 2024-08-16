#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 10

int main()
{
    // 创建命令管道
    const char *fileName = "./fileInfo";
    int ret = mkfifo(fileName, 0644);
    if (ret != 0)
    {
        if (errno != EEXIST)
            perror("mkfifo error:");
        exit(-1);
    }

    // 创建进程
    pid_t pid = fork();
    if (pid > 0)
    {
        cout << "this is parent"<<endl;
        // 父进程写
        int fd = open(fileName, O_RDWR);
        if (fd == -1)
        {
            perror("open error");

            _exit(-1);
        }
        const char *buf = "helloworld";
        int writeBytes = 0;
        int cin = 3;
        // FIFO写三次
        while (cin--)
        {
            writeBytes = write(fd, buf, strlen(buf));
            if (writeBytes > 0)
            {
                cout << "writeBytes=" << writeBytes << endl;
            }
            else if (writeBytes == 0)
            {
                cout << "writeBytes == 0" << endl;
            }
            else if (writeBytes < 0)
            {
                perror("write error");
            }
            //sleep(1);
        }

        // 回收紫禁城资源
        wait(NULL);
        // 关闭文件描述符
        close(fd);
    }
    else if (pid == 0)
    { 
          cout << "this is child"<<endl;
        // 紫禁城向有名管道读数据
        sleep(3);
        int fd = open(fileName, O_RDONLY);
        if (fd == -1)
        {
            perror("open error");

            _exit(-1);
        }
        char buffer[BUFFER_SIZE] = {0};

        int readBytes = 0;
        while (1)
        {
            readBytes = read(fd, buffer, sizeof(buffer));
            if (readBytes > 0)
            {
                printf("readBytes = %d\t buffer = %s\n", readBytes, buffer);
            }
            else if (readBytes == 0)
            {
                cout << "read == 0" << endl;
             
            }
            else if (readBytes < 0)
            {
                if(errno == EAGAIN)
                {
                    cout<<"..."<< endl;
                }
                else
                {
                    perror("read error:");
                    close(fd);
                    _exit(-1);
                }
  
            }
            sleep(1);
            //清除赞数据
            memset(buffer, 0, sizeof(buffer));
        }
        close(fd);

        _exit(0);
    }
    else if (pid < 0)
    {
        cout<< "no process"<< endl;
    }
}