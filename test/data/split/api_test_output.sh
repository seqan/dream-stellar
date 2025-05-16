#!/bin/bash
cd split
set -Eeuo pipefail

#----------- Split multiple sequences of various lengths -----------

seg_input="various_chromosome_lengths.fasta"
for p in 20
do
    for b in 4 16
    do
        echo "Splitting the genome into $b segments that overlap by $p"
        seg_meta="multi/"$p"overlap"$b"bins.index"
        valik build "$seg_input" --pattern "$p" --seg-count "$b" --output "$seg_meta" --without-parameter-tuning
    done
done

rm multi/*.arg
rm fn_err_conf*.bin
