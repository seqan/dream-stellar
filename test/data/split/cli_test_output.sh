#!/bin/bash
cd split
set -Eeuo pipefail

if [ -z "${VALIK_TMP}" ]; then
    echo "no VALIK_TMP folder given"
    exit 127
fi

mkdir -p $VALIK_TMP

#----------- Split multiple sequences of various lengths -----------

seg_input="various_chromosome_lengths.fasta"
for o in 0 20
do
    for b in 4 16
    do
        echo "Splitting the genome into $b segments that overlap by $o"
        ref_meta="multi/chromosome_"$o"overlap"$b"bins.txt"
        seg_meta="multi/"$o"overlap"$b"bins.txt"
        valik split "$seg_input" --overlap "$o" --seg-count "$b" --db-meta "$ref_meta" --seg-meta "$seg_meta"
    done
done

# avoid creating multiple identical reference metadata output files
rm multi/chromosome_0overlap4bins.txt
rm multi/chromosome_0overlap16bins.txt
rm multi/chromosome_20overlap4bins.txt
mv "$ref_meta" multi/chromosome_metadata.txt


#----------- Split and search a single reference sequence -----------

# Split parameters
seg_overlap="150"     # how much adjacent segments overlap

# Build parameters
k=13
ibf_size="32k"

# Search parameters
errors=1              # max allowed errors
pattern=50            # min local match length
pat_overlap=49        # how much adjacent patterns overlap
tau=0.75
p_max=0.25

ref_input="single_reference.fasta"
query="single_query.fq"
for b in 4 16
do
    echo "Splitting the genome into $b segments that overlap by $seg_overlap"
    ref_meta="single/ref_"$seg_overlap"overlap"$b"bins.txt"
    seg_meta="single/"$seg_overlap"overlap"$b"bins.txt"
    valik split "$ref_input" --overlap "$seg_overlap" --seg-count "$b" --db-meta "$ref_meta" --seg-meta "$seg_meta"

    for w in 13 15
    do
        echo "Creating IBF for w=$w and k=$k where segments overlap by $seg_overlap"
        index="single/"$seg_overlap"overlap"$b"bins"$w"window.ibf"
        valik build "$ref_input" --kmer "$k" --window "$w" --size "$ibf_size" --output "$index" --from-segments --ref-meta "$ref_meta" --seg-meta "$seg_meta"

        echo "Searching IBF with $errors errors"
        search_out="single/"$seg_overlap"overlap"$b"bins"$w"window"$errors"errors.gff"
        valik search --distribute --index "$index" --query "$query" --output "$search_out" --error "$errors" --pattern "$pattern" --overlap "$pat_overlap" --tau "$tau" --p_max "$p_max" --ref-meta "$ref_meta" --seg-meta "$seg_meta" --threads 1
    rm "$search_out"
    done
done

# avoid creating multiple identical reference metadata output files
rm single/ref_"$seg_overlap"overlap4bins.txt
mv "$ref_meta" single/reference_metadata.txt

rm -r $VALIK_TMP
