/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#include <stdio.h>
#include "errors.h"

void perr1(void)
{
  fprintf(
    stderr,
    "usage: eugenia [options] [arguments]\n"
    "for further help: eugenia --help\n"
  );
}

void perr2(const char* badCmd)
{
  fprintf(
    stderr,
    "invalid command: %s\n"
    "for further help: eugenia --help\n",
    badCmd
  );
}

void perr3(void)
{
  fprintf(stderr, "--stats: fatal error: no input file\n");
}

void perr4(int reqFiles)
{
  fprintf(
    stderr,
    "--stats: too many files for '--stats' command\n"
    "expected 1 file, but received %d files\n",
    reqFiles
  );
}

void perr5(const char* cmd, const char* filename)
{
  fprintf(
    stderr,
    "%s: fatal error: no such file (%s)\n",
     cmd, filename
  );
}

void perr6(const char* cmd)
{
  fprintf(
    stderr,
    "%s: fatal error: could not init reader\n",
    cmd
  );
}
