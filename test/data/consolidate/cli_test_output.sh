#!/bin/bash
cd consolidate
set -Eeuo pipefail

rm -f *_*_dream_consolidated.gff

for bin in 8 16
do
    for minLen in 50
    do
        valik consolidate --input ${bin}bins${minLen}overlap_dream_all.gff \
                                             --ref-meta ${bin}bins${minLen}overlap_reference_metadata.tsv \
                                             --output ${bin}bins${minLen}overlap_dream_consolidated.gff
    done
done
