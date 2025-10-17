#!/bin/bash
cd split
set -Eeuo pipefail

if [ -z "${VALIK_TMP}" ]; then
    echo "no VALIK_TMP folder given"
    exit 127
fi

mkdir -p $VALIK_TMP

#----------- Split and search a single reference sequence -----------

# Build parameters
k=13
ibf_size="32k"

# Search parameters
errors=1              # max allowed errors
pattern=50            # min local match length

ref_input="single_reference.fasta"
query="single_query.fasta"
for b in 4 16
do
    for w in 13 15
    do
        echo "Creating IBF for w=$w and k=$k where segments overlap by $pattern"
        index="single/"$pattern"overlap"$b"bins"$w"window.ibf"
        dream-stellar build "$ref_input" --pattern "$pattern" --seg-count "$b" --kmer "$k" --window "$w" --size "$ibf_size" \
                                 --output "$index" --without-parameter-tuning --verbose

        echo "Searching IBF with $errors errors"
        search_out="single/"$pattern"overlap"$b"bins"$w"window"$errors"errors.gff"
        error_rate=$(echo $errors/$pattern| bc -l )
        dream-stellar search --distribute --index "$index" --query "$query" --output "$search_out" --error-rate "$error_rate" \
                     --query-every 1 --threads 1 --very-verbose --cart-max-capacity 3 --max-queued-carts 10 --bin-cutoff 0.5
        mkdir -p $VALIK_TMP

    rm "$search_out"    # only look at .gff.out
    done
done

rm single/*.arg
rm -r $VALIK_TMP stellar.disabled.fasta
rm fn_err_conf*.bin
