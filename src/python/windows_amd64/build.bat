SET build_directory=../../../builds/python/windows_amd64
SET precompiled_directory=../../../hasomed_precompiled/smpt_rm3_msvc2015_x86_amd64_static

echo rehamove-integration-lib: Performing the build
swig -python rehamovelib.i
cl /LD /MD rehamovelib.c rehamovelib_wrap.c /Fe_rehamovelib.pyd /I "C:/Users/Agggron/AppData/Local/Programs/Python/Python37/include" /I "%precompiled_directory%/include/low-level" /I "%precompiled_directory%/include/general" /link "%precompiled_directory%/lib/libsmpt.lib" "C:/Users/Agggron/AppData/Local/Programs/Python/Python37/libs/python37.lib"

echo rehamove-integration-lib: Moving built files into the builds directory
copy rehamove.py "%build_directory%"
move rehamovelib.py "%build_directory%"
move _rehamovelib.pyd "%build_directory%"

echo rehamove-integration-lib: Cleaning up intermediate build files
del rehamovelib_wrap.c
del rehamovelib.obj
del rehamovelib_wrap.obj
del _rehamovelib.lib
del _rehamovelib.exp