#!/bin/sh

mkdir -p build; cd build && conan install .. -pr=default --build=missing -c tools.system.package_manager:mode=install && cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build  . -- -j 3

cp r-type_client  ..

cp r-type_server  ..
