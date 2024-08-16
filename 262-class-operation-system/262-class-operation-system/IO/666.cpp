#include <iostream>
#include <string>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;
#define BUFFER_SIZE 16

//将信息写入文件
void writeFile(string & content)
{
    //打开文件
    const char * filename = "./test.txt";
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
        if (fd == -1)
        {
            perror("openerro:");
        }
//重定向文件指定位置
lseek(fd, 0, SEEK_END);

size_t writrBytes = write(fd, (const void *)content.c_str(), content.size());
 //关闭文件描述符
close(fd);
}


 int main()
 {
    string content;

    while(1)
    {
        cout << "输入文件内容:(出入break结束)";
        cin >> content;

        if (content == "break")
        {
            break;
        }
            writeFile(content);
    }

    return 0;
 }
