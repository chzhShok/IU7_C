#!/bin/bash

gcc-13 -c -g *.c \
  -Werror \
  -Wall \
  -std=c99 \
  -Wpedantic \
  -O0 \
  -Wextra \
  -Wfloat-conversion \
  -Wfloat-equal \
  --coverage

gcc-13 --coverage *.o -o app.exe -lm
