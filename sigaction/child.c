#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int
main(int argc, char **argv)
{
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
            printf("kill : %s\n",optarg);
            break;
        case 't':
            printf("tout : %s\n",optarg);
            break;
        case 's':
            printf("sibling : %s\n",optarg);
            break;
        }
    }
}
