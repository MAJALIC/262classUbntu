#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
using namespace std;
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>

#define SERVER_PORT 8080

void *handleClientInfo(void *arg)
{
//分离
pthread_detach(pthread_self());

    char buffer[1024] = {0};
int connfd = *(int *)arg;

    while (1)
    {
        int readBytes = read(connfd, buffer, sizeof(buffer));
        if (readBytes < 0)
        {
            cout << "readBytes <0" << endl;
            break;
        }
        else if (readBytes == 0)
        {
            cout << "readBytes ==0" << endl;
            break;
        }
        else
        {
            cout << "buffer:" << buffer << endl;

            for (int idx = 0; idx < readBytes; idx++)
            {
                buffer[idx] = toupper(buffer[idx]);
            }
        }
        write(connfd, buffer, readBytes);
    }
    close(connfd);

   pthread_exit(NULL);
}

int main()
{
    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket error");
        _exit(-1);
    }

    // 设置端口复用
    int optVal = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal));

    // 绑定IP和端口
    struct sockaddr_in localADDress;
    memset(&localADDress, 0, sizeof(localADDress));

    // 设置端口族
    localADDress.sin_family = AF_INET;
    localADDress.sin_port = htons(SERVER_PORT);
    localADDress.sin_addr.s_addr = INADDR_ANY; // 全通，不管谁都可以连接

    // 绑定
    int ret = bind(sockfd, reinterpret_cast<const sockaddr *>(&localADDress), sizeof(localADDress));
    if (ret != 0)
    {
        perror("create error:");
        _exit(-1);
    }

    // 监听的套接字设置监听
    ret = listen(sockfd, 10);
    if (ret != 0)
    {
        perror("create error:");
        _exit(-1);
    }

    int connfd = 0;


    while (1)
    {
        connfd = accept(sockfd, NULL, NULL);
        if (connfd == -1)
        {
            perror("accept error");
            _exit(-1);
        }
        // 程序到达这个地方就要新线程来接

        // 创建性的线程
        pthread_t tid = 0;
        ret = pthread_create(&tid, NULL, handleClientInfo, (void *)&connfd);
        if (ret != 0)

        {
            perror("pthread create error");
            _exit(-1);
        }
      
      //保证线程一定创建成功，一定接收到当前文件
      sleep(1);
    }


    // 释放资源
    close(connfd);

    // 关闭文件描述符
    close(sockfd);
    cout << "helloworld" << endl;
    return 0;
}