#!/bin/bash
# Prints the sum of the arguments to the screen

# Get the total
total=0
for arg in $*;
do
    let "total+=$arg"
done

# Print the total
echo "Sum of arguments is $total"
# Success
exit 0
