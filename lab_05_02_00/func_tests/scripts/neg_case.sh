#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Использование: $0 файл_входных_данных"
  exit 1
fi

args_file="$2"
result_file="temp.out"

args=$(cat "$args_file")

./app.exe "$args" > "$result_file"
result=$?

if [ "$result" -eq 0 ]; then
  exit 1
else
  exit 0
fi
