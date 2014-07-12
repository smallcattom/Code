#!/bin/bash
if [ $# -eq 0 ]
then
exit 1
fi

a=`ls | grep $1`
if [ $a != $1 ]
then
echo "file $1 is not exist.\nPlease try again."
exit 1
fi

name=$1
if [ $# -eq 1 ]
then
desc="update"
else
shift
desc=$@
fi
#echo $desc,$name
git add $name
git commit -m "$desc"
git push origin master
