#include<stdio.h>
#include<signal.h>
#include<inttypes.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdint.h>
#include<immintrin.h>
#include<sys/time.h>
#include<fcntl.h>
#include<stdbool.h>

void handler(int n, siginfo_t *m, void *o)
{
    uint64_t* ptr=m->si_value.sival_ptr;

    printf("Random number from main: %llu\n", ptr);
}

int main()
{
    int pid=fork();

    if(pid==0)
    {
        struct sigaction action = {0};
        sigemptyset(&action.sa_mask);
        action.sa_sigaction=&handler;
        action.sa_flags=SA_SIGINFO;

        while(true)
        {
            int c=sigaction(SIGTERM, &action, 0);

            if(c==-1)
            {
                perror("sigaction failed for main\n");

                return 1;
            }

            sleep(1);
        }
    }
    else
    {
        char arr[10];
        sprintf(arr, "%d", pid);

        int sr=fork();

        if(sr==0)
        {
            execlp("./SR", arr, "NULL");
        }
        else
        {
            sleep(1);

            int st=fork();

            if(st==0)
            {
                execlp("./ST", arr, "NULL");
            }
        }
    }

    return 0;
}