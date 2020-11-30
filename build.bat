mkdir build
pushd build
cl  /DDEBUG /MD -FC -Zi  ..\*.cpp /link User32.lib
popd