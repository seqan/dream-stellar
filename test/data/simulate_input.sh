#!/bin/bash

BINARY_DIR=/home/evelin/metagenomics/raptor_data_simulation/build/bin
SEED=42 # was 20181406 before, but was hardcoded to 42 in seqan
BIN_NUMBER=8
HAPLOTYPE_COUNT=4

./split/cli_test_input.sh $BINARY_DIR $SEED

./build/cli_test_input.sh $BINARY_DIR $SEED $BIN_NUMBER $HAPLOTYPE_COUNT

./search/cli_test_input.sh $BINARY_DIR $SEED $BIN_NUMBER $HAPLOTYPE_COUNT
