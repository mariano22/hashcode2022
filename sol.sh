#!/bin/bash

SOL=$1
OUT=$2

echo "Using solution ${SOL}.cpp"
g++ -O3 -w -o $SOL.out -std=c++17 $SOL.cpp
chmod +x $SOL.out

rm -rf ./$OUT/
mkdir ./$OUT
cp ./$SOL.cpp ./$OUT

for filepath in ./in/*.in; do
    echo ""
    echo ""
    filename="${filepath##*/}"
    echo "CASE $filename"
    time ./$SOL.out < $filepath > ./$OUT/${filename%.*}.out
done

