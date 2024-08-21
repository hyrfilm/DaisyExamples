#!/bin/bash

directory=./

# Line to prepend
line='#include "hacks.h"'

# Loop over all .h files in the directory
for file in "$directory"/*.h; do
    # Prepend the line to the file using a temporary file
    { echo "$line"; cat "$file"; } > temp && mv temp "$file"
    echo "Prepended to $(basename "$file")"
done

