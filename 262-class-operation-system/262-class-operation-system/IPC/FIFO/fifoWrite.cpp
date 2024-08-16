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
    const char *fileName = "./commonfifo";

    int ret = access(fileName, F_OK);
    if(ret == -1)
    {
     perror("mkfifo error:");
        exit(-1);
    }
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
            sleep(1);
        }

}