#!/bin/bash

SRC_DIR="src"

CPPLIST=$(cd $SRC_DIR/ && ls -a | grep .cpp)
echo -e "target => \n$CPPLIST"
TARGETS=$(echo -e $CPPLIST|xargs)

REPO_URL='https://github.com/atcoder/ac-library.git'
git clone $REPO_URL
ls -a # tmp

OKFLAG=1
for e in ${TARGETS[@]}; do
    echo -e "\n***${e}***"
    g++ -g $SRC_DIR/$e -o a.out -std=gnu++17 -Wall -Wextra -Wshadow -Wconversion -ggdb -I ac-library/
    ./a.out
    if [ $? -ne 0 ]; then
        echo "!!!FAILUE!!!"
        OKFLAG=0
    else
        echo "===SUCCESS==="
    fi
done

if [ $OKFLAG -eq 1 ]; then
    echo -e "\ntest clear"
    exit 0
else
    echo -e "\ntest failed"
    exit 1
fi
