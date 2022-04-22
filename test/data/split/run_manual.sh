#!/bin/bash

valik build bin_paths.txt --kmer 13 --window 15 --size 100k --output manual_test.index
valik search --index manual_test.index --query single_query.fq --output manual_test.out --error 2 --pattern 50 --overlap 49 --tau 0.75 --p_max 0.75
