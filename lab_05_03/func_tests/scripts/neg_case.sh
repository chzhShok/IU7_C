#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Использование: $0 файл_входных_данных файл_аргументов"
  exit 1
fi

input_txt="$1"
args_file="$2"
result_file="temp.out"

result=0

input_bin="${input_txt//txt/bin}"
./app.exe import "$input_txt" "$input_bin" > "$result_file"
result=$((result + $?))

args=$(cat "$args_file")

eval "./app.exe $args > \"\$result_file\""
result=$((result + $?))

if [ "$result" -eq 0 ]; then
  exit 1
else
  exit 0
fi
