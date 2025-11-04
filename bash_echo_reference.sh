#!/bin/bash

# Bash Echo Reference - Understanding the behavior you need to replicate

echo "=== BASH ECHO BEHAVIOR REFERENCE ==="
echo

echo "Test 1: Basic echo"
echo -n "bash: "
echo Hello World
echo

echo "Test 2: Echo with -n (no newline)"
echo -n "bash: "
echo -n Hello World
echo " <- (no newline here)"
echo

echo "Test 3: Echo with no arguments"
echo -n "bash: "
echo
echo "^ That was just a newline"
echo

echo "Test 4: Echo -n with no arguments"
echo -n "bash: "
echo -n
echo " <- (absolutely no output)"
echo

echo "Test 5: Multiple -n flags (important behavior!)"
echo -n "bash: "
echo -n -n test
echo " <- (consecutive -n flags)"

echo "Test 5b: Extended -n flags"
echo -n "bash: "
echo -nn test
echo

echo "Test 5c: Mixed extended -n flags"
echo -n "bash: "
echo -nnn -nn test
echo
echo

echo "Test 6: -n combined with text (not a flag)"
echo -n "bash: "
echo -ntest
echo

echo "Test 7: Empty string argument"
echo -n "bash: "
echo Hello "" World
echo

echo "Test 8: Multiple spaces (shell splits them)"
echo -n "bash: "
echo Hello     World
echo "^ Those multiple spaces become single space"
echo

echo "Test 9: Tab and newline characters"
echo -n "bash: "
echo "Hello\tWorld\nTest"
echo

echo "Test 10: Special case - invalid flags are treated as arguments"
echo -n "bash: "
echo -x Hello
echo

echo "=== KEY OBSERVATIONS ==="
echo "1. Only exact '-n' as first arg suppresses newline"
echo "2. Multiple -n flags: first is flag, rest are arguments"
echo "3. Arguments are separated by single spaces"
echo "4. echo never fails (always exit status 0)"
echo "5. No interpretation of escape sequences by default"
echo "6. Empty arguments create extra spaces between words"

echo
echo "=== EXIT STATUS TEST ==="
echo Hello
echo "Exit status: $?"  # Should always be 0

echo -n "Non-existent option test: "
echo -xyz hello
echo "Exit status: $?"  # Still 0

echo
echo "Run this script to see exact bash behavior:"
echo "bash bash_echo_reference.sh"