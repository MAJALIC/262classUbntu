#include <iostream>
#include <string>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;
int main()
{
    //文件信息
    const char* filename = "./Append.cpp";
struct stat fileInfo;
//获取文件信息
stat(filename, &fileInfo);

cout << "size:"<< fileInfo.st_size<< endl;

if(S_ISREG(fileInfo.st_mode))
{
    cout << "regular file" << endl;     
}
    return 0;

}