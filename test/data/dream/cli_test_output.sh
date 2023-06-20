#!/bin/bash
cd dream
set -Eeuo pipefail

if [ -z "${VALIK_TMP}" ]; then
    echo "no VALIK_TMP folder given"
    exit 127
fi

mkdir -p $VALIK_TMP

#----------- Split the reference genome -----------

seg_input="ref.fasta"
for o in 0 20
do
    for b in 4 16
    do
        echo "Splitting the genome into $b segments that overlap by $o"
        ref_meta="ref_meta"$o"overlap"$b"bins.txt"
        seg_meta="seg_meta"$o"overlap"$b"bins.txt"
        valik split "$seg_input" --overlap "$o" --bins "$b" --ref-meta "$ref_meta" --seg-meta "$seg_meta"
    done
done

# avoid creating multiple identical reference metadata output files
rm ref_meta0overlap4bins.txt
rm ref_meta0overlap16bins.txt
rm ref_meta20overlap4bins.txt
mv "$ref_meta" ref_meta.txt

#----------- Index and search the reference genome -----------

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

ref_input="ref.fasta"
query="query.fastq"
for b in 4 16
do
    echo "Splitting the genome into $b segments that overlap by $seg_overlap"
    ref_meta="ref_meta.txt"
    seg_meta="seg_meta"$seg_overlap"overlap"$b"bins.txt"
    valik split "$ref_input" --overlap "$seg_overlap" --bins "$b" --ref-meta "$ref_meta" --seg-meta "$seg_meta"

    for w in 13 15
    do
        echo "Creating IBF for w=$w and k=$k where segments overlap by $seg_overlap"
        index="seg_meta"$seg_overlap"overlap"$b"bins"$w"window.ibf"
        valik build "$ref_input" --kmer "$k" --window "$w" --size "$ibf_size" --output "$index" --from-segments --ref-meta "$ref_meta" --seg-meta "$seg_meta"

        echo "Searching IBF with $errors errors"
        search_out=$seg_overlap"overlap"$b"bins"$w"window"$errors"errors.gff"
        valik search --index "$index" --query "$query" --output "$search_out" --error "$errors" --pattern "$pattern" --overlap "$pat_overlap" --tau "$tau" --p_max "$p_max" --ref-meta "$ref_meta" --seg-meta "$seg_meta" --threads 1
    done
done

rm -r $VALIK_TMP
