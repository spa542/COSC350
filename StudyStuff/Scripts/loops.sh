#!/bin/bash
# Loops in shell scripting

echo "Name the file in the current directory"
for file in *; do
    echo $file
    case $file in
        *.sh) 
            echo "We like this file"
            echo "This is a shell script";;
        *.o) echo "This is an object file";;
        *.h) echo "This is a header file";;
        *) echo "This is an unrecognized file";;
    esac
    echo "------------------------------------"
    sleep 1
done

exit 0
