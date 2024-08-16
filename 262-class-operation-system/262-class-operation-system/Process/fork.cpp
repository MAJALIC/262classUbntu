#include <iostream>

using namespace std;

#include <unistd.h>

#include <string>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <cstring>


static int writeFile(const char * filename, const void * buf, size_t size)
{
  int fd = open (filename,O_RDWR | O_CREAT, 0644);
if (fd ==-1)
{
    perror("open error");
    return -1;
}
int writefile = write(fd, buf, size );
close(fd);

return writefile;

}

static int readFile(const char * filename, void * buf, size_t size)
{
 int fd = open (filename,O_RDWR );
if (fd ==-1)
{
    perror("open error");
    return -1;
}

int readBytes = read(fd, buf,size);
     
     close(fd);

return readBytes;
}

int main()
{
    int num =100;
    
   
    pid_t pid = fork();
    if(pid > 0)
    {
        num += 666;
        printf("parent process - num : %d\n",num);
        //父进程的程序
    
        printf("parent process child pid = %d,pid = %d\n",pid,getpid());
        writeFile("./test.txt",&num, sizeof(num));
    }
    else if (pid== 0)
    {
       int buffer = 0;
        sleep(2);
  readFile("./test.txt", &buffer, sizeof(buffer));

        printf("child process - num : %d\n",buffer);

        //子进程代码
      
        printf("child process pid = %d,ppid = %d\n",getpid(), getppid() );
    }
    else if(pid< 0)
    {
        perror("fork error:");
        exit(-1);
    }

 printf("hello world!");
while (1)
{
    sleep(1);

}

    return 0;
}
