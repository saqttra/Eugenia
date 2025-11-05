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

static void print_header(const int digits);
static size_t refill(Reader* reader);
static const char* visible_repr(Rune codepoint, const Byte* runeBuf);

void scan(Reader* reader)
{
  const int digits = count_digits(ULONG_MAX);
  Byte runeBuf[UTF8_MAX_WIDTH] = {0};
  int runeWidth = 0, i, hexbuf;
  Rune codepoint;
  size_t offset = 0, line = 1, col = 0;

  print_header(digits);

  while(1){
    if(reader->offset >= reader->bytesRead){
      if(!refill(reader)){
        printf("EOF\n");
        return;
      }
    }

    runeWidth = rune_width(reader->readBuf[reader->offset]);
    if(runeWidth > (int)(reader->bytesRead - reader->offset)){
      if(!refill(reader)){
        printf("EOF\n");
        return;
      }
      continue;
    }

    for(i=0; i < runeWidth; i++)
      runeBuf[i] = reader->readBuf[reader->offset + i];
    codepoint = decode_seq(runeBuf);

    printf("%0*lu %*lu %*lu %-5d ",
      digits, offset,
      -digits, line,
      -digits, ++col, 
      runeWidth
    );

    if (codepoint == '\n'){
      line++;
      col = 0;
    }

    hexbuf = 0;
    for(i=0; i < runeWidth; i++)
      hexbuf += printf("0x%02X ", runeBuf[i]);

    for (; hexbuf < 20; hexbuf++)
      putchar(' ');

    printf("U+%04lX : %s\n", codepoint, visible_repr(codepoint, runeBuf));

    reader->offset += runeWidth;
    offset += runeWidth;

    /* clean buffer */
    runeBuf[0] = runeBuf[1] = runeBuf[2] = runeBuf[3] = 0;
  }
}

/* stDigits: size_t's max digits */
static void print_header(const int stDigits)
{
  /* Offset Line Col Width UTF-8 Unicode/Rune */
  printf(
    "%*s %*s %*s %*s %*s %*s\n",
    -stDigits, "Offset",
    -stDigits, "Line",
    -stDigits, "Col",
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

static const char* visible_repr(Rune codepoint, const Byte* runeBuf)
{
  switch(codepoint) {
    case '\0':  return "\\0";
    case '\t':  return "\\t";
    case '\n':  return "\\n";
    case '\r':  return "\\r";
    case '\v':  return "\\v";
    case '\f':  return "\\f";
    case '\a':  return "\\a";
    case '\b':  return "\\b";
    case 0x1B:  return "\\e";  /* ESC */
    default:
      /* control chars (0x00-0x1F y 0x7F-0x9F) */
      if ((codepoint >= 0 && codepoint <= 0x1F) || 
          (codepoint >= 0x7F && codepoint <= 0x9F)) {
        return "[CTRL]";
      }

      /* visible: runeBuf
         LOC 102: already ensures null termination */
      return (char*)runeBuf;
  }
}

#undef UTF8_MAX_WIDTH
