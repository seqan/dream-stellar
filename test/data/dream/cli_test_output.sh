#!/bin/bash
cd dream
set -Eeuo pipefail

if [ -z "${VALIK_TMP}" ]; then
    echo "no VALIK_TMP folder given"
    exit 127
fi

mkdir -p $VALIK_TMP

#----------- Index and search the reference genome -----------

# Split parameters
seg_overlap="150"     # how much adjacent segments overlap

# Build parameters
k=13
ibf_size="32k"

# Search parameters
pattern=50            # min local match length
pat_overlap=49        # how much adjacent patterns overlap

ref_input="ref.fasta"
query="query.fastq"
for b in 4 16
do
    echo "Splitting the genome into $b segments that overlap by $seg_overlap"
    ref_meta="ref_meta.txt"
    seg_meta="seg_meta"$seg_overlap"overlap"$b"bins.txt"
    valik split "$ref_input" --overlap "$seg_overlap" --seg-count "$b" --ref-meta "$ref_meta" --seg-meta "$seg_meta"

    for w in 13 15
    do
        echo "Creating IBF for w=$w and k=$k where segments overlap by $seg_overlap"
        index=$b"bins"$w"window.ibf"
        valik build "$ref_input" --kmer "$k" --window "$w" --size "$ibf_size" --output "$index" --from-segments --ref-meta "$ref_meta" --seg-meta "$seg_meta"

        for e in 1
        do
            echo "Searching IBF with $e errors"
            dist_out=$b"bins"$w"window"$e"error.gff"
            #local_out="local"$b"bins"$w"window"$e"error.gff"
            valik search --index "$index" --query "$query" --output "$dist_out" --error "$e" --pattern "$pattern" --overlap "$pat_overlap" --ref-meta "$ref_meta" --seg-meta "$seg_meta"
            #valik search --shared-memory --index "$index" --query "$query" --output "$local_out" --error "$e" --pattern "$pattern" --overlap "$pat_overlap" --ref-meta "$ref_meta" --seg-meta "$seg_meta"
        done

        rm $VALIK_TMP/*
    done
done

#stellar_out="stellar.gff"
#stellar ref.fasta query.fasta -e 0.02 -l 50 -o $stellar_out

rm -r $VALIK_TMP
