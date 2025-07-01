#!/bin/bash
cd prepare
set -Eeuo pipefail

ref_input="../dream/ref.fasta"
p=50
for shape in "11111111" "111110011111"
do
    echo "Creating IBF for shape $shape"
    index="s${shape}.ibf"
    mkdir -p "s$shape"
    
    if [ -f "s${shape}/s${shape}_ref.0.header"  ];then   
        rm s${shape}/*
    fi

    dream-stellar build "$ref_input" --shape $shape --pattern "$p" --write-out --kmer-count-min 0 --kmer-count-max 254 \
                            --output "$index" --fast --without-parameter-tuning --seg-count 8 

    for i in ref.*.header; do mv $i s$shape/s${shape}_${i}; done
    for i in ref.*.minimiser; do mv $i s$shape/s${shape}_${i}; done
done

mkdir -p bins
if [ -f "bins/ref_0.fasta" ];then
    rm bins/*
fi
mv ../dream/ref_*.fasta bins/
