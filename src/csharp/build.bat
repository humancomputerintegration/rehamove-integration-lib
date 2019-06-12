swig -csharp rehamovelib.i
cl /LD /MD rehamovelib.c rehamovelib_wrap.c /Ferehamovelib.dll /I ../../hasomed_precompiled/smpt_rm3_msvc2015_x86_amd64_static/include/low-level/ /I ../../hasomed_precompiled/smpt_rm3_msvc2015_x86_amd64_static/include/general /link ../../hasomed_precompiled/smpt_rm3_msvc2015_x86_amd64_static/lib/libsmpt.lib

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