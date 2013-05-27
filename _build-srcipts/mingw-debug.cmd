mkdir ..\_build
cd ..\_build

cmake -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Debug -DCMAKE_INCLUDE_PATH=_deps-win32\mingw\include -DCMAKE_LIBRARY_PATH=_deps-win32\mingw\lib\debug -DCMAKE_FRAMEWORK_PATH=_deps-win32\mingw\share -DBoost_NO_SYSTEM_PATHS=TRUE -DBoost_NO_BOOST_CMAKE=TRUE -DBOOST_ROOT=_deps-win32\mingw\Boost ..\

REM cmake -G "MinGW Makefiles" -D CMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=C:\Qt\Qt5.0.2\5.0.2\mingw47_32\lib\cmake\Qt5Core -DCMAKE_INCLUDE_PATH=_deps-win32\mingw\include -DCMAKE_LIBRARY_PATH=_deps-win32\mingw\lib\debug -DCMAKE_FRAMEWORK_PATH=_deps-win32\mingw\share -DBoost_NO_SYSTEM_PATHS=TRUE -DBoost_NO_BOOST_CMAKE=TRUE -DBOOST_ROOT=_deps-win32\mingw\Boost ..\

