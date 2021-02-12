#!/bin/bash
# This program will print a left arrow to the screen
# skip Function
skip() {
    for i in $(seq $1);
    do
        printf " "
    done
}
# printStars Function
printStars() {
    for i in $(seq $1);
    do
        printf "*"
    done
    # Allow the option for printing the tail
    if [ ! -z $2 ]; 
    then
        for i in $(seq $2);
        do
            printf "*"
        done
    fi
}

# Get the length of base from user
echo "What wide length of base would you like?"
read wideLength
# Make sure it meets specifications
if [ `expr "$wideLength" % 2` == 0 ];
then
    echo "The wide length of the base must be odd!"
    exit 1
fi
# Get the length of the tail from the user
echo "What length of tail would you like?"
read tailLength
# Make sure neither length is less than 0
if [ "$wideLength" -lt 0 ] || [ "$tailLength" -lt 0 ];
then
    echo "You cannot have a wide length or tail length less than 0"
    exit 1
fi

# Set the number of skips to start with
let "skips=$wideLength-1"
# Set the top half number of rows
let "topHalf=$wideLength/2"
# Set the bottom half the same as the top half
bottomHalf=$topHalf
# Set the number of stars default
numOfStars=1

# Print the top half
for i in $(seq $topHalf);
do
    skip $skips
    printStars $numOfStars
    echo
    let "numOfStars+=2"
    let "skips-=2"
done

# Print the middle row + the tail
printStars $numOfStars $tailLength
echo
let "numOfStars-=2"
let "skips+=2"

# Print the bottom half of the arrow
for i in $(seq $bottomHalf);
do
    skip $skips
    printStars $numOfStars
    echo
    let "numOfStars-=2"
    let "skips+=2"
done

echo "Tail $tailLength, Base $wideLength Left Arrow"

exit 0
