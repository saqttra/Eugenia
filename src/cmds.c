/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#include <stdio.h>
#include <stdlib.h>
#include "cmds.h"
#include "errors.h"
#include "reader.h"

void version_cmd(void)
{
  printf(
    "Saqttra Eugenia 1.0.0\n"
    "Copyright (C) 2025 Saqttra\n"
  );
}

/* Usage: eugenia <commands>
   Commands:
     --help          Display this information.
     --version       Display Eugenia's version.
     --scan <file>   Scan and display the UTF-8 structure of <file> */

void help_cmd(void)
{
  printf(
    "Usage: eugenia <commands>\n"
    "Commands:\n"
    "  %-15s %s\n"
    "  %-15s %s\n"
    "  %-15s %s\n",
    "--help", "Display this information",
    "--version", "Display Eugenia's version",
    "--scan <file>", 
    "Scan and display the UTF-8 structure of <file>"
  );
}

/* TBI: stats command
   Example:
    $ eugenia --stats poem.txt

    Total bytes: 104
    Total runes: 96
    UTF-8 valid: yes
    1-byte: 88 (91.7%)
    2-byte: 8  (8.3%)
    Lines: 3
    Most common rune: U+0020 (space) */
/* void stats_cmd(const char* filename)
{
  Reader* reader = init_reader(filename, "--stats");
  if(!reader){
    perr6("--stats");
    exit(6);
  }
  free_reader(&reader);
} */

void scan_cmd(const char* filename)
{
  Reader* reader = init_reader(filename, "--scan");
  if(!reader){
    perr6("--scan");
    exit(6);
  }

  scan(reader);

  free_reader(&reader);
}
