#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <cctype>
#include <arpa/inet.h>

#define UDP_SERVER_PORT 999

int main()
{
    // 创建套接子
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("socket error:");
        _exit(-1);
    }

    // 连接服务器的IP和端口
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(UDP_SERVER_PORT);
    const char *ip = "192.168.183.129";
    inet_pton(AF_INET, ip, &(serverAddr.sin_addr.s_addr));

    char buffer[128] = {"hello world"};
    int writeBytes = sendto(sockfd, buffer, sizeof(buffer), 0, reinterpret_cast<const sockaddr *>(&serverAddr), sizeof(serverAddr));

    cout << "writeBytes:" << writeBytes << endl;
    sleep(1);

    return 0;
}