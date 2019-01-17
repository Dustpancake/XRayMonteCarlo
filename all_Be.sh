#!/bin/bash

declare -i count=0
for i in $(find ./xraydata/atten_lengths/Comp -maxdepth 1 -type f \( ! -name . \) -exec echo '{}' \;); do
    ./build/run single 1e7 1 $i ./xraydata/e_spectra/test.txt
    sleep 0.1
    mv output.png ./singles/single_$count.png
    mv output.txt ./singles/single_$count.txt
    count=count+1
done