#!/bin/bash

echo "=== Testing ft_export Memory Fix ==="

# # Copy fixed files
# cp /home/claude/ft_export_FIXED.c sources/builtins/ft_export.c
# cp /home/claude/env_sync_SAFE.c sources/executor/env_sync.c

# Compile
echo "Compiling..."
make re

# Test export functionality without persistence
echo "Testing basic export..."
echo 'export TEST="Hello"' | ./minishell
echo 'env | grep TEST' | ./minishell

echo "Test complete. Check for memory leaks above."