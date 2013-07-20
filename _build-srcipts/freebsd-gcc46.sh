#!/bin/sh

mkdir ../_build
cd ../_build
cmake -DCMAKE_C_COMPILER=/usr/local/bin/gcc46 -DCMAKE_CXX_COMPILER=/usr/local/bin/g++46 -D CMAKE_BUILD_TYPE=GCCNativeMaxSpeedRel ../

