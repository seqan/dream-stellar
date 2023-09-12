#!/bin/bash
cd "$(dirname "$0")"
set -Eeuo pipefail

if ! which valik 2> /dev/null; then
    echo "valik not found. please compile it and add its path to the PATH variable"
    exit 255
fi

export VALIK_TMP=tmp/valik/my_dir
#export VALIK_STELLAR=echo
#export VALIK_MERGE=echo
#
#echo "### Running valik split ###"
#./split/cli_test_output.sh
#
#echo "### Running valik build ###"
#./build/cli_test_output.sh
#
#echo "### Running valik search ###"
#./search/cli_test_output.sh
#
#echo "### Running valik consolidate ###"
#./consolidate/cli_test_output.sh

export VALIK_STELLAR=stellar
export VALIK_MERGE=cat

echo "### Running distributed DREAM-Stellar ###"
./dream/cli_test_output.sh

echo "### Finished ###"