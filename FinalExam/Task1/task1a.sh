#!/bin/bash

for eachfile in *
do
    echo "File in current directory"
    echo $eachfile
    if [ -d $eachfile ];
    then
        subdirpath=$eachfile
        subdirpath+="/*"
        echo "Sub-Direcories:"
        for subfile in $subdirpath
        do
            if [ -d $subfile ];
            then
                echo $subfile
            fi
        done
    fi
done
