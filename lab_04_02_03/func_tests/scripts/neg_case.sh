#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Использование: $0 файл_входных_данных"
  exit 1
fi

input_file="$1"
result_file="temp.out"

./app.exe < "$input_file" > "$result_file"
result=$?

if [ "$result" -eq 0 ]; then
  exit 1
else
  exit 0
fi
