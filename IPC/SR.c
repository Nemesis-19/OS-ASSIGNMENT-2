#include<stdio.h>
#include<signal.h>
#include<inttypes.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
#include<fcntl.h>
#include<stdbool.h>

void alrm_handler(int j, siginfo_t *m, void *o)
{
    sleep(1);

    unsigned char n;

    uint64_t i;

    asm volatile ("rdrand %0; setc %1":"=r"(i), "=qm"(n));

    int r=(int)n;

    if(r==0)
    {
        printf("Randomizing failed for SR\n");

        return;
    }

    printf("Random number from SR: %llu\n", i);

    union sigval v;

    v.sival_ptr=(void(*)(int))i;

    if(sigqueue(m->si_value.sival_int, 15, v)!=0)
    {
        printf("sigqueue failed for SR\n");

        return;
    }
}

int main(int argc, char* argv[])
{
    int pid_sr=atoi(argv[0]);

    struct sigaction action_alrm;
    sigemptyset(&action_alrm.sa_mask);
    action_alrm.sa_flags=SA_SIGINFO;
    action_alrm.sa_sigaction=&alrm_handler;

    union sigval value;

    value.sival_int=pid_sr;

    while(true)
    {
        if(sigaction(SIGALRM, &action_alrm, 0)==-1)
        {
            perror("sigaction failed for SR\n");

            return 6;
        }

        sigqueue(getpid(), SIGALRM, value);
    }

    return 2;
}