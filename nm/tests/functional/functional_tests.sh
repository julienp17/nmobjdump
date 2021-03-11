#!/bin/bash

WD=./tests/functional
RD=$WD/ressources
BIN=nm
MY_BIN=./my_nm

passed=0
nb_tests=0
red=`tput setaf 1`
green=`tput setaf 2`
yellow=`tput setaf 3`
white=`tput setaf 7`

function run_test {
    sleep 0.01
    nb_tests=$((nb_tests+1))

    descr=$1
    arg=$2
    my_status=0

    echo "${yellow}Running '$descr'...${white}"

    $MY_BIN  $arg &> $MY_BIN.txt
    my_status=$?
    $BIN $arg &> $BIN.txt
    status=$?
    if [ $my_status -ne $status ] ; then
        echo "${red}> Failed !"
        echo "$MY_BIN returned $my_status"
        echo "$BIN returned $status"
        return 1
    fi

    diff $MY_BIN.txt $BIN.txt &> /dev/null
    status=$?
    if [ $status -eq 0 ] ; then
        echo "${green}> Success!"
        passed=$((passed+1))
    else
        echo "${red}> Failed !"
        diff --side-by-side --color --suppress-common-lines $MY_BIN.txt $BIN.txt
    fi
    return $status
}

run_test "no args"
run_test "wrong file format"     $RD/test.txt
run_test "executable"            $RD/main
run_test "main.o"                $RD/main.o
run_test "dump.o"                $RD/dump.o
run_test "extract.o"             $RD/extract.o
run_test "flags.o"               $RD/flags.o
run_test "objdump.o"             $RD/objdump.o
run_test "multiple .o"           $RD/main.o $RD/dump.o $RD/extract.o $RD/flags.o
run_test "multiple with invalid" $RD/main.o $RD/test.txt $RD/ $RD/extract.o
run_test "libasm.so"             $RD/libasm.so
run_test "archive"               $RD/main.a
# run_test "coredump"           $RD/core

failed=$((nb_tests - passed))
echo "${yellow}ran $nb_tests tests, ${green}$passed passed, ${red}$failed failed${white}"

rm -f $MY_BIN.txt
rm -f $BIN.txt

if [[ failed -gt 0 ]]; then
    exit 1
else
    exit 0
fi