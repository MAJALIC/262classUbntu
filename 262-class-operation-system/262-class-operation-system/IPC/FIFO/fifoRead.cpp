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

}
