#!/bin/bash

if [ $# -le 0 ];
then
    echo "Invalid # of arguments"
    exit 1
fi

sum=0

for i in $*
do
    let "sum+=$i"
done

echo "Summation of arguments is $sum"
