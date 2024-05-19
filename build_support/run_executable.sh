#!/bin/bash

# run all executable files 
echo "Start running all algorithms"

for file in ` ls `
    do 
        if [[ -f ${file} && -x ${file} ]]; then
            echo "In debug mode run ${file}......"
            ./$file
            if [[ $? -ne 0 ]]; then
                echo "In debug mode run ${file} failed!"
                exit 1
            fi
        fi
    done

echo "All tests passed!"