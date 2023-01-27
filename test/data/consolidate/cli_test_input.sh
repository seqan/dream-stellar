#!/bin/bash

STELLAR=/home/evelin/DREAM-Stellar/dream_stellar/build/bin/stellar

# ============================================================
# Varying error rates
# ============================================================

rm *_*_*.gff
rm *_*_*.stdout
rm full.gff
rm full.stdout
rm segment_metadata.tsv
rm reference_metadata.tsv

errRate=0.05
minLen=50
ref_file=multi_seq_ref.fasta
query_file=query_e${errRate}.fasta

call_stellar () {
   ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest $1 \
              --segmentBegin $2 --segmentEnd $3 \
              --suppress-runtime-printing \
              -o $1_$2_$3.gff \
              $ref_file $query_file > 0_$1_$2.stdout
}

${STELLAR} -e $errRate -l $minLen -v --suppress-runtime-printing -o full.gff $ref_file $query_file > full.stdout

for bin in 4 16
do
        valik split $ref_file --reference-output reference_metadata.tsv --segment-output segment_metadata.tsv --bins 16 --overlap $minLen

        while read line; do
                bin=$(echo "$line" | cut -f1)
                seq_ind=$(echo "$line" | cut -f2)
                start=$(echo "$line" | cut -f3)
                len=$(echo "$line" | cut -f4)
                end=$(expr $start + $len)
                echo bin=$bin seq_ind=$seq_ind start=$start len=$len end=$end

                call_stellar $seq_ind $start $end
        done < segment_metadata.tsv

        cat *_*_*_$bin.gff > dream_all_$bin.gff
done