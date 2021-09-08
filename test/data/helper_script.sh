#!/bin/bash
  
# the read IDs can not contain
e="${1}"
p="${2}"
o="${3}"

output="8bins23window"$e"error"$p"pattern"$o"overlap.out"

sliding_window search --index 8bins23window.ibf --query query.fq --output "$output" --error "$e" --pattern "$p" --overlap "$o"

printf $output | sha256sum
