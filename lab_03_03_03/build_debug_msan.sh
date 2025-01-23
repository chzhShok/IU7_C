#!/bin/bash

clang -c *.c -Werror -Wall -std=c99 -Wpedantic -O0 -Wextra -Wfloat-conversion -Wfloat-equal -fsanitize=memory -fno-omit-frame-pointer -g
clang *.o -o app.exe -lm -fsanitize=memory -fPIE -pie
