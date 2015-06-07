#!/bin/bash
path="/home/cam/book/long.file.name"
echo '##/*/',${path##/*/}
echo '#/*/',${path#/*/}
echo $path
echo '*%.',${path%.*}
echo '%%.*',${path%%.*}
echo ${path##*/}
filename="main.cpp.cpp"
echo ${filename/.cpp/.txt}#替换第一个
echo ${filename//.cpp/.txt}#替换所有


