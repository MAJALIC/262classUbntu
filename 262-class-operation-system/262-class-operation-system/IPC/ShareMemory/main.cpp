#include <iostream>

using namespace std;

#include <unistd.h>
#include <sys/mman.h>

#include <string>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstring>
#define BUFFER_SIZE 16

int main()
{
    const char* filename = "./text.txt";

    int fd = open(filename, O_RDWR);
    if(fd == -1)
    {
        perror("open error");
        exit(-1);

    }
    //获取文件大小
    int length = lseek(fd, 0, SEEK_END);
    printf("length = %d\n", length);

    void * addr =  mmap(NULL, length, PROT_READ | PROT_WRITE,MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED)
    {
        perror("mmap error");
        exit(-1);
    }

    close(fd);

    pid_t pid = fork();
    if (pid > 0)
    {
        cout << "this is parent"<<endl;
        // 父进程写
        const char * str = "hello world";

        //字符串拷贝
        strncpy((char * )addr, str, strlen(str)+1);
     

    }
    else if (pid == 0)
    { 
        cout << "this is child"<<endl;
        usleep(1000);
        char buffer[BUFFER_SIZE]= {0};
        //地质拷贝
        memcpy(buffer, addr, sizeof(buffer));
        //紫荆城负责读
        printf("addr = %s\n", (char *)buffer);
      
    }
else{
    perror("fork error");
    exit(-1);
}
 //结束映射
 munmap(addr, length);

 return 0;

}
