# Rehamove Integration Lib: Python and C# Extensions for RehaMove 3

This is the **rehamoveIntegrationLib**, a collection of libraries that interface with the RehaMove 3 medical device.

![image](extra/video.png)
(click [here](https://youtu.be/IyL0C_fEE2A) for our youtube video)

**What does this do?** The RehaMove 3 is a medical device that sends out electrical signals, which can be used clinically and in research, e.g. by doing functional electrical stimulation (FES) and/or electrical muscle stimulation (EMS). Existing documentation is provided by the manufacturer Hasomed to control the RehaMove via C code. **Our libraries extend this functionality to Python and C#**, allowing the user to send commands in these other languages. This can be used for rapid prototyping, and/or integration with engines such as Unity3D.

## 0. A must read before using

1. Read the LICENSE (when it exists) and [Liability Waiver](https://github.com/PedroLopes/openEMSstim/blob/master/documentation/liability_waiver.md)
2. Read the [what-not-to-do list](https://github.com/PedroLopes/openEMSstim/blob/master/start-here-tutorials/0.WhatNotToDo.md).
3. Never tried EMS before? Then, [watch our tutorial of applying EMS first](http://plopes.org/ems/#testingEMSmachine).


## 1. How to install

### 1.1 Python

We support several versions of the library for different systems. After downloading the files, **move the files to your working directory** (where you will run Python from).

#### 1.1.1 Linux

For Linux, we support two versions (for AMD64 and for ARM architectures). Make sure you have the following files:

1. `rehamove.py`
2. `rehamovelib.py`
3. `_rehamovelib.so`

#### 1.1.2 Windows

For Windows, we support AMD64 architectures. Make sure you have the following files:

1. `rehamove.py`
2. `rehamovelib.py`
3. `_rehamovelib.pyd`

#### 1.1.3 MacOS
We currently do not support MacOS. Come back soon!

### 1.2 C\# (for Unity3D)

We support C# for Unity3D integration on Windows. Make sure you have the following files:

1. `rehamovelib.dll`
2. `UnityRehamove.dll`

After downloading the files, **move the downloaded files into the Assets folder of your Unity project**.


## 2. How to use

This section explains how to use our libraries, including example code demonstrating imports and calling the library functions.

The following is a video tutorial:
[insert video here]

### 2.1 Python

You can import the libraries into your own Python scripts. For example, the following script `test_example1.py` was included in the tutorial video (here for Windows): 

```
from rehamove import *          # Import our library
import time

r = Rehamove("COM4")            # Open USB port (on Windows)
for i in range(0, 5):
    r.pulse("blue", 6, 200)     # Send pulse every second
    time.sleep(1)
```

Scripts like these can be invoked from the command line, using `python3 test_example1.py` or its equivalent.

In addition, our libraries can also be imported in interactive Python sessions. Example:

```
python
> from rehamove import *                                # Import our library
> r = Rehamove("/dev/ttyUSB0")                          # Open USB port (on Linux)
> r.pulse("blue", 5, 200)                               # Send single pulse
> r.battery()                                           # Query battery life
> r.custom_pulse("blue", [(5.0, 200), (-5.0, 200)])     # Send pulse with custom waveform
> exit()                                                # Automatically closes port
```

### 2.2 C\# (Unity3D)

You can write C# scripts in your Unity3D project that call our library functions: Example:
```
...
using UnityRehamove;

public class NewBehaviourScript : MonoBehaviour
{
    Rehamove r = null;

    void Start() {
        r = new UnityRehamove.Rehamove("COM3");
        StartCoroutine(Pulse());
    }

    IEnumerator Pulse() {
        for (int i = 0; i < 10; i++) {
            r.pulse("blue", 6, 200);
            yield return new WaitForSeconds(1.0f);
        }
        yield return 0;
    }

    void OnApplicationQuit() {
        r.close();
    }
}
```

## 3. What is supported?

This section describes the list of functions that our libraries currently support. In the future, we hope to support all of the API (link?) provided by the RehaMove manufacturers.

### 3.1 Python

* `r = Rehamove(port_name)`: Constructor to initialize the device. **Save the return value to a variable! This return value is needed to invoke the other functions.** Takes in one argument (the port_name, for example **/dev/ttyUSB0**). Returns a Rehamove object. This function automatically opens the port.

* `r.pulse(channel_name, current, pulse_width)`: Sends a single pulse. Takes in three arguments:
	* a character string for the channel (e.g. `"red"`, `"blue"`, or `"black"`)
	* the current intensity (mA)
	* the length of the pulse (us)

* `r.custom_pulse(channel_name, points_array)`:
Sends a single pulse with a custom waveform. Takes in two arguments:
	* a character string for the channel (e.g. `"red"`, `"blue"`, or `"black"`)
	* an array of tuples, each tuple having two elements (a current (mA), and a pulse_width (us)). The custom waveform can only support 16 points. Sending an array with more than 16 points will only execute the first 16 points, and sending an array with less than 16 points will automatically create empty points (0.0, 0) to fill in the leftover number.

* `r.battery()`: Queries the device for the battery percentage. Currently this is printed rather than returned as a value.

* The connection port **automatically closes** open exiting the Python application.

### 3.2 C\# (Unity3D)

The supported functionality is almost entirely the same as for Python (see section for Python). 

Differences:
* `r.battery()`: Queries the device for the battery percentage. Currently this is returned as a value (integer).
* `r.close()`: Closes the port (assuming that `r` is a Rehamove object created when opening the port. Unlike in the Python library, the port **does NOT automatically close** when the C# execution ends. The port must be manually closed with this function. It is possible to use Unity3D's `onApplicationQuit()` method to call this function automatically when the Unity3D program ends.

## 4. How to build/compile

This section is for developers interested in building/compiling from source. This project is compiled and linked with the Hasomed's Rehamove library (a precompiled C library). Our libraries were developed and compiled with version 3.2.4. You can find their latest version [here](https://www.rehamove.com/fileadmin/user_upload/RehaMove/ScienceMode/smpt_rm3_V3.2.4b.zip). 


In order to interface with Hasomed's precompiled C library our project uses [SWIG](http://www.swig.org/). 

### 4.0 General dependencies
Install SWIG (you may have to also download PCRE, `configure`, `make`, and `make install`).

### 4.1 Python

#### 4.1.1 Python on Linux (64 bit architectures, i.e., AMD64)

The files needed include:

* `rehamovelib.c`: Our functions in C that call functions from Hasomed's existing C library
* `rehamovelib.i`: An interface file of function declarations used for SWIG wrapper generation
* `rehamove.py`: Our own Python wrapper to run on top of SWIG's generated wrapper

Next, we generated the shared library file by invoking SWIG, compiling, and then linking our libraries. We called the following build script in the terminal:

```
swig -python rehamovelib.i;

gcc -c rehamovelib.c -fPIC -I ../../../library/smpt_rm3_gcc_linux_x86_amd64_static/include/low-level/ -I ../../../library/smpt_rm3_gcc_linux_x86_amd64_static/include/general/;

gcc -c rehamovelib_wrap.c -fPIC -I ../../../library/smpt_rm3_gcc_linux_x86_amd64_static/include/low-level/ -I ../../../library/smpt_rm3_gcc_linux_x86_amd64_static/include/general/ -I /usr/include/python2.7 ;

ld -shared rehamovelib.o rehamovelib_wrap.o -o _rehamovelib.so -L ../../../library/smpt_rm3_gcc_linux_x86_amd64_static/lib/ -lsmpt
```

The shared library output, `_rehamovelib.so`, can be included with the wrappers (`rehamovelib.py` and `rehamove.py`) for final use.

Some notes:

* SWIG can compile for several languages (here we use the `-python` flag). It takes an interface file as input (here `rehamovelib.i`), and generates wrapper files.
* The `-fPIC` flag is used to specify position-independent code, since we are building a shared library.
* The Hasomed C library we use is the version: `smpt_rm3_gcc_linux_x86_amd64_static`.
* When compiling, we use the `-I` flag to include paths to the C header files.
* Additionally, we include paths to the Python header files.
* When linking, we use the `-L` flag we include the path to the precompiled C library.

#### 4.1.2 Python on Linux for ARM architectures

We tested our project on a Raspberry Pi 3 running the Raspbian operating system. The build process here is very similar to that of Python on Linux AMD64, with some slight differences based on this architecture. Here is an example of the modified build script:
```
swig -python rehamovelib.i;

gcc -c rehamovelib.c -fPIC -I ../RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_gcc_linux_arm_eabihf_static/include/low-level/ -I ../RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_gcc_linux_arm_eabihf_static/include/general/;

gcc -c rehamovelib_wrap.c -fPIC -I ../RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_gcc_linux_arm_eabihf_static/include/low-level/ -I ../RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_gcc_linux_arm_eabihf_static/include/general/ -I /usr/include/python2.7 ;

ld -shared rehamovelib.o rehamovelib_wrap.o -o _rehamovelib.so -L ../RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_gcc_linux_arm_eabihf_static/lib/ -lsmpt -L /usr/lib/gcc/arm-linux-gnueabihf/6 -lgcc
```

The shared library output, `_rehamovelib.so`, can be included with the wrappers (`rehamovelib.py` and `rehamove.py`) for final use.

Some notes:

 SWIG can compile for several languages (here we use the `-python` flag). It takes an interface file as input (here `rehamovelib.i`), and generates wrapper files.
* The `-fPIC` flag is used to specify position-independent code, since we are building a shared library.
* The Hasomed C library we use is the version: `smpt_rm3_gcc_linux_arm_eabihf_static`.
* When compiling, we use the `-I` flag to include paths to the C header files.
* Additionally, we include paths to the Python header files.
* When linking, we use the `-L` flag we include the path to the precompiled C library.
* In the linking step, we now needed to also link to a GCC library that handles floating point numbers. This could possibly be because the ARM and AMD64 architectures handle floating point calculations differently.

#### 4.1.3 Python on Windows (also 64-bit)

We tested our build here on a Windows 10 system. The starting files are the same as in Python for Linux AMD64.

In order to access the precompiled C library for Windows, we needed to build using the Microsoft Visual C++ compiler (MSVC). After downloading Visual Studio 2017, we compiled using the developer command line tool: `x64 Native Tools Command Prompt for VS 2017`. An example of the build batch script is:

```
swig -python rehamovelib.i

cl /LD /MD rehamovelib.c rehamovelib_wrap.c /Fe_rehamovelib.pyd /I "C:/Users/Agggron/AppData/Local/Programs/Python/Python37/include" /I "C:/Users/Agggron/Documents/UCHICAGO/SPRING_2019/rehamove-library/rehamove-library/RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_msvc2015_x86_amd64_static/include/low-level" /I "C:/Users/Agggron/Documents/UCHICAGO/SPRING_2019/rehamove-library/rehamove-library/RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_msvc2015_x86_amd64_static/include/general" /link "C:/Users/Agggron/Documents/UCHICAGO/SPRING_2019/rehamove-library/rehamove-library/RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_msvc2015_x86_amd64_static/lib/libsmpt.lib" "C:/Users/Agggron/AppData/Local/Programs/Python/Python37/libs/python37.lib"
```

The shared library output, `_rehamovelib.pyd`, can be included with the wrappers (`rehamovelib.py` and `rehamove.py`) for final use.

Some notes:

- `cl` invokes the compiler + linker. The commands that follow relate to the MSVC compiler.
- `/LD` specifies creation of a DLL. 
- `/MD` links to the library MSVCRT.lib, which apparently is needed to access some of its C functions.
- `/Fe` specifies the output file. For using Python on Windows, **we need a .pyd file as output!**
- When including directories (with `/I`), the Hasomed C library we use is the version: `smpt_rm3_msvc2015_x86_amd64_static`
- When linking (with `/link`), we also need to link to a Python library. 

### 4.2 C\# (for Unity3D) on Windows (also 64-bit)

We performed our build here on a Windows 10 system. The files needed include:

* `rehamovelib.c`: Our functions in C that call functions from Hasomed's existing C library
* `rehamovelib.i`: An interface file of function declarations used for SWIG wrapper generation
* `rehamove.cs`: Our own C# wrapper to run on top of SWIG's generated wrapper

In order to access Hasomed's precompiled C library for Windows, we needed to build using the Microsoft Visual C++ compiler (MSVC). After downloading Visual Studio 2017, we compiled using the developer command line tool: `x64 Native Tools Command Prompt for VS 2017`. 

For integration with Unity3D, we realized we needed two DLLs: one that links to the library functions, and another that can integrate with Unity3D. The following batch script (run from the above-mentioned command line tool) creates the first DLL and prepares for the second DLL:

```
swig -csharp rehamovelib.i

cl /LD /MD rehamovelib.c rehamovelib_wrap.c /Ferehamovelib.dll /I ../../RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_msvc2015_x86_amd64_static/include/low-level/ /I ../../RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_msvc2015_x86_amd64_static/include/general /link ../../RehaMove3_ScienceMode3/smpt_rm3_V3.2.4/library/smpt_rm3_msvc2015_x86_amd64_static/lib/libsmpt.lib

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
```

Some notes:

- `cl` invokes the compiler + linker. The commands that follow relate to the MSVC compiler.
- `/LD` specifies creation of a DLL. 
- `/MD` links to the library MSVCRT.lib, which apparently is needed to access some of its C functions.
- `/Fe` specifies the output file. For using C# on Windows, we create a .dll file.
- When including directories (with `/I`), the Hasomed C library we use is the version: `smpt_rm3_msvc2015_x86_amd64_static` 

The first part of the batch script creates the output `rehamovelib.dll`. The second part of the batch script simply adds the lines `namespace UnityRehamove {` and `}` to each of the .cs files, in preparation for creating the second DLL.

We then performed the following steps to create the second DLL that interfaces with Unity3D:

* Create a new project in Visual Studio 2017. We will select `Visual C# => Class Library (.NET Framework)` to create a project for a C# DLL.
* We add the files to the solution. In the `Solution Explorer`, right-click the solution name, go to `Add`, then `Existing Item`, followed by choosing all of the .cs files in our build so far. There should be five of them: 
	* `rehamove.cs`
	* `rehamovelib.cs`
	* `rehamovelibPINVOKE.cs`
	* `RehamoveDevice.cs`
	* `SWIGTYPE_p_Smpt_device.cs` 
* Add a reference to the UnityEngine DLL. To do this, in the `Solution Explorer`, I right-clicked `References`, clicked `Add Reference` (opening up the `Reference Manager`), and then added in a reference to the `UnityEngine.dll` path location. For me, the path was: `C:\Program Files\Unity\Hub\Editor\2019.1.2f1\Editor\Data\Managed\UnityEngine.dll`
* Make sure that all of the files are under the same namespace (here `UnityRehamove`). This should be done by the previous batch script.
* Perform the build! At the top of Visual Studio 2017, go to `Build`, then `Build Solution`. You should generate the output, `UnityRehamove.dll`.

Both of the output DLLs (`rehamovelib.dll` and `UnityRehamove.dll`) can be imported into a Unity project for use!

## 5. Next features and known bugs

This is a list of known bugs/features in our libraries that we hope to fix and/or implement soon. Please feel free to contact us if you find more!

- Sparse exception handling. Python versions will see printed statements for unsuccessful port connections, etc., but in general error messages can be more comprehensive and standard in both Python and C#.
- For C# (on Unity3D), the port does not automatically close. Please use Unity3D's `onApplicationQuit()` method to call our library's `close()` function.
- Our library's `battery()` function stalls the program if the query to the RehaMove is unsuccessful.

## 6. Contact

This library was made by Aaron Tang with the help of Pedro Lopes. Feel free to contact us if you have any questions, comments, or suggestions!

## 7. LICENSE

This project is licensed via Creative Commons Attribution-NonCommercial 2.0 Generic (CC BY-NC 2.0). 

This means:
* You cannot use it for commercial purposes without asking us.
* You can' only use this for non-commercial purposes crediting our work (link to https://github.com/humancomputerintegration/rehamove-integration-lib or lab.lopes.org/rehamove.html).
* Otherwise, you can share it, you can remix it, etc.

Full LICENSE AT: https://creativecommons.org/licenses/by-nc/2.0/
