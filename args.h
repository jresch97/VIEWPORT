#ifndef VIEWPORT_ARGS_H
#define VIEWPORT_ARGS_H

enum ARGERRS { ARGDUPL, ARGMISS, ARGMISSV };

typedef struct ARGUMENT {
        const char *n, *a, *u;
        int         f,  r;
        const char *d, *v;
        int         s,  i,  e;
} ARGUMENT;

int argparse(ARGUMENT *args, int argc, char *argv[], int *e)
{
	ARGUMENT *arg;
        int       n, i, j, f;
        arg = args;
        while (arg->n) {
                arg->i = -1;
                arg->v = arg->d;
                arg->s = arg->e = 0;
                arg++;
                n++;
        }
        for (i = 1; i < argc; i++) {
                for (j = 0, f = 0; j < n; j++) {
                        if (strcmp(argv[i], args[j].n) == 0 ||
                            strcmp(argv[i], args[j].a) == 0) {
                                if (args[j].i > 0) {
                                        args[j].i = i;
                                        args[j].e = ARGDUPL;
                                        *e = j;
                                        return 0;
                                }
                                args[j].i = i;
                                if (args[j].f) {
                                        args[j].s = 1;
                                        f = 1;
                                        break;
                                }
                                i++;
                                if ((i < argc && argv[i][0] == '-') ||
                                    i >= argc) {
                                        args[j].e = ARGMISSV;
                                        *e = j;
                                        return 0;
                                }
                                else args[j].v = argv[i];
                                f = 1;
                                break;
                        }
                }
                if (!f) {
                        *e = -i;
                        return 0;
                }
        }
        for (i = 0; i < n; i++) {
                if (args[i].r && args[i].i < 0) {
                        args[i].e = ARGMISS;
                        *e = i;
                        return 0;
                }
        }
        return 1;
}

void argerr(ARGUMENT *args, char *argv[], int e)
{
        if (e < 0) {
                e = abs(e);
                fprintf(stderr, "unknown arg %s at argv[%d]\n",
                        argv[e], e);
        }
        else if (args[e].e == ARGDUPL) {
                fprintf(stderr, "duplicate arg %s (%s) at argv[%d]\n",
                        args[e].n, args[e].a, args[e].i);
        }
        else if (args[e].e == ARGMISSV) {
                fprintf(stderr, "no value for arg %s (%s) at argv[%d]\n",
                        args[e].n, args[e].a, args[e].i);
        }
        else if (args[e].e == ARGMISS) {
                fprintf(stderr, "required arg %s (%s) missing\n",
                        args[e].n, args[e].a);
        }
}

void arghelp(ARGUMENT *args)
{
        ARGUMENT *arg;
        arg = args;
        while ((arg = args++)->n) {
                printf("%s%s (%s) - %s\n",
                        arg->r ? "* " : "  ", arg->n, arg->a, arg->u);
        }
}

#endif