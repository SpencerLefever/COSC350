#!/bin/sh

for file in *
do
  echo $file
    if [[ -d $file ]]
    then
        for file1 in "${file}/*"
        do 
            echo $file1
        done
    fi
done

exit 0 # Succesful exit