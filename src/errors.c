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
