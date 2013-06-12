mkdir ..\_build
cd ..\_build

cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=C:\Qt\Qt5.1.0\5.1.0-rc1\mingw48_32\lib\cmake\Qt5Core -DCMAKE_INCLUDE_PATH=_deps-win32\mingw\include -DCMAKE_LIBRARY_PATH=_deps-win32\mingw\lib\debug -DCMAKE_FRAMEWORK_PATH=_deps-win32\mingw\share ..\

