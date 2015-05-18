#!/bin/bash
filename=${1:?"need input filename"}
howmany=${2:-3}
sort -rn $filename | head -$howmany

