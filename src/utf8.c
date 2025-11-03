/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#include "utf8.h"

int rune_width(const Byte firstByte)
{ 
  /* ASCII */
  if((firstByte & 0x80) == 0x00) return 1;

  if((firstByte & 0xE0) == 0xC0) return 2;
  if((firstByte & 0xF0) == 0xE0) return 3;
  if((firstByte & 0xF8) == 0xF0) return 4;

  /* continuation byte */
  if((firstByte & 0xC0) == 0x80) return 0;

  return -1;
}

Rune decode_seq(const Byte* seq)
{ 
  /* ASCII */
  if((seq[0] & 0x80) == 0x00)
    return (Rune)seq[0];

  /* matches? 110x xxxx 10yy yyyy */
  if(((seq[0] & 0xE0) == 0xC0) && /* 110x xxxx */
     ((seq[1] & 0xC0) == 0x80))   /* 10yy yyyy */
  /* LOC 40: xxxxx
                  yyyyyy
             -----------
             xxxxxyyyyyy */  
    return (Rune)(((seq[0] & 0x1F) << 6) | (seq[1] & 0x3F));

  /* matches? 1110 xxxx 10yy yyyy 10zz zzzz */
  if(((seq[0] & 0xF0) == 0xE0) && /* 1110 xxxx */
     ((seq[1] & 0xC0) == 0x80) && /* 10yy yyyy */
     ((seq[2] & 0xC0) == 0x80))   /* 10zz zzzz */
  /* LOC 51-53: xxxx
                    yyyyyy
                          zzzzzz
                ----------------
                xxxxyyyyyyzzzzzz */
    return (Rune)(((seq[0] & 0xF)  << 12) |
                  ((seq[1] & 0x3F) <<  6) |
                   (seq[2] & 0x3F));

  /* matches? 1111 0www 10xx xxxx 10yy yyyy 10zz zzzz */
  if (((seq[0] & 0xF8) == 0xF0) && /* 1111 0www */
      ((seq[1] & 0xC0) == 0x80) && /* 10xx xxxx */
      ((seq[2] & 0xC0) == 0x80) && /* 10yy yyyy */
      ((seq[3] & 0xC0) == 0x80))   /* 10zz zzzz */
  /* LOC 66-69: www
                   xxxxxx
				                 yyyyyy
					                     zzzzzz
                ---------------------
                wwwxxxxxxyyyyyyzzzzzz -> MAX 21-bit */  
    return (Rune)(((seq[0] & 0x7)  << 18) |
                  ((seq[1] & 0x3F) << 12) |
                  ((seq[2] & 0x3F) <<  6) |
                   (seq[3] & 0x3F));

  return -1;
}
