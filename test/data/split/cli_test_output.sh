#!/bin/bash

cd split

for o in 0 20
do
    for b in 4 16
    do
        echo "Splitting the genome into $b segments that overlap by $o"
        ref_meta="chromosome_"$o"overlap"$b"bins.txt"
        seg_meta=$o"overlap"$b"bins.txt"
        valik split various_chromosome_lengths.fasta --overlap "$o" --bins "$b" --reference-output "$ref_meta" --segment-output "$seg_meta"
    done
done

# avoid creating multiple identical reference metadata output files
rm chromosome_0overlap4bins.txt
rm chromosome_0overlap16bins.txt
rm chromosome_20overlap4bins.txt
mv "$ref_meta" chromosome_metadata.txt
