#!/bin/bash

SOL=$1

echo "Using solution ${SOL}.cpp"
g++ -O3 -w -o $SOL.out -std=c++17 $SOL.cpp
chmod +x $SOL.out

for filepath in ./in/*.in.txt; do
    echo ""
    echo ""
    filename="${filepath##*/}"
    echo "CASE $filename"
    time ./$SOL.out < $filepath > ./out/${filename%.*}.out
done

