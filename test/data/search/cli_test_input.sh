#!/bin/bash

cd search

set -e

BINARY_DIR="${1}"
SEED="${2}"
BIN_NUMBER="${3}"
ERRORS=2
READ_LENGTHS="100 150 250"
READ_COUNT=32
HAPLOTYPE_COUNT="${4}"

for read_length in $READ_LENGTHS
do
    echo "Generating $READ_COUNT reads of length $read_length with $ERRORS errors"
    mkdir -p reads
    $BINARY_DIR/generate_reads \
        --output reads \
        --max_errors $ERRORS \
        --number_of_reads $READ_COUNT \
        --read_length $read_length \
        --number_of_haplotypes $HAPLOTYPE_COUNT \
        $(seq -f "../build/bin_%0${#BIN_NUMBER}g.fasta" 0 1 $((BIN_NUMBER-1))) > /dev/null
    cat reads/*.fastq > reads/all
    mv reads/all query.fq
    rm -r reads
done
