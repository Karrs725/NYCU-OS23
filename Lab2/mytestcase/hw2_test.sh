#!/bin/bash

cpp_program="../hw2"

output_dir="./output"
mkdir -p "$output_dir"
count=0;

ref_output_dir="./ans"

# Loop through input files and run the C++ program
for i in {1..1000}; do
    input_file="testcase/tc_${i}.txt"
    output_file="${output_dir}/output_${i}.txt"
    ref_output_file="${ref_output_dir}/ans_${i}.txt"

    # Check if the input file exists
    if [ -f "$input_file" ]; then
        # Run the C++ program with the input file and save output to the corresponding output file
        "$cpp_program" < "$input_file" > "$output_file"
        #echo "Processed $input_file and saved output to $output_file"
        
        # Compare the generated output with the reference output
        if diff "$output_file" "$ref_output_file"; then
            #echo "Files $output_file and $ref_output_file are identical."
            count=$((count + 1))
        else
            echo "Files $output_file and $ref_output_file are different."
        fi
    else
        echo "Input file $input_file not found."
    fi
    
done
echo "count: $count"