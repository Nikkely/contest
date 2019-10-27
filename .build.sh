#!/bin/bash

cpplist=$(ls -a | grep .cpp)
echo -e "target => \n$cpplist"

targets=$(echo -e $cpplist|xargs)

okflag=1
for e in ${targets[@]}; do
    echo "$e"
    clang++ -std=c++14 "$e"
    ./a.out
    if [ $? -ne 0 ]; then
        echo "FAILUE"
        okflag=0
    else
        echo "SUCCESS"
    fi
done

if [ $okflag -eq 1 ]; then
    echo "test clear"
    exit 0
else
    echo "test failed"
    exit 1
fi
