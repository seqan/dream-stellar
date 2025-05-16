#!/bin/bash
cd build
set -Eeuo pipefail

for w in 19 23
do
    echo "Creating IBF for w=$w and k=19"
    output="8bins"$w"window.ibf"
    valik build bin_paths.txt --metagenome --pattern 50 --window "$w" --kmer 19 --output "$output" --size 32k --seg-count 8 --without-parameter-tuning
done

rm *.arg
rm fn_err_conf*.bin
cp 8bins19window.ibf index_copy_without_meta.ibf 
