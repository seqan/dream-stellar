#!/bin/bash

wget http://ftp.flybase.net/genomes/Drosophila_melanogaster/dmel_REFSEQ/fasta/dmel-all-chromosome-r6.32.fasta.gz
gunzip dmel-all-chromosome-r6.32.fasta.gz

# remove scaffolds
sed -i -e '/Scaffold/{N;d;}' dmel-all-chromosome-r6.32.fasta
# remove contigs
sed -i -e '/>211/{N;d;}' dmel-all-chromosome-r6.32.fasta
# remove mitochondrial DNA
sed -i -e '/mitochondrion/{N;d;}' dmel-all-chromosome-r6.32.fasta
# remove ribosomal DNA
sed -i -e '/rDNA/{N;d;}' dmel-all-chromosome-r6.32.fasta

# short and simple chromosome IDs
cat dmel-all-chromosome-r6.32.fasta | awk -F 'type=' '{print $1}' > dmel.fasta
rm dmel-all-chromosome-r6.32.fasta
