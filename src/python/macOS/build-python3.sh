#!/bin/bash 
build_directory=../../../builds/python/macOS
precompiled_directory=../../../hasomed_precompiled/smpt_rm3_clang_darwin_x86_amd64_static
python_include_path=/usr/local/Cellar/python/3.7.4/Frameworks/Python.framework/Versions/3.7/include/python3.7m/

echo "Setting up your environment, check the lines below for consistency:"
echo "  1. Your python executable was found at $python_executable_path"
echo "  2. Your python include path (where Python.h is) is $python_include_path"
echo "  3. Creating all needed directories now."
mkdir -p $build_directory
echo "  4. Checking if you have the Hasomed precompiled libs"
[ ! -d $precompiled_directory ] && echo "Directory $precompiled_directory DOES NOT exists. Seems like you do not have the Hasomed's precompiled library, you need that to build our library. Please check instructions at https://lab.plopes.org/rehalib.html"

echo "rehamove-integration-lib: Performing the build (Python on MacOS AMD64)"
swig -python rehamovelib.i;

echo "rehamove-integration-lib: Compiling C sources"
gcc -c rehamovelib.c -fPIC -I $precompiled_directory/include/low-level/ -I $precompiled_directory/include/general/;

echo "rehamove-integration-lib: Compiling SWIG-generated wrapper"
gcc -c rehamovelib_wrap.c -fPIC -I $precompiled_directory/include/low-level/ -I $precompiled_directory/include/general/ -I $python_include_path ;

echo "rehamove-integration-lib: Linking to generate shared library"
ld -dylib -bundle -flat_namespace -undefined suppress rehamovelib.o rehamovelib_wrap.o -o _rehamovelib.so -L  $precompiled_directory/lib/ -lsmpt

echo "rehamove-integration-lib: Moving built files into the builds directory"
cp rehamove.py $build_directory
mv rehamovelib.py $build_directory
mv _rehamovelib.so $build_directory

echo "rehamove-integration-lib: Cleaning up intermediate build files"
rm *.o
rm rehamovelib_wrap.c
