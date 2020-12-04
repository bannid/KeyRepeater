@echo off
mkdir build
pushd build
cl  /Femain.exe /DDEBUG /MD -FC -Zi  ..\*.cpp /link User32.lib
popd	