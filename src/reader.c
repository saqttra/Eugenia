/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "reader.h"
#include "errors.h"
#include "utils.h"
#include "utf8.h"

#define UTF8_MAX_WIDTH 4

Reader* init_reader(const char* filename, const char* cmd)
{
  /* TODO: avoid magical number for page size. */
  Reader* reader = malloc(sizeof(Reader) + 4);
  if(!reader)
    return NULL;

  reader->file = fopen(filename, "rb");
  if(!reader->file){
    perr5(cmd, filename);
    free(reader);
    exit(5);
  }

  reader->readBuf = (Byte*)(reader + 1);
  reader->bytesRead = 0;
  reader->offset = 0;
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

/* static void print_header(const unsigned long digits); */
static size_t refill(Reader* reader);

void scan(Reader* reader)
{
  /* const int digits = count_digits(ULONG_MAX); */
  Byte runeBuf[UTF8_MAX_WIDTH] = {0};
  int runeWidth = 0, i;
  Rune codepoint;

  /* TODO: for later use */
  /* size_t offset, line, col;
    offset = line = col = 0; */
  /* Line Col Bytes UTF-8 Unicode Rune */
  /* print_header(digits); */

  while(1){
    if(reader->offset >= reader->bytesRead){
      if(!refill(reader))
        return;
    }

    runeWidth = rune_width(reader->readBuf[reader->offset]);
    if(runeWidth > (int)(reader->bytesRead - reader->offset)){
      if(!refill(reader)){
        printf("TODO: PENDING to handle\n");
        return;
      }
      continue;
    }

    for(i=0; i < runeWidth; i++)
      runeBuf[i] = reader->readBuf[reader->offset + i];

    codepoint = decode_seq(runeBuf);
    printf("U+%04lX : %ld\n", codepoint, codepoint);

    reader->offset += runeWidth;
  }
}

/* static void print_header(const unsigned long digits)
{
  int offsetWidth = digits > strlen("Offset") ? digits : strlen("Offset");
  int lineWidth   = digits > strlen("Line")   ? digits : strlen("Line");
  int colWidth    = digits > strlen("Col")    ? digits : strlen("Col");

  printf(
    "%*s %*s %*s\n", 
    -offsetWidth, "Offset", 
    -lineWidth, "Line", 
    -colWidth, "Col"
  );
} */

static size_t refill(Reader* reader)
{
  int remaining = 0;
  
  if(reader->offset < reader->bytesRead){
    remaining = reader->bytesRead - reader->offset;
    memmove(
      reader->readBuf,
      reader->readBuf + reader->offset,
      remaining
    );
  }

  /* TODO: avoid magical number for page size. */
  reader->bytesRead = fread(
    reader->readBuf + remaining,
    sizeof(Byte),
    4 - remaining,
    reader->file
  );

  reader->bytesRead = remaining + reader->bytesRead;
  reader->offset = 0;

  return reader->bytesRead;
}

#undef UTF8_MAX_WIDTH

/* TODO: for later use */
/*for(i = 0; i < reader->bytesRead; i++){
  printf(
    "%0*lu %*lu %*lu\n",
    digits, offset,
    -digits, line,
    -digits, col
  );
  printf("%X ", reader->readBuf[i]);

  col++;
  offset++;
  reader->offset++;
}*/
