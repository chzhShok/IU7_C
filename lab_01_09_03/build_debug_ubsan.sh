#!/bin/bash

clang -c main.c -Werror -Wall -std=c99 -Wpedantic -O0 -Wextra -Wfloat-conversion -Wfloat-equal -fsanitize=undefined -fno-omit-frame-pointer -g
clang main.o -o app.exe -lm -fsanitize=undefined 