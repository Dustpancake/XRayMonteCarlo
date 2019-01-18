#!/bin/bash

declare -i count=0
for i in $(find ./xraydata/atten_lengths/Comp -maxdepth 1 -type f \( ! -name . \) -exec echo '{}' \;); do
    ./build/run simulate 1e6 0.05 0.05 5 $i ./xraydata/e_spectra/test.txt
    sleep 0.1
    mv output.png ./composition_out/be_$count.png
    mv output.txt ./composition_out/be_$count.txt
    #mv spectrum.png ./singles/spectrum_$count.png
    count=count+1
done