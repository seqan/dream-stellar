#!/bin/bash

echo -e "cmake_minimum_required (VERSION 3.8)\n" > datasources.cmake

echo -e "include (cmake/app_datasources.cmake)\n" >> datasources.cmake

cd split

for file in *
do
    [[ $file == *.sh ]] && continue # don't add script as datasource
    echo -n "declare_datasource (FILE ${file}
                URL \${CMAKE_SOURCE_DIR}/test/data/split/${file}
                URL_HASH SHA256=" >> ../datasources.cmake

    sha=($(shasum -a 256 $file))
    echo -n $sha >> ../datasources.cmake
    echo ")" >> ../datasources.cmake
done

echo -e "\n" >> ../datasources.cmake

cd ../build

for file in *
do
    [[ $file == *.sh ]] && continue
    echo -n "declare_datasource (FILE ${file}
                URL \${CMAKE_SOURCE_DIR}/test/data/build/${file}
                URL_HASH SHA256=" >> ../datasources.cmake

    sha=($(shasum -a 256 $file))
    echo -n $sha >> ../datasources.cmake
    echo ")" >> ../datasources.cmake
done

echo -e "\n" >> ../datasources.cmake

cd ../search

for file in *
do
    [[ $file == *.sh ]] && continue
    echo -n "declare_datasource (FILE ${file}
                URL \${CMAKE_SOURCE_DIR}/test/data/search/${file}
                URL_HASH SHA256=" >> ../datasources.cmake

    sha=($(shasum -a 256 $file))
    echo -n $sha >> ../datasources.cmake
    echo ")" >> ../datasources.cmake
done
