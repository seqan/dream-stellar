#!/bin/bash
cd consolidate
set -Eeuo pipefail

# ============================================================
# Varying error rates
# ============================================================

rm -f *_full.gff
rm -f *bins*overlap_segment_metadata.tsv
rm -f *bins*overlap_reference_metadata.tsv

errRate=0.06
ref_file=multi_seq_ref.fasta
query_file=query_e${errRate}.fasta

for minLen in 50
do
        stellar -e $errRate -l $minLen -v -o ${minLen}overlap_full.gff $ref_file $query_file > /dev/null

        for bin in 8 16
        do
                valik split $ref_file --db-meta ${bin}bins${minLen}overlap_reference_metadata.tsv \
                                      --seg-meta ${bin}bins${minLen}overlap_segment_metadata.tsv \
                                      --seg-count $bin --overlap $minLen

                valik build --from-segments $ref_file --seg-meta ${bin}bins${minLen}overlap_segment_metadata.tsv \
                --ref-meta ${bin}bins${minLen}overlap_reference_metadata.tsv \
                --window 15 --kmer 13 --output ${bin}index.ibf --size 10k

                errors=$(echo "($errRate*$minLen+0.5)/1;" | bc)
                valik search --index ${bin}index.ibf --query $query_file --pattern $minLen --error $errors \
                --output ${bin}bins${minLen}overlap_dream_all.gff --ref-meta ${bin}bins${minLen}overlap_reference_metadata.tsv \
                --seg-meta ${bin}bins${minLen}overlap_segment_metadata.tsv

                rm ${bin}index.ibf
                rm ${bin}bins${minLen}overlap_segment_metadata.tsv
        done
done
