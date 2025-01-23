#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Использование: comparator.sh файл1 файл2"
  exit 1
fi

file1=$1
file2=$2

if [ "$(diff "$file1" "$file2")" != '' ]; then
  exit 1
fi
  exit 0
