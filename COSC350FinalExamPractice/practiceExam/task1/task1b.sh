#!/bin/bash

for var in "$@";
do
    let sum="$sum+$var"
done

echo "Sum: $sum"
exit 0;