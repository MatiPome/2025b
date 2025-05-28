#!/bin/bash

# Output will be saved here
OUTPUT_FILE="output.txt"
: > "$OUTPUT_FILE"  # Clears the file at start

# List of test input files
tests=(
    "test1_valid_magic.txt"
    "test2_duplicate.txt"
    "test3_out_of_range.txt"
    "test4_not_enough.txt"
    "test5_too_many.txt"
    "test6_non_integer.txt"
    "test6_v2_non_integer.txt"
    "test7_wrong_sum.txt"

)

# Loop through each test file and run the program with it
for test_file in "${tests[@]}"
do
    echo "=== Running $test_file ===" >> "$OUTPUT_FILE"
    ./magic "$test_file" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE"
done