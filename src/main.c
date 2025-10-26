/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "cmds.h"

#define TOTAL_NUM_CMDS 2

int str_in_strlist(const char* str, const char* list[], int len)
{
  while(len-- > 0){
    if(!strcmp(str, list[len]))
      return 1;
  }

  return 0;
}

int main(int argc, const char* argv[])
{
  const char* cmds[TOTAL_NUM_CMDS] = {"--version", "--help"};

  if(argc < 2){
    perr1();
    return 1;
  }

  if(!str_in_strlist(argv[1], cmds, TOTAL_NUM_CMDS)){
    perr2(argv[1]);
    return 1;
  }

  if(strcmp(argv[1], "--version") == 0){
    version_cmd();
    return 0;
  }

  if(strcmp(argv[1], "--help") == 0){
    help_cmd();
    return 0;
  }
}

#undef TOTAL_NUM_CMDS
