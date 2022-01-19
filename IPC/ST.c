#include<stdio.h>
#include<signal.h>
#include<inttypes.h>
#include<unistd.h>
#include<stdlib.h>
#include<immintrin.h>
#include<sys/time.h>
#include<fcntl.h>
#include<stdbool.h>
#include<time.h>

void alrm_handler(int j, siginfo_t *m, void *o)
{
    sleep(1);

    uint64_t a;
    a=__rdtsc();

    long long int b=a/CLOCKS_PER_SEC;

    int year=b/60/60/24/365;
    int month=b/60/60/24/30;
    int day=b/(24*3600);
    b=b%(24*3600);
    int hour=b/3600;
    b%=3600;
    int minutes=b/60;
    b%=60;
    int seconds=b;

    time_t x = time(0);
    struct tm y = *localtime(&x);

    printf("No.of ticks: %llu Secs generated: %lld Time Now: %d-%d-%d %d:%d:%d\n", a, b, y.tm_year + 1900, y.tm_mon + 3, y.tm_mday, y.tm_hour+9, y.tm_min+25, y.tm_sec);

    unsigned h, l;

    __asm__ __volatile__ ("rdtsc":"=a"(l), "=d"(h));

    uint64_t i=((unsigned long long)l|((unsigned long long)h)<<32);

    printf("Random number from ST: %llu\n", i);

    union sigval v_st;

    v_st.sival_ptr=(void(*)(int))i;

    if(sigqueue(m->si_value.sival_int, 15, v_st)!=0)
    {
        printf("sigqueue failed for ST\n");

        return;
    }

    kill(m->si_value.sival_int, 15);
}

int main(int argc, char* argv[])
{
    int pid_st=atoi(argv[0]);

    struct sigaction action_alrm;
    sigemptyset(&action_alrm.sa_mask);
    action_alrm.sa_flags=SA_SIGINFO;
    action_alrm.sa_sigaction=&alrm_handler;

    union sigval value;

    value.sival_int = pid_st;

    struct itimerval t;
    t.it_value.tv_sec=1;
    t.it_value.tv_usec=1000000;
    t.it_interval=t.it_value;
    setitimer(ITIMER_REAL, &t, NULL);

    while(true)
    {
        if(sigaction(SIGALRM, &action_alrm, 0)==-1)
        {
            perror("sigaction failed for SR\n");

            return 6;
        }

        sigqueue(getpid(), SIGALRM, value);
    }

    return 3;
}