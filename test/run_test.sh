#!/bin/bash

cpplist=$(cd src/ && ls -a | grep .cpp)
echo -e "target => \n$cpplist"

targets=$(echo -e $cpplist|xargs)

okflag=1
for e in ${targets[@]}; do
    echo -e "\n***${e}***"
    clang++ -std=c++14 -fsanitize=address "$e"
    ./a.out
    if [ $? -ne 0 ]; then
        echo "!!!FAILUE!!!"
        okflag=0
    else
        echo "===SUCCESS==="
    fi
done

if [ $okflag -eq 1 ]; then
    echo -e "\ntest clear"
    exit 0
else
    echo -e "\ntest failed"
    exit 1
fi
