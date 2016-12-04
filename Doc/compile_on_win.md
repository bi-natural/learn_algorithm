# compile on windows

참고) https://msdn.microsoft.com/en-us/library/kezkeayy.aspx
참고) https://msdn.microsoft.com/en-us/library/f2ccy3wt.aspx

If you already have Visual Studio 201x.

To run vcvarsall.bat

At the command prompt, change to the Visual C++ installation directory. (The location depends on the system and the Visual Studio installation, but a typical location is C:\Program Files (x86)\Microsoft Visual Studio version\VC\.) For example, enter:
cd "\Program Files (x86)\Microsoft Visual Studio 14.0\VC"
To configure this Command Prompt window for 32-bit x86 command-line builds, at the command prompt, enter:

"\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall" x86


compile.

C:\> cl /EHsc sample.cpp

   :

C:\> sample.exe


[Ref] nmake.exe
    https://msdn.microsoft.com/en-us/library/dd9y37ha.aspx
