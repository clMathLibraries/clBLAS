del CMakeCache.txt
cmake -DCMAKE_BUILD_TYPE=debug -G "Visual Studio 10" ..\tplgen
if NOT ERRORLEVEL 1 goto end
IF ERRORLEVEL 4 goto try9
IF ERRORLEVEL 3 goto try9
IF ERRORLEVEL 2 goto try9
IF ERRORLEVEL 1 goto try9
goto end

:try9
del CMakeCache.txt
cmake -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 9 2008" ..\tplgen

:end