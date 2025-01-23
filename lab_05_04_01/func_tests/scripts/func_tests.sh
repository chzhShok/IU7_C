#!/bin/bash

green="\033[92m"
red="\033[31m"
reset="\033[0m"

n=1
err=0
for test in ./func_tests/data/pos_??_in.txt; do
	echo "Pos test $n: "
	if ./func_tests/scripts/pos_case.sh "$test" "${test//in/out}" "${test//in/args}"; then
		echo -e "$green-PASS-$reset\n"
	else
		echo -e "$red-ERROR-$reset\n"
		err=$((err+1))
	fi
	n=$((n+1))
done
n=1
for test in ./func_tests/data/neg_??_in.txt; do
	echo "Neg test $n: "
	if ./func_tests/scripts/neg_case.sh "$test" "${test//in/args}"; then
		echo -e "$green-PASS-$reset\n"
	else
		echo -e "$red-ERROR-$reset\n"
		err=$((err+1))
	fi
	n=$((n+1))
done
exit $err
