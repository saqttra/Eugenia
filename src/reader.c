/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#include <stdlib.h>
#include "reader.h"
#include "errors.h"

Reader* init_reader(const char* filename, const char* cmd)
{
  Reader* reader = malloc(sizeof(Reader));
  if(!reader)
    return NULL;

  reader->file = fopen(filename, "rb");
  if(!reader->file){
    perr5(cmd, filename);
    free(reader);
    exit(5);
  }

  reader->readOffset = 0;
  return reader;
}

void free_reader(Reader** readerPtr)
{
  if(!readerPtr || !*readerPtr)
    return;

  if((*readerPtr)->file){
    fclose((*readerPtr)->file);
    (*readerPtr)->file = NULL;
  }

  free(*readerPtr);
  *readerPtr = NULL;
}
