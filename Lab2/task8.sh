#!/bin/bash
# This program will take one argument, an integer, and print the sum of it's digits

# Make sure that the correct amount of arguments has been passed
if [ $# != 1 ];
then
    echo "Incorrect amount of arguments passed. Need 1 integer argument"
    exit 1
fi

# Get a total
total=0
# Get a counter going
counter=$1

while [ "$counter" -gt 0 ];
do
    # Parse out each digit
    let "k=$counter % 10"
    let "counter/=10"
    let "total+=$k"
done

echo "Sum of digits for $1 is $total"
exit 0
