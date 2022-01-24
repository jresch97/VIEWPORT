#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "args.h"

static ARGUMENT args[] = {
        { "--help", "-h", "show help text",          1, 0 },
        { "--vert", "-v", "path to vertex shader",   0, 1 },
        { "--frag", "-f", "path to fragment shader", 0, 1 },
        { NULL }
};

int main(int argc, char *argv[])
{
        int         e;
        const char *vp;
        const char *fp;
        if ((e = argparse(args, argc, argv)) != 0) {
                argerr(args, argv, e);
                arghelp(args);
                return EXIT_FAILURE;
        }
        if (args[0].s) {
                arghelp(args);
                return EXIT_SUCCESS;
        }
        vp = args[1].v;
        fp = args[2].v;
        printf("vp=%s\n", vp);
        printf("fp=%s\n", fp);
        return EXIT_SUCCESS;
}