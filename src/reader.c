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

static void print_header(const unsigned long digits);
static size_t refill(Reader* reader);

void scan(Reader* reader)
{
  const int digits = count_digits(ULONG_MAX);
  Byte runeBuf[UTF8_MAX_WIDTH] = {0};
  int runeWidth = 0, i;
  int hexbuf;
  Rune codepoint;

  /*size_t offset, line, col;
  offset = line = col = 0;*/

  /* Line Col Bytes UTF-8 Unicode Rune */
  print_header(digits);

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

    printf("%-5d ", runeWidth);

    hexbuf = 0;
    for(i=0; i < runeWidth; i++)
      hexbuf += printf("0x%02X ", runeBuf[i]);

    for (; hexbuf < 20; hexbuf++)
      putchar(' ');

    printf("U+%04lX : %s\n", codepoint, runeBuf);

    /*printf(
      "%0*lu %*lu %*lu %-5d ",
      digits, offset,
      -digits, line,
      -digits, col,
      runeWidth
    );*/

    reader->offset += runeWidth;

    /* clean buffer */
    runeBuf[0] = runeBuf[1] = runeBuf[2] = runeBuf[3] = 0;
  }
}

static void print_header(const unsigned long digits)
{
  /* Offset Line Col Width UTF-8 Unicode/Rune */

  /* temp to silence compiler warnings */
  digits > strlen("Offset") ? digits : strlen("Offset");
  /* int thWidth  = digits > strlen("Offset") ? digits : strlen("Offset");
     int th2Width = digits > strlen("Line")   ? digits : strlen("Line");
     int th3Width = digits > strlen("Col")    ? digits : strlen("Col");
  
     -thWidth, "Offset",
     -th2Width, "Line",
     -th3Width, "Col", */

  printf(
    "%*s %*s %*s\n", 
    -(int)strlen("Width"), "Width",
    -19, "UTF-8",
    -8, "Unicode/Rune"
  );
}

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
