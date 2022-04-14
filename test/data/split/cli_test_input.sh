#!/bin/bash

cd split

set -e

#----------- Simulate chromosomes of various lengths -----------

BINARY_DIR="${1}"
SEED=${2}

i=1
for length in 210 490 420 280 4
do
    echo "Simulating chromosome with length $length"
    chr_out="chr"$i".fasta"
    $BINARY_DIR/mason_genome -l $length -o $chr_out -s $SEED &>/dev/null

    sed -i "s/^>.*$/>chr$i/g" $chr_out
    let i=i+1
done

cat chr*.fasta > various_chromosome_lengths.fasta
rm chr*.fasta

#----------- Simulate a single long reference sequence -----------

ref_len=10240
ref_out="single_reference.fasta"
$BINARY_DIR/mason_genome -l $ref_len -o $ref_out -s $SEED &>/dev/null

#----------- Sample reads from reference sequence -----------

errors=2
read_length="150"
read_count=10
haplotype_count=1

echo "Generating $read_count reads of length $read_length with $errors errors"
read_dir=reads_$read_length
mkdir -p $read_dir
$BINARY_DIR/generate_reads \
    --output $read_dir \
    --max_errors $errors \
    --number_of_reads $read_count \
    --read_length $read_length \
    --number_of_haplotypes $haplotype_count \
    $ref_out > /dev/null

mv $read_dir/single_reference.fastq single_query.fq
rm -r $read_dir
