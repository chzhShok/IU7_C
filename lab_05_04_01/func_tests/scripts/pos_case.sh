#!/bin/bash

if [ $# -ne 3 ]; then
  echo "Использование: $0 файл_входных_данных файл_ожидаемых_выходных_данных файл_аргументов"
  exit 1
fi

input_txt="$1"
expected_output_file="$2"
args_file="$3"
result_file="temp.out"
result_file_bin="temp.bin"

result=0

input_bin="${input_txt//txt/bin}"
./app.exe import "$input_txt" "$input_bin"
result=$((result + $?))

args=$(cat "$args_file")

if echo "$args" | awk '{print $1}' | grep -q "^sb"; then
  eval "./app.exe $args > \"$result_file\""
  result=$((result + $?))
elif echo "$args" | awk '{print $1}' | grep -q "^fb"; then
  eval "./app.exe $args"
  result=$((result + $?))
  eval "./app.exe export \"$result_file_bin\" \"$result_file\""
  result=$((result + $?))
else
  eval "./app.exe $args"
  result=$((result + $?))
  eval "./app.exe export \"$input_bin\" \"$result_file\""
  result=$((result + $?))
fi

if [ "$result" -ne 0 ]; then
  exit 1
fi

if ./func_tests/scripts/comparator.sh "$result_file" "$expected_output_file"; then
  exit 0
else
  exit 1
fi
