pushd build

cmake ..
make install -j 4

ARCH_STR="x86_64-linux-gnu-11.4.0"

export PATH=$PATH:${PWD}/${ARCH_STR}/bin/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PWD}/${ARCH_STR}/lib/

popd