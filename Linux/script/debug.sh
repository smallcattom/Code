#!/bin/bash
for i in {1..6}
do
set -x
sleep 2
echo $i
set +x
done
echo "Script executed"
