#!/bin/bash
cd consolidate
set -Eeuo pipefail

# ============================================================
# Varying error rates
# ============================================================

rm -f *_full.gff
rm -f *bins*overlap_segment_metadata.tsv
rm -f *bins*overlap_reference_metadata.tsv

errRate=0.05
ref_file=multi_seq_ref.fasta
query_file=query_e${errRate}.fasta
call_stellar () {
   stellar -e $errRate -l $2 -v --sequenceOfInterest $3 \
              --segmentBegin $4 --segmentEnd $5 \
              --suppress-runtime-printing \
              -o $1bins$2overlap$3index$4start$5end.gff \
              $ref_file $query_file > /dev/null
        # $1bins$2overlap$3index$4start$5end.stdout
}

for minLen in 10 50
do
        stellar -e $errRate -l $minLen -v --suppress-runtime-printing -o ${minLen}overlap_full.gff $ref_file $query_file > /dev/null

        for bin in 8 16
        do
                valik split $ref_file --reference-output ${bin}bins${minLen}overlap_reference_metadata.tsv \
                                      --segment-output ${bin}bins${minLen}overlap_segment_metadata.tsv \
                                      --bins $bin --overlap $minLen

                while read line; do
                        current_bin=$(echo "$line" | cut -f1)
                        seq_ind=$(echo "$line" | cut -f2)
                        start=$(echo "$line" | cut -f3)
                        len=$(echo "$line" | cut -f4)
                        end=$(expr $start + $len)
                        echo current_bin=$current_bin seq_ind=$seq_ind start=$start len=$len end=$end

                        call_stellar $bin $minLen $seq_ind $start $end
                done < ${bin}bins${minLen}overlap_segment_metadata.tsv

                cat ${bin}bins${minLen}overlap*index*start*end.gff > ${bin}bins${minLen}overlap_dream_all.gff

                rm ${bin}bins${minLen}overlap*index*start*end.gff
                # rm ${bin}bins${minLen}overlap*index*start*end.stdout
                rm ${bin}bins${minLen}overlap_segment_metadata.tsv
        done
done
