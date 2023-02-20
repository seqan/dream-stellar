#!/bin/bash
cd search
set -Eeuo pipefail

mkdir -p $VALIK_TMP

tau=0.75
p_max=0.75

for w in 19 23
do
    for e in 0 1
    do
        for p in 50 100
        do
            for o in 1 40
            do
                echo "Searching the IBF (w=$w, k=19) for an approximate local match of length $p with $e error(s)"
                echo "Potential matches overlap by $o bp"
                output="8bins"$w"window"$e"error"$p"pattern"$o"overlap.gff"
                valik search --index ../build/8bins${w}window.ibf --query query.fq --output "$output" --error "$e" --pattern "$p" --overlap "$o" --tau "$tau" --p_max "$p_max" --threads 1
	        done
        done
    done
done
