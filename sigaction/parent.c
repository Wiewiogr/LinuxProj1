#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        printf("Too few arguments...\n");
        exit(1);
    }

    for(int i = 1u ; i < argc ;i++)
    {
        pid_t id = 123;
        if((id = fork()) == 0)
        {
            char* signal = NULL;
            printf("arg : %s\n", argv[i]);
            float time = strtof(argv[i], &signal);
            printf("Value : %lf, rest : %s \n", time, signal);
            char killArg[20];
            char toutArg[20];
            char siblingArg[20];
            sprintf(killArg,"--kill=%s",signal);
            sprintf(toutArg,"--tout=%lf",time);
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
                printf("Zjebło się ;c numer:\n");
            }
            break;
        }
        else
            printf("Jestem tatus!\n");
    }
    return 0;
}
