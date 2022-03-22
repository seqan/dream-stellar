#!/bin/bash

cd split

set -e

BINARY_DIR="${1}"
SEED=${2}

i=1
for LENGTH in 210 490 420 280 4
do
    echo "Simulating chromosome with length $LENGTH"
    chr_out="chr"$i".fasta"
    $BINARY_DIR/mason_genome -l $LENGTH -o $chr_out -s $SEED &>/dev/null

    sed -i "s/^>.*$/>chr$i/g" $chr_out
    let i=i+1
done

cat chr*.fasta > various_chromosome_lengths.fasta
rm chr*.fasta
