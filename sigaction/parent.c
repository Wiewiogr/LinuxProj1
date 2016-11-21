#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

struct Child
{
    bool isAlive;
    int pid;
};
struct Child* children;
int numOfChildren;

void childSignal(int _, siginfo_t * info,void * context)
{
    int code = info->si_code;
    int pid = info->si_pid;
    if(code == CLD_KILLED)
    {
        printf("Child with pid : %d killed\n",pid);
        int i = 0;
        for(i = 0; i < numOfChildren;i++)
            if(children[i].pid == pid)
            {
                children[i].isAlive = false;
                break;
            }
        for(; i < numOfChildren;i++)
        {
            kill(children[i].pid,SIGKILL);
        }
    }
    else if(code == CLD_EXITED)
    {
        printf("Child with pid : %d exited\n",pid);
    }
    else if(code == CLD_STOPPED)
    {
        printf("Child with pid : %d stopped\n",pid);
    }
    else if(code == CLD_CONTINUED)
    {
        printf("Child with pid : %d continued\n",pid);
    }
}


int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        printf("Too few arguments...\n");
        exit(1);
    }
    struct sigaction sa;
    sa.sa_sigaction = childSignal;
    sa.sa_flags = SA_SIGINFO;
    sigaction (SIGCHLD, &sa, NULL);
    numOfChildren = argc -1;
    children = malloc((numOfChildren)*sizeof(struct Child));

    for(int i = 0u ; i < numOfChildren ;i++)
    {
        int id;
        if((id = fork()) == 0)
        {
            char* signal = NULL;
            printf("arg : %s\n", argv[i+1]);
            float time = strtof(argv[i+1], &signal);
            printf("Value : %lf, rest : %s \n", time, signal);
            char killArg[20];
            char toutArg[20];
            char siblingArg[20];
            sprintf(killArg,"--kill=%s",signal);
            sprintf(toutArg,"--tout=%lf",time);
            int pid;
            if(i == 1)
                pid = getpid();
            else
                pid = children[i-1].pid;
            sprintf(siblingArg,"--sibling=%d",getpid());
            char * newArgs[] =
            {
                "child.o",
                killArg,
                toutArg,
                siblingArg,
                (char *) 0
            };
            if(execvp("./child.o",newArgs)==-1)
            {
                printf("Zjebło się ;c\n");
            }
            break;
        }
        else
        {
            printf("checkpoint");
            children[i].pid = id;
            children[i].isAlive = true;
        }
    }
    while(1);
    free(children);
    return 0;
}
