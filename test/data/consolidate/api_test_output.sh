#!/bin/bash
cd consolidate
set -Eeuo pipefail

rm stellar_truth*.gff

errRate=0.06
ref_file=multi_seq_ref.fasta
query_file=multi_seq_query.fasta
minLen=50

/home/evelin/DREAM-Stellar/stellar/build/bin/stellar -e $errRate -l $minLen -o stellar_truth.gff $ref_file $query_file > /dev/null

for n in 3 5 9
do
        /home/evelin/DREAM-Stellar/stellar/build/bin/stellar -e $errRate -l $minLen -o stellar_truth_num${n}.gff $ref_file $query_file --numMatches $n> /dev/null
done
