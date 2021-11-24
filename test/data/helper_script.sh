#!/bin/bash
  
#w="${1}"
#e="${2}"
#p="${3}"
#o="${4}"

for w in 20 23
do
    for e in 0 1
    do
        for p in 50 100
        do
            for o in 1 40
            do
                output="8bins"$w"window"$e"error"$p"pattern"$o"overlap.out"
                #sliding_window search --index 8bins23window.ibf --query query.fq --output "$output" --error "$e" --pattern "$p" --overlap "$o"
		echo "declare_datasource (FILE ${output}
                    URL \${CMAKE_SOURCE_DIR}/test/data/${output}
                    URL_HASH SHA256="
		printf $output | sha256sum
		echo ")"
	    done
        done
    done
done
