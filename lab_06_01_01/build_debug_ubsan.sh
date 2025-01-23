#!/bin/bash

clang -c *.c -Werror -Wall -std=c99 -Wpedantic -O0 -Wextra -Wfloat-conversion -Wfloat-equal -fsanitize=undefined -fno-omit-frame-pointer -g
clang *.o -o app.exe -lm -fsanitize=undefined
