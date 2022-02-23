#!/bin/bash

SOL=$1

echo "Using solution ${SOL}.cpp"
g++ -O3 -w -o $SOL.out -DDEBUG -std=c++17 $SOL.cpp
chmod +x $SOL.out

for filepath in ./in/*.in; do
    filename="${filepath##*/}"
    echo "CASE $filename"
    time ./$SOL.out < $filepath > ./out/${filename%.*}.out
done

