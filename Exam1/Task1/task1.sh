#!/bin/bash

if [ $# -lt 1 ];
then
    echo "Need one or more arguments";
    exit 1
fi

# Get a total
oddTotal=0

for arg in $@
do
    if [ `expr $arg % 2` -gt 0 ];
    then
        let "oddTotal+=$arg"
    fi

done

echo "Sum of odd arguments is $oddTotal"
exit 0
