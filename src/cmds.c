/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#include <stdio.h>
#include "cmds.h"

void version_cmd(void)
{
  printf(
    "Saqttra Eugenia 0.x.x--alpha\n"
    "Copyright (C) 2025 Saqttra\n"
  );
}

/* Usage: eugenia <commands>
   Commands:
     --help          Display this information
     --version       Display Eugenia's version */

void help_cmd(void)
{
  printf(
    "Usage: eugenia <commands>\n"
    "Commands:\n"
    "  %-15s %s\n"
    "  %-15s %s\n"
    "  %-15s %s\n",
    "--help", "Display this information",
    "--version", "Display Eugenia's version"
    "--stats <file>", ""
  );
}
