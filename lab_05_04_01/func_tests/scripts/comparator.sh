#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Использование: comparator.sh файл1 файл2"
  exit 1
fi

file1=$1
file2=$2


get_numbers() {
  grep -oE "[-+]?([0-9]+[.])?[0-9]" "$1"
}

f1=$(get_numbers "$file1")
f2=$(get_numbers "$file2")
if [ "$f1" != "$f2" ]; then
  exit 1
fi
  exit 0
