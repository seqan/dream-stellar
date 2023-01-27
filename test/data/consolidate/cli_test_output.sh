#!/bin/bash

rm dream_consolidated.gff

../../../debug/bin/valik consolidate -i dream_all.gff --meta-path reference_metadata.tsv -o dream_consolidated.gff

rm *_*_*.gff
rm *_*_*.stdout
