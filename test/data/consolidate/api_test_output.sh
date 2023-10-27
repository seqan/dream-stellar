#!/bin/bash
cd consolidate
set -Eeuo pipefail

rm stellar_truth*.gff

errRate=0.06
ref_file=multi_seq_ref.fasta
query_file=multi_seq_query.fasta
minLen=50

stellar -e $errRate -l $minLen -o stellar_truth.gff $ref_file $query_file > /dev/null

for d in 7 9 10 12
do
        for n in 3 5 9
        do
                stellar -e $errRate -l $minLen -o stellar_truth_disable${d}_num${n}.gff $ref_file $query_file --disableThresh $d --numMatches $n> /dev/null
        done
done

rm stellar.disabled.fasta
