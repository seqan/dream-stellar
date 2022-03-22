#!/bin/bash

cd build

for w in 19 23
do
    echo "Creating IBF for w=$w and k=19"
    output="8bins"$w"window.ibf"
    valik build bin_paths.txt --window "$w" --kmer 19 --output "$output" --size 32k
done
