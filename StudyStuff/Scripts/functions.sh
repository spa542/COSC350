#!/bin/bash
# This is going to demonstrate functions

greeting() {
    echo "In function:"
    echo "Positional parameter 1: $1"
    echo "Positional parameter 2: $2"
}

echo "Outside function:"
echo "Positional parameter 1: $1"
echo "Positional parameter 2: $2"
greeting "Yeet" "Yote"

exit 0
