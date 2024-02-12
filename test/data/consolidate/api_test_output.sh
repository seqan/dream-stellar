#!/bin/bash
cd consolidate
set -Eeuo pipefail

rm stellar_truth*.gff

execs=(stellar)
for exec in "${execs[@]}"; do
    if ! which ${exec} &>/dev/null; then
        echo "${exec} is not available"
        echo ""
        echo "make sure \"${execs[@]}\" are reachable via the \${PATH} variable"
        echo ""

        # trying to do some guessing here:
        paths+=(../../../stellar3/build/bin)

        p=""
        for pp in ${paths[@]}; do
            p=${p}$(realpath -m $pp):
        done
        echo "you could try "
        echo "export PATH=${p}\${PATH}"

        exit 127
    fi
done


errRate=0.06
ref_file=multi_seq_ref.fasta
query_file=multi_seq_query.fasta
minLen=50

stellar -e $errRate -l $minLen -o stellar_truth.gff $ref_file $query_file > /dev/null

for d in 3 8 13
do
        for n in 3 9 12
        do
                stellar -e $errRate -l $minLen -o stellar_truth_num${n}_dis${d}.gff $ref_file $query_file --numMatches $n --disableThresh $d > /dev/null
        done
done

rm stellar.disabled.fasta
