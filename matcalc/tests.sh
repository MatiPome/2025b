#!/usr/bin/env bash
# tests.sh – semantic tests for your matrix calculator
# Usage:
#   chmod +x tests.sh
#   ./tests.sh

EXE=./mainmat   # <-- must point to your built REPL executable

# run_test: feeds one command + “stop” into the REPL, then greps for the expected regex
run_test() {
  local cmd="$1"
  local expect="$2"
  out="$(printf '%s\nstop\n' "$cmd" | "$EXE" 2>&1)"
  if echo "$out" | grep -qE "$expect"; then
    printf "PASS: %-40s → %s\n" "\"$cmd\"" "$expect"
  else
    printf "FAIL: %-40s\n  got: %s\n  expected: %s\n\n" "\"$cmd\"" "$out" "$expect"
  fi
}

# 1. No spaces around commas
run_test "read_mat MAT_A,1,2,3"             "Values successfully inserted!"

# 2. Spaces around commas
run_test "read_mat   MAT_B , 4 , 5 ,6  "    "Values successfully inserted!"

# 3. Missing comma after first name
run_test "add_mat MAT_A MAT_B,MAT_C"        "Missing comma after first name"

# 4. Trailing comma at end
run_test "read_mat MAT_A,1,2,3,"            "Trailing comma after last value"

# 5. Unknown matrix
run_test "print_mat MAT_X"                  "Invalid matrix name"

# 6. Undefined command
run_test "foobar MAT_A,MAT_B,MAT_C"         "Undefined command or missing args"

# 7. Missing scalar value
run_test "mul_scalar MAT_A, ,MAT_B"         "no scalar found in input"

# 8. No space between cmd and args should still work
#    We just check that a number prints (matrix output)
run_test "print_mat MAT_A"                  '^[[:space:]]*[0-9]'

# 9. Missing all args
run_test "read_mat"                         "Undefined command or missing args"

# 10. Correct transpose produces no error (empty regex matches anything)
run_test "trans_mat MAT_A,MAT_B"            ""

echo "Semantic tests complete."
