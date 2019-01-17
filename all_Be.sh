#!/bin/bash

declare -i count=0
for i in $(find ./xraydata/atten_lengths/Comp -maxdepth 1 -type f \( ! -name . \) -exec echo '{}' \;); do
    ./build/run simulate 1e7 1 1 100 $i ./xraydata/e_spectra/test.txt
    sleep 0.1
    mv output.png ./composition_out/comp_$count.png
    mv output.txt ./composition_out/comp_$count.txt
    count=count+1
done