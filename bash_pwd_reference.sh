#!/bin/bash

# Bash PWD Reference - Understanding the behavior you need to replicate

echo "=== BASH PWD BEHAVIOR REFERENCE ==="
echo

echo "Test 1: Basic pwd"
echo -n "bash: "
pwd
echo "Exit status: $?"
echo

echo "Test 2: pwd with no arguments (standard usage)"
echo -n "bash: "
pwd
echo "Exit status: $?"
echo

echo "Test 3: pwd should NOT accept options in minishell"
echo "Note: Real bash supports options, but minishell should NOT"
echo -n "bash with -L: "
pwd -L 2>/dev/null || echo "Error: $?"
echo -n "bash with -P: "
pwd -P 2>/dev/null || echo "Error: $?"
echo -n "bash with --help: "
pwd --help 2>/dev/null | head -1 || echo "Error: $?"
echo "^ Your minishell should reject ALL of these options"
echo

echo "Test 4: pwd with arguments (should fail)"
echo -n "bash with argument: "
pwd extra_argument 2>&1
echo "Exit status: $?"
echo "^ Your minishell should also fail with extra arguments"
echo

echo "Test 5: pwd in different directories"
ORIGINAL_DIR=$(pwd)
echo "Current directory:"
echo -n "bash: "
pwd

if cd /tmp 2>/dev/null; then
    echo "In /tmp directory:"
    echo -n "bash: "
    pwd
    cd "$ORIGINAL_DIR"
fi

if cd / 2>/dev/null; then
    echo "In root directory:"
    echo -n "bash: "
    pwd
    cd "$ORIGINAL_DIR"
fi

if cd .. 2>/dev/null; then
    echo "In parent directory:"
    echo -n "bash: "
    pwd
    cd "$ORIGINAL_DIR"
fi
echo

echo "Test 6: pwd output format"
echo "pwd output should be:"
echo "1. Absolute path starting with '/'"
echo "2. No trailing spaces"
echo "3. Single newline at the end"
echo "4. No additional text or formatting"
echo
echo -n "Example: "
pwd
echo "^ Exactly like that"
echo

echo "Test 7: pwd in paths with special characters"
# Create a test directory with spaces and special chars if possible
SPECIAL_DIR="/tmp/test dir with spaces"
if mkdir -p "$SPECIAL_DIR" 2>/dev/null; then
    echo "Testing in directory with spaces:"
    if cd "$SPECIAL_DIR" 2>/dev/null; then
        echo -n "bash: "
        pwd
        cd "$ORIGINAL_DIR"
        rmdir "$SPECIAL_DIR" 2>/dev/null
    fi
else
    echo "Could not create test directory with special characters"
fi
echo

echo "Test 8: pwd never fails under normal conditions"
echo "pwd should return 0 (success) unless there are serious filesystem issues"
echo -n "Normal pwd exit status: "
pwd >/dev/null
echo $?
echo

echo "Test 9: pwd with symlinks"
echo "pwd resolves symlinks and shows the real path:"
# Create a symlink test if possible
LINK_TEST="/tmp/pwd_link_test"
if ln -sf "$ORIGINAL_DIR" "$LINK_TEST" 2>/dev/null; then
    echo "Created symlink: $LINK_TEST -> $ORIGINAL_DIR"
    if cd "$LINK_TEST" 2>/dev/null; then
        echo -n "pwd via symlink: "
        pwd
        echo "Note: Shows resolved real path, not symlink path"
        cd "$ORIGINAL_DIR"
        rm -f "$LINK_TEST"
    fi
else
    echo "Could not create symlink for test"
fi
echo

echo "=== KEY BEHAVIORS FOR MINISHELL ==="
echo "1. pwd takes NO arguments (fail if any provided)"
echo "2. pwd takes NO options (fail if any provided)"
echo "3. Always print absolute path starting with '/'"
echo "4. Always end with exactly one newline"
echo "5. Return 0 on success, 1 on error"
echo "6. Use getcwd() system call (like your ft_getcwd)"
echo "7. Handle memory allocation/deallocation properly"
echo

echo "=== DIFFERENCES FROM FULL BASH ==="
echo "❌ Minishell should NOT support: -L, -P, --help options"
echo "❌ Minishell should NOT accept any arguments"
echo "✅ Minishell should behave like: pwd (no args, no options)"
echo

echo "=== ERROR CASES (rare) ==="
echo "pwd can fail if:"
echo "- Current directory is deleted while shell is in it"
echo "- Filesystem corruption or permission issues"
echo "- getcwd() system call fails"
echo "In these cases, return 1 and handle gracefully"
echo

echo "=== TESTING YOUR IMPLEMENTATION ==="
echo "1. Compile: gcc -Wall -Wextra -Werror test_pwd.c [your_files] -o test_pwd"
echo "2. Run: ./test_pwd"
echo "3. Check: valgrind --leak-check=full ./test_pwd"
echo "4. Compare output with this script: bash bash_pwd_reference.sh"
echo

echo "Current working directory for reference:"
echo -n "bash: "
pwd
echo

echo "=== END OF REFERENCE ==="