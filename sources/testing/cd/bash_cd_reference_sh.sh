#!/bin/bash

# Bash cd Reference - Understanding the behavior you need to replicate

echo "=== BASH CD BEHAVIOR REFERENCE ==="
echo

# Store original directory to restore later
ORIGINAL_DIR=$(pwd)

# Function to show current state
show_state() {
    echo "Current directory: $(pwd)"
    echo "PWD: $PWD"
    echo "OLDPWD: $OLDPWD"
    echo "Exit status: $?"
}

echo "INITIAL STATE:"
show_state
echo

echo "======================================="
echo "Test 1: cd (no arguments - go to HOME)"
echo "Command: cd"
echo "======================================="
echo "bash: cd"
cd
show_state
echo

echo "======================================="
echo "Test 2: cd to /tmp"
echo "Command: cd /tmp"
echo "======================================="
echo "bash: cd /tmp"
cd /tmp
show_state
echo

echo "======================================="
echo "Test 3: cd - (go to previous directory)"
echo "Command: cd -"
echo "======================================="
echo "bash: cd -"
cd -  # This should print the directory it goes to
echo "Exit status: $?"
echo "Result after cd -:"
show_state
echo

echo "======================================="
echo "Test 4: cd ~ (explicit home)"
echo "Command: cd ~"
echo "======================================="
echo "bash: cd ~"
cd ~
show_state
echo

echo "======================================="
echo "Test 5: cd to non-existent directory"
echo "Command: cd /this/path/does/not/exist"
echo "======================================="
echo "bash: cd /this/path/does/not/exist"
cd /this/path/does/not/exist 2>&1  # Capture stderr
echo "Exit status: $?"
show_state
echo

echo "======================================="
echo "Test 6: cd .. (parent directory)"
echo "Command: cd .."
echo "======================================="
echo "bash: cd .."
cd ..
show_state
echo

echo "======================================="
echo "Test 7: cd . (current directory)"
echo "Command: cd ."
echo "======================================="
echo "bash: cd ."
cd .
show_state
echo

echo "======================================="
echo "Test 8: cd with relative path"
echo "Command: cd usr"
echo "======================================="
echo "bash: cd usr"
cd usr 2>&1  # May fail, capture error
echo "Exit status: $?"
show_state
echo

echo "======================================="
echo "Test 9: Testing with unset HOME"
echo "======================================="
# Go to a known directory first
cd /tmp
echo "Current: $(pwd)"
echo "Unsetting HOME variable..."
SAVED_HOME="$HOME"
unset HOME
echo "bash: cd (with HOME unset)"
cd 2>&1
echo "Exit status: $?"
echo "Current after failed cd: $(pwd)"
# Restore HOME
export HOME="$SAVED_HOME"
echo "HOME restored: $HOME"
echo

echo "======================================="
echo "Test 10: Testing with unset OLDPWD"
echo "======================================="
# Go somewhere to set OLDPWD
cd /tmp
echo "Current: $(pwd), OLDPWD: $OLDPWD"
# Save and unset OLDPWD
SAVED_OLDPWD="$OLDPWD"
unset OLDPWD
echo "OLDPWD unset, trying cd -:"
echo "bash: cd -"
cd - 2>&1
echo "Exit status: $?"
echo "Current after failed cd -: $(pwd)"
# Restore OLDPWD
export OLDPWD="$SAVED_OLDPWD"
echo "OLDPWD restored: $OLDPWD"
echo

echo "======================================="
echo "Test 11: Multiple cd operations sequence"
echo "======================================="
echo "bash: cd /tmp"
cd /tmp
echo "PWD: $PWD, OLDPWD: $OLDPWD"
echo "bash: cd /usr"
cd /usr
echo "PWD: $PWD, OLDPWD: $OLDPWD"
echo "bash: cd -"
cd -  # Should go back to /tmp and print it
echo "PWD: $PWD, OLDPWD: $OLDPWD"
echo "bash: cd -"
cd -  # Should go back to /usr and print it
echo "PWD: $PWD, OLDPWD: $OLDPWD"
echo

echo "=== KEY BASH CD BEHAVIORS TO REPLICATE ==="
echo
echo "1. BASIC BEHAVIOR:"
echo "   - cd (no args) goes to HOME directory"
echo "   - cd <path> goes to specified path"
echo "   - cd - goes to OLDPWD (previous directory)"
echo "   - cd ~ goes to HOME directory"
echo
echo "2. ENVIRONMENT VARIABLES:"
echo "   - PWD is always updated to current directory"
echo "   - OLDPWD is set to previous PWD before changing"
echo "   - Both are exported environment variables"
echo
echo "3. SPECIAL cd - BEHAVIOR:"
echo "   - Prints the destination directory to stdout"
echo "   - Example output: '/home/user' (just the path)"
echo "   - Only prints when successfully changing directory"
echo
echo "4. ERROR HANDLING:"
echo "   - Return 0 on success, 1 on failure"
echo "   - Error messages go to stderr"
echo "   - Format: 'bash: cd: <path>: <error_message>'"
echo "   - HOME not set: 'bash: cd: HOME not set'"
echo "   - OLDPWD not set: 'bash: cd: OLDPWD not set'"
echo
echo "5. DIRECTORY VALIDATION:"
echo "   - Must exist and be accessible"
echo "   - Must be a directory (not a file)"
echo "   - Permission denied shows appropriate error"
echo
echo "6. PATH RESOLUTION:"
echo "   - Relative paths resolved from current directory"
echo "   - Absolute paths used as-is"
echo "   - . refers to current directory"
echo "   - .. refers to parent directory"
echo "   - ~ expands to HOME"
echo
echo "7. EDGE CASES:"
echo "   - cd to current directory still updates PWD/OLDPWD"
echo "   - cd with no HOME variable fails"
echo "   - cd - with no OLDPWD variable fails"
echo "   - Multiple arguments to cd uses only the first"
echo

# Return to original directory
cd "$ORIGINAL_DIR"
echo "Returned to original directory: $(pwd)"
echo
echo "Run this script with: bash bash_cd_reference.sh"
echo "Compare output with your ft_cd implementation!"