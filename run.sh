cd build
make clean
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
make
./run