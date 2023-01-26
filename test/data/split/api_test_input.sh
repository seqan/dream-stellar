#!/bin/bash

set -e

cd split

#----------- Simulate chromosomes of various lengths -----------

BINARY_DIR="${1}"
SEED=${2}

for overlap in 0 20
do
    for bins in 4 16
    do
        i=1
        for length in 210 490 420 280 4
        do
            echo "Simulating chromosome with length $length"
            chr_out="chr"$i".fasta"
            $BINARY_DIR/mason_genome -l $length -o $chr_out -s $SEED &>/dev/null

            sed -i "s/^>.*$/>chr$i/g" $chr_out
            let i=i+1
        done

        out_dir=write_out_${overlap}_${bins}
        mkdir -p ${out_dir}
        cat chr*.fasta > ${out_dir}/ref.fasta
        rm chr*.fasta

        valik split ${out_dir}/ref.fasta --overlap ${overlap} --bins ${bins} --reference-output ${out_dir}/reference_metadata.txt --segment-output ${out_dir}/reference_segments.txt
    done
done
