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
#include <signal.h>

void handleSignal(int sig)
{
    cout<<"1"<<endl;
}

int main()
{
   pid_t pid = fork();
   if(pid> 0)
   {
    sleep(5);
     kill (pid, SIGKILL);
   }
   else if(pid == 0)
   {
       while(1)
       {
        printf("i am child process\n");
        sleep(1);
       }
   }
else if (pid < 0)
{
    struct sigaction newAction;
    memset(&newAction, 0, sizeof(newAction));
    newAction.sa_flags = 0;
    newAction.sa_handler = handleSignal;
   sigemptyset(&newAction.sa_mask);

}
   
    return 0;
}
