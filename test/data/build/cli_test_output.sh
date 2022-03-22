#!/bin/bash

cd build

for w in 20 23
do
    echo "Creating IBF for w=$w and k=20"
    output="8bins"$w"window.ibf"
    valik build bin_paths.txt --window "$w" --output "$output" --size 100k
done
