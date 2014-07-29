#!/bin/bash
echo -n input numbers of seconds:
read c
echo -n Count:
tput sc
count=0
while true
do
if [ $count -lt $c ]
then let count++;
sleep 1;
tput rc
tput ed
echo -n $count
else exit 0
fi
done
