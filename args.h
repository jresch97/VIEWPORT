/**
 *
 * Copyright (C) 2022 Jared B. Resch
 *
 * This file is part of VIEWPORT.
 * 
 * VIEWPORT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * VIEWPORT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with VIEWPORT. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef VIEWPORT_ARGS_H
#define VIEWPORT_ARGS_H

#include <stdio.h>
#include <string.h>

enum ARGERRS { ARGDUPL, ARGMISS, ARGMISSV };

typedef struct ARGUMENT {
        const char *n, *a, *u;
        int         f,  r;
        const char *d, *v;
        int         s,  i,  e;
} ARGUMENT;

int argparse(ARGUMENT *args, int argc, char *argv[])
{
        int i, j, k, f, n = 0;
        while (args->n) {
                args->v = args->d, args->s = args->i = args->e = 0;
                args++, n++;
        }
        for (i = 1, args -= n; i < argc; i++) {
                k = 0, f = 0;
                for (j = 0; j < n; j++) {
                        if (!strcmp(argv[i], args[j].n) ||
                            !strcmp(argv[i], args[j].a)) {
                                if (args[j].i > 0) {
                                        args[j].i = i, args[j].e = ARGDUPL;
                                        return j + 1;
                                }
                                else if (k == 0) args[j].i = i, k = j, f = 1;
                        }
                }
                if (!f) return -i;
                else if (args[k].f) args[k].s = 1;
                else if (++i >= argc || argv[i][0] == '-') {
                        args[k].e = ARGMISSV;
                        return k + 1;
                }
                else args[k].v = argv[i];
        }
        for (i = 0; i < n; i++) {
                if (args[i].r && args[i].i == 0) {
                        args[i].e = ARGMISS;
                        return i + 1;
                }
        }
        return 0;
}

void argerr(ARGUMENT *args, char *argv[], int e)
{
        if (e < 0) {
                e = abs(e);
                fprintf(stderr, "unknown arg %s at argv[%d]\n",
                        argv[e], e);
        }
        else {
                e = e - 1;
                if (args[e].e == ARGDUPL) {
                        fprintf(stderr,
                                "duplicate arg %s (%s) at argv[%d]\n",
                                args[e].n, args[e].a, args[e].i);
                }
                else if (args[e].e == ARGMISSV) {
                        fprintf(stderr,
                                "no value for arg %s (%s) at argv[%d]\n",
                                args[e].n, args[e].a, args[e].i);
                }
                else if (args[e].e == ARGMISS) {
                        fprintf(stderr,
                                "required arg %s (%s) missing\n",
                                args[e].n, args[e].a);
                }
        }
}

void arghelp(ARGUMENT *args)
{
        while (args->n) {
                printf("%s%s (%s) - %s\n",
                        args->r ? "* " : "  ",
                        args->n, args->a, args->u);
                args++;
        }
}

#endif