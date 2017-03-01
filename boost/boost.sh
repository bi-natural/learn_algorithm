#!/bin/bash

rm -rf build-script
mkdir -p build-script

pushd build-script

cmake ­-DCMAKE_BUILD_TYPE=Release ..

popd

cmake --build build-script --config Release
