#!/bin/bash

cd search

for w in 20 23
do
    for e in 0 1
    do
        for p in 50 100
        do
            for o in 1 40
            do
                echo "Searching the IBF (w=$w, k=20) for an approximate local match of length $p with $e error(s)"
                echo "Potential matches overlap by $o bp"
                output="8bins"$w"window"$e"error"$p"pattern"$o"overlap.out"
                valik search --index ../build/8bins${w}window.ibf --query query.fq --output "$output" --error "$e" --pattern "$p" --overlap "$o"
	        done
        done
    done
done
