#!/bin/bash 
build_directory=../../../builds/python/linux_ARM
precompiled_directory=../../../hasomed_precompiled/smpt_rm3_gcc_linux_arm_eabihf_static

echo "rehamove-integration-lib: Performing the build (Python on Linux ARM)"
swig -python rehamovelib.i;

echo "rehamove-integration-lib: Compiling C sources"
gcc -c rehamovelib.c -fPIC -I $precompiled_directory/include/low-level/ -I $precompiled_directory/include/general/;

echo "rehamove-integration-lib: Compiling SWIG-generated wrapper"
gcc -c rehamovelib_wrap.c -fPIC -I $precompiled_directory/include/low-level/ -I $precompiled_directory/include/general/ -I /usr/include/python2.7 ;

echo "rehamove-integration-lib: Linking to generate shared library"
ld -shared rehamovelib.o rehamovelib_wrap.o -o _rehamovelib.so -L $precompiled_directory/lib/ -lsmpt -L /usr/lib/gcc/arm-linux-gnueabihf/6 -lgcc

echo "rehamove-integration-lib: Moving built files into the builds directory"
cp rehamove.py $build_directory
mv rehamovelib.py $build_directory
mv _rehamovelib.so $build_directory

echo "rehamove-integration-lib: Cleaning up intermediate build files"
rm *.o
rm rehamovelib_wrap.c