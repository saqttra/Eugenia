/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#include <math.h>
#include "utils.h"

int count_digits(unsigned long maxVal)
{
  int digits = 0;
  if (maxVal == 0) return 1;
    
  digits = (int)(log10((double)maxVal)) + 1;
  return digits;
}
