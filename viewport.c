/**
 *
 * Copyright (C) 2021 Jared B. Resch
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
        if (!argparse(args, argc, argv, &e)) {
                if (!args[0].s) argerr(args, argv, e);
                arghelp(args);
                return EXIT_FAILURE;
        }
        vp = args[1].v;
        fp = args[2].v;
        printf("vp=%s\n", vp);
        printf("fp=%s\n", fp);
        return EXIT_SUCCESS;
}