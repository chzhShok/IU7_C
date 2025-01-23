#!/bin/bash

gcc-13 -c ./main.c \
  -Werror \
  -Wall \
  -std=c99 \
  -Wpedantic \
  -O0 \
  -Wextra \
  -Wfloat-conversion \
  -Wfloat-equal \
  --coverage

gcc-13 --coverage ./main.o -o app.exe -lm
