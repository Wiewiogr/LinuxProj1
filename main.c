#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void usage()
{
    printf("Usage: ./prog.o --dwa/--trzy/-2/-3 --poziom=<non negative number>\n");
}

int main(int argc, char *argv[])
{
    int c;
    int error = 0;
    int numOfChildren = 0;
    int level = 0;
    char * ppids = "";
    while (1)
    {
        int option_index = 0;
        static struct option long_options[] = {
        {"dwa", no_argument, 0, '2' },
        {"trzy",  no_argument, 0, '3' },
        {"poziom",  required_argument, 0, 'l' },
        {"ppid", required_argument, 0, 'p' },
        {0, 0, 0, 0 }
        };

        c = getopt_long(argc, argv, "23h",
            long_options, &option_index);
        if (c == -1)
        break;

        switch (c) {
        case '2':
        case '3':
            if (numOfChildren != 0)
            {
                printf("Number of children occurs in two program arguments\n");
                error = 1;
            }
            numOfChildren = c - '0';
            break;
        case 'l':
            if (level != 0)
            {
                printf("Level occurs in two program arguments\n");
                error = 1;
            }
            level = atoi(optarg);
            break;
        case 'p':
            ppids = optarg;
            break;
        case 'h':
            usage();
            return 1;
        case '?':
            break;
        default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    if (optind < argc) 
        error = 1;

    if(level != 0 && numOfChildren != 0)
    {
        printf("Number of Children : %d\nLevel : %d\n",numOfChildren, level);
        if(strlen(ppids) != 0)
            printf("ppids : %s\n",ppids);
    }
    else
        error = 1;
    if(error)
    {
        printf("Wrong Usage, should be:\n");
        usage();
    }

    return 0;
}
