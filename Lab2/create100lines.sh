#!/bin/bash
# Creates a file of 100 lines counting from 1 to 100
if [ -e numbs ]; then
    echo "Appending to the file that already exists :)"
else
    echo "Creating and appending to the file :)"
    touch numbs
fi
for n in $(seq 1 100);
do
    echo "$n" >> numbs
done
