#!/bin/bash

declare -i count=0
for i in $(find ./xraydata/atten_lengths/Be -maxdepth 1 -type f \( ! -name . \) -exec echo '{}' \;); do
    #./build/run simulate 1e4 1 1 100 $i ./xraydata/e_spectra/test.txt
    mv ./build/output.png ./bashscript_out/be_$count.png
    mv ./build/output.txt ./bashscript_out/be_$count.txt
    count=count+1
done