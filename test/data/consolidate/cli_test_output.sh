#!/bin/bash

rm *_*_dream_consolidated.gff

for bin in 8 16
do
    for minLen in 10 50
    do
        valik consolidate --input ${bin}bins${minLen}overlap_dream_all.gff \
                                             --meta-path ${bin}bins${minLen}overlap_reference_metadata.tsv \
                                             --output ${bin}bins${minLen}overlap_dream_consolidated.gff

        rm ${bin}bins${minLen}overlap_reference_metadata.tsv
    done
done
