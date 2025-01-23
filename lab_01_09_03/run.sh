#!/bin/bash

magenta="\033[35m"
reset="\033[0m"

echo -e "$magenta"--COVERAGE--"$reset"
./build_debug.sh
./func_tests/scripts/func_tests.sh
./collect_coverage.sh

echo -e "\n$magenta"--ADDRESS SANITIZER--"$reset"
./clean.sh
./build_debug_asan.sh
./func_tests/scripts/func_tests.sh

echo -e "\n$magenta"--UNDEFINED BEHAVIOR SANITIZER--"$reset"
./clean.sh
./build_debug_ubsan.sh
./func_tests/scripts/func_tests.sh

# memory sanitizer не поддерживается macos, поэтому был закомментирован
# echo -e "\n$magenta"--MEMORY SANITIZER--"$reset"
# ./clean.sh
# ./build_debug_msan.sh
# ./func_tests/scripts/func_tests.sh

echo -e "\n$magenta---TESTS---$reset"
./clean.sh
./build_debug.sh
./func_tests/scripts/func_tests.sh
