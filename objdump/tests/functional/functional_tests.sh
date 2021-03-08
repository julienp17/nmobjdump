#!/bin/bash

WD=./tests/functional
BIN=objdump -fs
MY_BIN=./my_objdump

passed=0
nb_tests=0
red=`tput setaf 1`
green=`tput setaf 2`
white=`tput setaf 7`

function run_test {
    descr=$1
    arg=$2
    echo "Running: '$descr' with arg: [`basename $arg 2> /dev/null`]"
    $MY_BIN  $arg 2>&1 $MY_BIN.txt
    $BIN     $arg 2>&1 $BIN.txt
    diff $MY_BIN.txt $BIN.txt &> /dev/null
    status=$?
    if [ $status -eq 0 ] ; then
        echo "${green}> Success!${white}"
        passed=$((passed+1))
    else
        echo "${red}> Failed ! Writing diff in ${descr// /_}.txt${white}"
        diff -y $MY_BIN.txt $BIN.txt > $WD/${descr// /_}.txt
    fi
    rm $MY_BIN.txt
    rm $BIN.txt
    nb_tests=$((nb_tests+1))
    sleep 0.01
    return $status
}

run_test "no args"
run_test "executable" "$WD/main"
run_test "object" "$WD/main.o"
run_test "shared object" "$WD/shared.so"
run_test "archive" "$WD/main.a"

failed=$((nb_tests - passed))
echo "ran $nb_tests tests, ${red}$failed failed${white}, ${green}$passed passed${white}"

if [[ failed -gt 0 ]]; then
    exit 1
else
    exit 0
fi