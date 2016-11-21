#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

int signalNum;
float tout;
int sibling;

void timerAlarm(int _, siginfo_t * info,void * context)
{
    printf("I'm %d, my sibling is %d", getpid(), sibling);
    if(signalNum == SIGSTOP)
        printf(" and my signal is SIGSTOP\n");
    else if(signalNum == SIGTSTP)
        printf(" and my signal is SIGTSTP\n");
    else if(signalNum == SIGTTIN)
        printf(" and my signal is SIGTTIN\n");
    else if(signalNum == SIGTTOU)
        printf(" and my signal is SIGTTOU\n");
}

void sendSignals(int _, siginfo_t * info,void * context)
{
    printf("I'm %d and i've sent a signal to %d\n", getpid(),sibling);
    kill(sibling,signalNum);
    struct timespec ts = {tolower(tout),(int)((tout-tolower(tout))*1000000000)};
    nanosleep(&ts,NULL);
    kill(sibling,SIGCONT);
}

int main(int argc, char **argv)
{
    struct sigaction sa;
    sa.sa_sigaction = timerAlarm;
    sa.sa_flags = SA_SIGINFO;
    sigaction (SIGALRM, &sa, NULL);
    sa.sa_sigaction = sendSignals;
    sa.sa_flags = SA_SIGINFO;
    sigaction (SIGCONT, &sa, NULL);

    int c;
    if(argc < 4)
    {
        printf("Too few arguments...\n");
        exit(1);
    }
    while (1)
    {
        int option_index = 0;
        static struct option long_options[] = {
        {"kill",     required_argument, 0,  'k' },
        {"tout",  required_argument,       0,  't' },
        {"sibling",  required_argument, 0,  's' },
        {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "k:t:s:",
        long_options, &option_index);
        if (c == -1)
        break;

        switch (c) {
        case 'k':
            if(!strcmp(optarg,"STOP"))
                signalNum = SIGSTOP;
            else if(!strcmp(optarg,"TSTP"))
                signalNum = SIGTSTP;
            else if(!strcmp(optarg,"TTIN"))
                signalNum = SIGTTIN;
            else if(!strcmp(optarg,"TTOU"))
                signalNum = SIGTTOU;
            break;
        case 't':
            tout = strtof(optarg,NULL);
            break;
        case 's':
            sibling = atoi(optarg);
            break;
        }
    }
    struct itimerval it_val;
    it_val.it_value.tv_sec = tolower(tout);
    it_val.it_value.tv_usec = (int)((tout-tolower(tout))*1000000);
    it_val.it_interval = it_val.it_value;

    setitimer(ITIMER_REAL, &it_val, NULL);
    while(1)
        pause();
}
