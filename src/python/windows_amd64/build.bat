echo Performing the build
swig -python rehamovelib.i
cl /LD /MD rehamovelib.c rehamovelib_wrap.c /Fe_rehamovelib.pyd /I "C:/Users/Agggron/AppData/Local/Programs/Python/Python37/include" /I ../../../hasomed_precompiled/smpt_rm3_msvc2015_x86_amd64_static/include/low-level /I ../../../hasomed_precompiled/smpt_rm3_msvc2015_x86_amd64_static/include/general /link ../../../hasomed_precompiled/smpt_rm3_msvc2015_x86_amd64_static/lib/libsmpt.lib "C:/Users/Agggron/AppData/Local/Programs/Python/Python37/libs/python37.lib"

echo Moving built files into the builds directory
copy "rehamove.py" "../../../builds/python/windows_amd64/"
move "rehamovelib.py" "../../../builds/python/windows_amd64/"
move "_rehamovelib.pyd" "../../../builds/python/windows_amd64/"

echo Cleaning up intermediate build files
del rehamovelib_wrap.c
del rehamovelib.obj
del rehamovelib_wrap.obj
del _rehamovelib.lib
del _rehamovelib.exp