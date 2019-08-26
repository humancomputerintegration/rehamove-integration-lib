#!/bin/bash 
SOURCE_DIRECTORY=..
PRECOMPILED_LIBRARY=../../hasomed_precompiled/smpt_rm3_gcc_linux_x86_amd64_static
SOURCE_TO_BUILD_DIRECTORY=linux_amd64
SOURCE_TO_PYTHON2_DIRECTORY=../../builds/python2/linux_amd64
SOURCE_TO_PYTHON3_DIRECTORY=../../builds/python/linux_amd64

echo "Starting build... python_linux_amd64 v1.6"

cd "$SOURCE_DIRECTORY"

echo "SWIGing."
swig -python rehamovelib.i

echo "Compiling C sources from rehamovelib."
gcc -c rehamovelib.c -fPIC -I "$PRECOMPILED_LIBRARY/include/low-level/" -I "$PRECOMPILED_LIBRARY/include/mid-level/" -I "$PRECOMPILED_LIBRARY/include/general/"

echo "Compiling Python rehamovelib wrapper."
gcc -c rehamovelib_wrap.c -fPIC -I "$PRECOMPILED_LIBRARY/include/low-level/" -I "$PRECOMPILED_LIBRARY/include/mid-level/" -I "$PRECOMPILED_LIBRARY/include/general/" -I /usr/include/python2.7

echo "Linking to generate _rehamovelib.so shared library."
ld -shared rehamovelib.o rehamovelib_wrap.o -o _rehamovelib.so -L "$PRECOMPILED_LIBRARY/lib/" -lsmpt

echo "Build finished."

echo "Moving files for Python2 build."
mv _rehamovelib.so "$SOURCE_TO_PYTHON2_DIRECTORY"
mv rehamovelib.py "$SOURCE_TO_PYTHON2_DIRECTORY"
cp rehamove.py "$SOURCE_TO_PYTHON2_DIRECTORY"
rm rehamovelib.o
rm rehamovelib_wrap.c
rm rehamovelib_wrap.o
cd "$SOURCE_TO_BUILD_DIRECTORY"


echo "Repeating for Python3"

cd "$SOURCE_DIRECTORY"

echo "SWIGing."
swig -python rehamovelib.i

echo "Compiling C sources from rehamovelib."
gcc -c rehamovelib.c -fPIC -I "$PRECOMPILED_LIBRARY/include/low-level/" -I "$PRECOMPILED_LIBRARY/include/mid-level/" -I "$PRECOMPILED_LIBRARY/include/general/"

echo "Compiling Python rehamovelib wrapper."
gcc -c rehamovelib_wrap.c -fPIC -I "$PRECOMPILED_LIBRARY/include/low-level/" -I "$PRECOMPILED_LIBRARY/include/mid-level/" -I "$PRECOMPILED_LIBRARY/include/general/" -I /usr/include/python3.6

echo "Linking to generate _rehamovelib.so shared library."
ld -shared rehamovelib.o rehamovelib_wrap.o -o _rehamovelib.so -L "$PRECOMPILED_LIBRARY/lib/" -lsmpt

echo "Build finished."

echo "Moving files for Python3 build."
mv _rehamovelib.so "$SOURCE_TO_PYTHON3_DIRECTORY"
mv rehamovelib.py "$SOURCE_TO_PYTHON3_DIRECTORY"
cp rehamove.py "$SOURCE_TO_PYTHON3_DIRECTORY"
rm rehamovelib.o
rm rehamovelib_wrap.c
rm rehamovelib_wrap.o

cd "$SOURCE_TO_BUILD_DIRECTORY"
