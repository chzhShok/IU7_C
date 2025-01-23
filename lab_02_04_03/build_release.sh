#!/bin/bash

gcc-13 -c ./main.c -Werror -Wall -std=c99 -Wpedantic -O2 -Wextra -Wfloat-conversion -Wfloat-equal
gcc-13 ./main.o -o app.exe -lm
