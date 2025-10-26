/* Copyright (C) 2025, Saqttra. All rights reserved.

This file is part of Saqttra Eugenia.

This source code is licensed under the MIT license
found in the LICENSE file in the root directory.

<https://github.com/saqttra/Eugenia>. */

#ifndef EUGENIA_ERRORS_H_
#define EUGENIA_ERRORS_H_

void perr1(void);
void perr2(const char* badCmd);
void perr3(const char* cmd);
void perr4(const char* cmd, int reqFiles);
void perr5(const char* cmd, const char* filename);
void perr6(const char* cmd);

#endif /* errors.h */
