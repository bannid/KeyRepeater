pushd build
cl  /DDEBUG /MD -FC -Zi ..\main.cpp /link User32.lib
popd