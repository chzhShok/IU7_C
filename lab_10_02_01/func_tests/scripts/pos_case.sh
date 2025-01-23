#!/bin/bash

if [ $# -ne 3 ]; then
  echo "Использование: $0 файл_входных_данных файл_ожидаемых_выходных_данных"
  exit 1
fi

input_file="$1"
expected_output_file="$2"
#args_file="$3"
result_file="temp.out"

#args=$(cat "$args_file")

#eval "./app.exe $args > \"$result_file\""
./app.exe < $input_file > $result_file
result=$?

if [ "$result" -ne 0 ]; then
  exit 1
fi

if ./func_tests/scripts/comparator.sh "$result_file" "$expected_output_file"; then
  exit 0
else
  exit 1
fi
