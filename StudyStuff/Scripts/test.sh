#!/bin/bash
# This is a test script
echo "What is your name?"
read answer
if [ "$answer" = "Ryan" ]; then
    echo "You are a cuck!"
elif [ "$answer" = "Grant" ]; then
    echo "You are obese!"
else
    echo "You are pretty cool!"
fi
exit 0
