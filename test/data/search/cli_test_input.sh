#!/bin/bash
cd search
set -Eeuo pipefail

SEED="${1}"
BIN_NUMBER="${2}"
ERRORS=2
READ_LENGTHS="150 250"
READ_COUNT=16
HAPLOTYPE_COUNT="${3}"

for read_length in $READ_LENGTHS
do
    echo "Generating $READ_COUNT reads of length $read_length with $ERRORS errors"
    read_dir=reads_$read_length
    mkdir -p $read_dir
    generate_reads \
        --output $read_dir \
        --max_errors $ERRORS \
        --number_of_reads $READ_COUNT \
        --read_length $read_length \
        --number_of_haplotypes $HAPLOTYPE_COUNT \
        $(seq -f "../build/bin_%0${#BIN_NUMBER}g.fasta" 0 1 $((BIN_NUMBER-1)))

    cat $read_dir/*.fastq >> all
    rm -rf $read_dir
done

# Create unique read IDs
awk '{if( (NR-1)%4 ) print; else printf("@read-%d\n",cnt++)}' all > query.fq
rm all

