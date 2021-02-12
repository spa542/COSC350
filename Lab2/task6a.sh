#!/bin/bash
# This will create a # based diamond
# Skip Function
skip() {
    for skip in $(seq $1);
    do
        printf " "
    done
}
# Print Stars function 
printStars() {
    for star in $(seq $1);
    do
        printf "*"
    done
}

echo "What base of diamond would you like?:"
read base
# Check to see if the base is correct
if [ "$base" -lt 3 ];
then
    echo "Base must be greater than 3!"
    exit 1
fi
if [ `expr $base % 2` == 0 ];
then
    echo "Base must be an odd number!"
    exit 1
fi
# To hold the amount of stars
numOfStars=1
# Calculate the number of skips
let "skips=$base/2"
# Calculate the number of top half rows
let "topHalf=$base/2"
# Bottom half rows are equal to the top half
bottomHalf=$topHalf
# Print the top half
for i in $(seq $topHalf);
do 
    skip $skips
    printStars $numOfStars
    skip $skips
    echo
    let "numOfStars+=2"
    let "skips-=1"
done

# Print the middle
printStars $numOfStars
echo
let "numOfStars-=2"
let "skips+=1"

# Print the bottom half
for i in $(seq $bottomHalf);
do 
    skip $skips
    printStars $numOfStars
    skip $skips
    echo
    let "numOfStars-=2"
    let "skips+=1"
done

echo "Base $base diamond!"

exit 0
