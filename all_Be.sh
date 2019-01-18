#!/bin/bash

declare -i count=0
for i in $(find ./xraydata/atten_lengths/Be -maxdepth 1 -type f \( ! -name . \) -exec echo '{}' \;); do
    ./build/run simulate 1e7 1 1 100 $i ./xraydata/e_spectra/test.txt
    sleep 0.1
    mv output.png ./bashscript_out/be_$count.png
    mv output.txt ./bashscript_out/be_$count.txt
    #mv spectrum.png ./singles/spectrum_$count.png
    count=count+1
done