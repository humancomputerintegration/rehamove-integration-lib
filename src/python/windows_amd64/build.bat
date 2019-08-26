REM Set paths to the locations of the .c file, Hasomed's precompiled files, and where we want our built files to go.
SET source_directory=..
SET precompiled_directory=../../../hasomed_precompiled/smpt_rm3_msvc2015_x86_amd64_static
SET source_to_build_directory=windows_amd64

REM Performing the build, Python3 on Windows, using x64 Native Tools Command Prompt for VS 2017 

SET python3_build_directory=../../../builds/python/windows_amd64
SET source_to_python3_build_directory=../../builds/python/windows_amd64

swig -python "%source_directory%/rehamovelib.i"
cl /LD /MD "%source_directory%/rehamovelib.c" "%source_directory%/rehamovelib_wrap.c" /Fe_rehamovelib.pyd /I "C:/Users/Agggron/AppData/Local/Programs/Python/Python37/include" /I "%precompiled_directory%/include/low-level" /I "%precompiled_directory%/include/mid-level" /I "%precompiled_directory%/include/general" /link "%precompiled_directory%/lib/libsmpt.lib" "C:/Users/Agggron/AppData/Local/Programs/Python/Python37/libs/python37.lib"

REM Moving built files into builds directory, and cleaning up files.
move _rehamovelib.pyd "%python3_build_directory%"
del rehamovelib.obj
del rehamovelib_wrap.obj
del _rehamovelib.lib
del _rehamovelib.exp
cd "%source_directory%"
copy rehamove.py "%source_to_python3_build_directory%"
move rehamovelib.py "%source_to_python3_build_directory%"
del rehamovelib_wrap.c
cd "%source_to_build_directory%"

REM Performing the build, Python2 on Windows, using x64 Native Tools Command Prompt for VS 2017 

SET python2_build_directory=../../../builds/python2/windows_amd64
SET source_to_python2_build_directory=../../builds/python2/windows_amd64

swig -python "%source_directory%/rehamovelib.i"
cl /LD /MD "%source_directory%/rehamovelib.c" "%source_directory%/rehamovelib_wrap.c" /Fe_rehamovelib.pyd /I "C:/Python27/include" /I "%precompiled_directory%/include/low-level" /I "%precompiled_directory%/include/mid-level" /I "%precompiled_directory%/include/general" /link "%precompiled_directory%/lib/libsmpt.lib" "C:/Python27/libs/python27.lib"

REM Moving built files into builds directory, and cleaning up files.
move _rehamovelib.pyd "%python2_build_directory%"
del rehamovelib.obj
del rehamovelib_wrap.obj
del _rehamovelib.lib
del _rehamovelib.exp
cd "%source_directory%"
copy rehamove.py "%source_to_python2_build_directory%"
move rehamovelib.py "%source_to_python2_build_directory%"
del rehamovelib_wrap.c
cd "%source_to_build_directory%"

REM Build complete.