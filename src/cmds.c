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
    "Saqttra Eugenia 0.x.x--alpha\n"
    "Copyright (C) 2025 Saqttra\n"
  );
}

/* Usage: eugenia <commands>
   Commands:
     --help          Display this information.
     --version       Display Eugenia's version.
     --stats         Display file's global stats: total bytes, runes,
                     lines, etc.*/

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
    "--stats <file>", 
    "Display file's global stats: total bytes, runes, lines, etc."
  );
}

/* Example:
   $ eugenia --stats poem.txt

   Total bytes: 104
   Total runas: 96
   UTF-8 valid: yes
   1-byte: 88 (91.7%)
   2-byte: 8  (8.3%)
   Lines: 3
   Most common rune: U+0020 (space) */
void stats_cmd(const char* filename)
{
  Reader* reader = init_reader(filename, "--stats");
  if(!reader){
    perr6("--stats");
    exit(6);
  }

  /* printf("readOffset: %lu\n", reader->readOffset); */

  free_reader(&reader);
}

void scan_cmd(const char* filename)
{
  printf("Filename: %s\n", filename);
}
