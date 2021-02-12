#!/bin/bash
# This script will compute the factorial of a number

echo "Enter a number:"
read number
# Quick return 
if [ "$number" -eq 1 ] || [ "$number" -eq 0 ];
then
    echo "Factorial is: 1"
    exit 0
fi
# Check bounds
if [ "$number" -lt 0 ]; 
then
    echo "Number must be greater than or equal to 0"
    exit 1
fi

# Set up a tmp total variable
total=$number
let "number-=1"

while [ "$number" -gt 1 ];
do
    let "total*=$number"
    let "number-=1"
done

echo "Factorial is: $total"
exit 0
