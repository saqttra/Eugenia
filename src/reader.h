/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#ifndef EUGENIA_READER_H_
#define EUGENIA_READER_H_

#include <stdio.h>

typedef struct Reader {
  FILE* file;
  size_t readOffset;
} Reader;

Reader* init_reader(const char* filename, const char* cmd);
void free_reader(Reader** readerPtr);

#endif /* reader.h */