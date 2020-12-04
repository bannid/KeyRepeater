mkdir KeyRepeater
pushd KeyRepeater
cl  /O2 /FeKeyTurbo.exe /DNDEBUG  ..\*.cpp /link User32.lib
popd