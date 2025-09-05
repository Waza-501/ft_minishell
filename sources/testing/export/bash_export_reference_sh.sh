#!/bin/bash

# Bash Export Reference - Understanding the behavior you need to replicate

echo "=== BASH EXPORT BEHAVIOR REFERENCE ==="
echo

echo "Test 1: Export without arguments (lists all exported variables)"
echo -n "bash: "
export | head -3
echo "^ Shows format: declare -x VAR=\"value\""
echo

echo "Test 2: Export new variable with value"
echo -n "bash: "
export TEST_VAR=hello
echo "TEST_VAR=$TEST_VAR"
echo "Exit status: $?"
echo

echo "Test 3: Export variable without value (creates empty variable)"
echo -n "bash: "
export EMPTY_VAR
echo "EMPTY_VAR='$EMPTY_VAR'"
echo "Exit status: $?"
echo

echo "Test 4: Export existing variable (modify PATH temporarily)"
echo -n "bash: "
OLD_PATH=$PATH
export PATH=/test/path
echo "PATH=$PATH"
export PATH=$OLD_PATH  # Restore original
echo "Exit status: $?"
echo

echo "Test 5: Invalid identifier - starts with digit"
echo -n "bash: "
export 123INVALID=test 2>&1
echo "Exit status: $?"
echo

echo "Test 6: Invalid identifier - contains special characters"
echo -n "bash: "
export VAR-NAME=test 2>&1
echo "Exit status: $?"
echo

echo "Test 7: Invalid identifier - starts with equals"
echo -n "bash: "
export =value 2>&1
echo "Exit status: $?"
echo

echo "Test 8: Export with empty value (different from no value)"
echo -n "bash: "
export EMPTY_VALUE=
echo "EMPTY_VALUE='$EMPTY_VALUE'"
echo "Exit status: $?"
echo

echo "Test 9: Export multiple variables in one command"
echo -n "bash: "
export VAR1=value1 VAR2=value2
echo "VAR1=$VAR1, VAR2=$VAR2"
echo "Exit status: $?"
echo

echo "Test 10: Export with quotes (preserves spaces)"
echo -n "bash: "
export QUOTED_VAR="hello world test"
echo "QUOTED_VAR=$QUOTED_VAR"
echo "Exit status: $?"
echo

echo "Test 11: Export with variable expansion"
echo -n "bash: "
export HOME_BACKUP=$HOME
echo "HOME_BACKUP=$HOME_BACKUP"
echo "Exit status: $?"
echo

echo "Test 12: Export with append operation (VAR+=value)"
echo -n "bash: "
export PATH_BACKUP=$PATH
export PATH=/test
export PATH+=":/additional/path"
echo "PATH=$PATH"
export PATH=$PATH_BACKUP  # Restore
echo "Exit status: $?"
echo

echo "Test 13: Export invalid characters in variable name"
echo -n "bash: "
export "VAR NAME"=test 2>&1
echo "Exit status: $?"
echo

echo "Test 14: Export with just equals sign"
echo -n "bash: "
export JUST_EQUALS==value
echo "JUST_EQUALS=$JUST_EQUALS"
echo "Exit status: $?"
echo

echo "Test 15: Export non-existent variable (without value)"
echo -n "bash: "
export NON_EXISTENT
echo "NON_EXISTENT='$NON_EXISTENT'"
echo "Exit status: $?"
echo

echo "=== KEY EXPORT BEHAVIOR OBSERVATIONS ==="
echo "1. export without args: lists all exported vars in 'declare -x' format"
echo "2. export VAR=value: creates/updates variable and marks for export"
echo "3. export VAR: marks existing variable for export, creates empty if new"
echo "4. Valid identifier: [a-zA-Z_][a-zA-Z0-9_]*"
echo "5. Invalid identifiers return exit status 1 and print error"
echo "6. export VAR= creates variable with empty string (not unset)"
echo "7. Multiple variables can be exported in one command"
echo "8. Variable expansion works in values (\$HOME, etc.)"
echo "9. export VAR+=value appends to existing variable"
echo "10. Successful export always returns 0"
echo

echo "=== SORTING BEHAVIOR TEST ==="
echo "Export should print variables in sorted order:"
echo -n "bash: "
export | grep "^declare -x [A-C]" | head -3
echo

echo "=== COMPARISON WITH ENV COMMAND ==="
echo "env shows all environment variables (exported and non-exported):"
echo -n "bash: "
env | head -3
echo
echo "export shows only exported variables with declare -x format"
echo

echo "=== ERROR MESSAGE FORMAT ==="
echo "bash: export: \`123invalid': not a valid identifier"
echo "bash: export: \`var-name': not a valid identifier"
echo "bash: export: \`=value': not a valid identifier"
echo

echo "Run this script to see exact bash behavior:"
echo "bash bash_export_reference.sh"