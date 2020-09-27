rem This file is used to initiate the nmake command

rem call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars64.bat"

set dir=src

:: Create the volumes
call .\utils\volumes\create-volumes.bat