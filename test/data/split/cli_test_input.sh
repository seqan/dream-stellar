#!/bin/bash
cd split
set -Eeuo pipefail

#----------- Simulate chromosomes of various lengths -----------

SEED=${1}

i=1
for length in 210 490 420 280 4
do
    echo "Simulating chromosome with length $length"
    chr_out="chr"$i".fasta"
    mason_genome -l $length -o $chr_out -s $SEED &>/dev/null

    sed -i "s/^>.*$/>chr$i/g" $chr_out
    let i=i+1
done

cat chr*.fasta > various_chromosome_lengths.fasta
rm chr*.fasta

#----------- Simulate a single long reference sequence -----------
ref_len=10240

echo "Simulating single reference with length $ref_len"
ref_out="single_reference.fasta"
mason_genome -l $ref_len -o $ref_out -s $SEED &>/dev/null

#----------- Sample reads from reference sequence -----------

error_rate=0.025
read_length=150
read_count=10

echo "Generating $read_count reads of length $read_length with error rate $error_rate"
read_dir=reads_$read_length
mkdir -p $read_dir
generate_local_matches \
    --output $read_dir \
    --max-error-rate $error_rate \
    --num-matches $read_count \
    --min-match-length $read_length \
    --max-match-length $read_length \
    --verbose-ids \
    --ref-len $ref_len \
    --seed $SEED \
    $ref_out

mv $read_dir/single_reference.fastq single_query.fq
rm -r $read_dir
