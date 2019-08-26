SET precompiled_directory=../../../hasomed_precompiled/smpt_rm3_msvc2015_x86_amd64_static
SET python3_build_directory=../../../builds/python/windows_amd64
SET python2_build_directory=../../../builds/python2/windows_amd64

echo rehamove-integration-lib: Performing the build (Python3 on Windows)
swig -python rehamovelib.i
cl /LD /MD rehamovelib.c rehamovelib_wrap.c /Fe_rehamovelib.pyd /I "C:/Users/Agggron/AppData/Local/Programs/Python/Python37/include" /I "%precompiled_directory%/include/low-level" /I "%precompiled_directory%/include/general" /link "%precompiled_directory%/lib/libsmpt.lib" "C:/Users/Agggron/AppData/Local/Programs/Python/Python37/libs/python37.lib"

echo rehamove-integration-lib: Moving built files into the builds directory and cleaning up files.
move _rehamovelib.pyd "%python3_build_directory%"
copy rehamove.py "%python3_build_directory%"
move rehamovelib.py "%python3_build_directory%"
del rehamovelib.obj
del rehamovelib_wrap.obj
del _rehamovelib.lib
del _rehamovelib.exp
del rehamovelib_wrap.c


echo rehamove-integration-lib: Performing the build (Python2 on Windows)
swig -python rehamovelib.i
cl /LD /MD rehamovelib.c rehamovelib_wrap.c /Fe_rehamovelib.pyd /I "C:/Python27/include" /I "%precompiled_directory%/include/low-level" /I "%precompiled_directory%/include/general" /link "%precompiled_directory%/lib/libsmpt.lib" "C:/Python27/libs/python27.lib"

echo rehamove-integration-lib: Moving built files into the builds directory and cleaning up files.
move _rehamovelib.pyd "%python2_build_directory%"
copy rehamove.py "%python2_build_directory%"
move rehamovelib.py "%python2_build_directory%"
del rehamovelib.obj
del rehamovelib_wrap.obj
del _rehamovelib.lib
del _rehamovelib.exp
del rehamovelib_wrap.c

echo rehamove-integration-lib: Build complete.