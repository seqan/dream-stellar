#!/bin/bash

wget http://ftp.flybase.net/genomes/Drosophila_melanogaster/dmel_REFSEQ/fasta/dmel-all-chromosome-r6.32.fasta.gz
gunzip dmel-all-chromosome-r6.32.fasta.gz

# only keep chromosomal sequences
awk '{ if ((NR>1)&&($0~/^>/)) { printf("\n%s", $0); } else if (NR==1) { printf("%s", $0); } else { printf("\t%s", $0); } }' dmel-all-chromosome-r6.32.fasta | grep -Ff chr_IDs - | tr "\t" "\n" > dmel-chr.fasta
rm dmel-all-chromosome-r6.32.fasta

# short and simple chromosome IDs
cat dmel-chr.fasta | awk -F 'type=' '{print $1}' > dmel.fasta
rm dmel-chr.fasta
