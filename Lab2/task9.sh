#!/bin/bash
# This program will search for a specified word in a specified file from the user

# First ask the user for a directory
echo "Enter a directory to be searched for (Absolute PATH only!):"
read dirpath
# Check to see if this is a valid directory
if [ ! -d "$dirpath" ]; 
then
    echo "This directory does not exist"
    exit 1 # Exit 1 indicates no such directory
fi

# Now ask for a file in that directory
numChances=3
counter=0
isFound=false
while [ $counter -lt $numChances ];
do
    # Get the name of the file from the user
    echo "Enter the name of a readable file (`expr $numChances - $counter` chance(s) left):"
    read filename
   
    # Create the full file path
    filepath=$dirpath
    filepath+=$filename

    # Check if the file exists
    if [ ! -f "$filepath" ];
    then
        echo "File path given: $filepath"
        echo "File not found :("
    else
        isFound=true
        break
    fi
    let "counter+=1"
done

# Check to see if the file was ever found
if [ "$isFound" = false ]; 
then
    echo "File was never found with the chances given"
    exit 2 # Exit 2 indicates no such file found after chances given
fi

# Check to see if the file is readable
if [ ! -r $filepath ]; 
then
    echo "File is not readable"
    exit 3 # Exit 3 indicates that the file found is not readable
fi

# Now ask the user for a word in the file
echo "Enter a word to be searched for within the file:"
read word

# Now check to see if the word is in the file or not
if grep "$word" $filepath;
then
    echo "$word FOUND!"
else
    echo "$word NOT FOUND!"
    exit 4 # Exit 4 indicates that the word was not found in the file
fi

exit 0 # Success!
