#!/bin/bash

clang -c *.c -Werror -Wall -std=c99 -Wpedantic -O0 -Wextra -Wfloat-conversion -Wfloat-equal -fsanitize=address -fno-omit-frame-pointer -g
clang -o app.exe -lm -fsanitize=address -static-libsan *.o
