#!/bin/bash
cd consolidate
set -Eeuo pipefail

rm -f *_full.gff
rm -f *bins*overlap_segment_metadata.tsv
rm -f *bins*overlap_reference_metadata.tsv

errRate=0.06
ref_file=multi_seq_ref.fasta
query_file=query_e${errRate}.fasta
minLen=50

stellar -e $errRate -l $minLen -o stellar_truth.gff $ref_file $query_file > /dev/null

for bin in 8 16
do
        valik split $ref_file --out ${bin}bins${minLen}overlap_reference_metadata.tsv --seg-count $bin --overlap $minLen

        #!TODO: read until $
        while read -r bin_id id start len;
        do
                end=$(echo $start + $len | bc)
                stellar -e $errRate -l $minLen -o multi_seq_ref_${id}_${start}_${len}.gff \
                        --sequenceOfInterest $id --segmentBegin $start \
                        --segmentEnd $end $ref_file $query_file > /dev/null

        done < ${bin}bins${minLen}overlap_segment_metadata.tsv

        rm ${bin}bins${minLen}overlap_segment_metadata.tsv

        cat multi_seq_ref_*.gff > ${bin}bins${minLen}overlap_dream_all.gff
        rm multi_seq_ref_*
done
