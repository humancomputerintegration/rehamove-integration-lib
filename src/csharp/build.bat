SET build_directory=../../builds/csharp/
SET precompiled_directory=../../hasomed_precompiled/smpt_rm3_msvc2015_x86_amd64_static

echo rehamove-integration-lib: Performing the build (C# on Windows)
swig -csharp rehamovelib.i
cl /LD /MD rehamovelib.c rehamovelib_wrap.c /Ferehamovelib.dll /I "%precompiled_directory%/include/low-level/" /I "%precompiled_directory%/include/general" /link "%precompiled_directory%/lib/libsmpt.lib"

echo rehamove-integration-lib: Moving built files into the builds directory
move rehamovelib.dll "%build_directory%"

echo rehamove-integration-lib: Cleaning up intermediate build files
del rehamovelib_wrap.c
del rehamovelib.obj
del rehamovelib_wrap.obj
del rehamovelib.lib
del rehamovelib.exp

echo rehamove-integration-lib: Adding in namespace lines for files used in UnityRehamove.dll

echo }>backspace.cs

copy rehamovelib.cs temp.cs
echo namespace UnityRehamove {>rehamovelib.cs
type temp.cs >> rehamovelib.cs
type backspace.cs >> rehamovelib.cs

copy rehamovelibPINVOKE.cs temp.cs
echo namespace UnityRehamove {>rehamovelibPINVOKE.cs
type temp.cs >> rehamovelibPINVOKE.cs
type backspace.cs >> rehamovelibPINVOKE.cs

copy RehamoveDevice.cs temp.cs
echo namespace UnityRehamove {>RehamoveDevice.cs
type temp.cs >> RehamoveDevice.cs
type backspace.cs >> RehamoveDevice.cs

copy SWIGTYPE_p_Smpt_device.cs temp.cs
echo namespace UnityRehamove {>SWIGTYPE_p_Smpt_device.cs
type temp.cs >> SWIGTYPE_p_Smpt_device.cs
type backspace.cs >> SWIGTYPE_p_Smpt_device.cs

del temp.cs
del backspace.cs