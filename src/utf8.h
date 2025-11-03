/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#ifndef EUGENIA_UTF8_H_
#define EUGENIA_UTF8_H_

#include "typedefs.h"

int rune_width(const Byte firstByte);
Rune decode_seq(const Byte* seq);

#endif /* utf8.h */
