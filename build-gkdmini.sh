#!/bin/sh
rm -r build
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="/opt/gkdminiplus-toolchain/usr/share/buildroot/toolchainfile.cmake" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS_RELEASE="-O2 -DEGL_NO_X11=1" -DCMAKE_EXE_LINKER_FLAGS="-s" -DCMAKE_INTERPROCEDURAL_OPTIMIZATION="TRUE" -DBUILD_RECORDER=0 -DUSE_SQLITE3=0 -DUSE_SYSTEM_ENET=0 -DUSE_CRYPTO_OPENSSL=0 -DUSE_SYSTEM_SQUISH=0 -DUSE_DNS_C=1 -DUSE_MOJOAL=1 -DUSE_WIIUSE=0  ..
make -j8
cd ..
