#!/bin/bash
if [ $# -eq 0 ]
then
exit 1
fi
git add $1
git commit -m $2
git push origin master
