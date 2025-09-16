/*
 * COMPILATION INSTRUCTIONS:
 *
 * 1. Place this file in your project directory alongside your ft_unset.c
 * 2. Compile with your existing files:
 *    gcc -Wall -Wextra -Werror test_unset.c ft_unset.c [libft files] [other_required_files.c] -o test_unset
 * 3. Run: ./test_unset
 *
 * Your ft_unset function signature: int ft_unset(t_cmds *cmd, t_shell *shell)
 *
 * EXPECTED BEHAVIOR NOTES:
 * - unset with no arguments should return 0 (success) and do nothing
 * - unset with non-existent variables should return 0 (not an error in bash)
 * - unset should only remove exact variable name matches (not partial)
 * - unset should handle multiple variables in one command
 * - Invalid variable names should cause error (return 1) in bash, but your implementation may vary
 * - Memory management should be clean (no leaks)
 * 
 * CRITICAL BUG IN YOUR IMPLEMENTATION:
 * Your unset_array() function has incorrect string comparison logic!
 * It uses ft_strncmp(env[i], str, ft_strlen(str)) which will incorrectly
 * match partial variable names. For example, trying to unset "PATH" would
 * also remove "PATHEXT" or "PATHNAME". You need to use the same boundary
 * checking logic as your in_env() function.
 *
 * BASH COMPATIBILITY NOTES:
 * - bash unset returns 0 for non-existent variables
 * - bash unset validates variable names (letters, digits, underscore only)
 * - bash unset prints error for invalid variable names but continues processing
 * - bash unset processes all arguments even if some are invalid
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Mock structures - adjust these to match your actual implementation
typedef struct s_cmds {
    char **str;  // Array of command arguments
} t_cmds;

typedef struct s_shell {
    char **env;  // Environment variables array
} t_shell;

// Your function prototype
int ft_unset(t_cmds *cmd, t_shell *shell);

// Helper functions for testing
char **create_test_env(void)
{
    char **env = malloc(sizeof(char*) * 6);
    env[0] = strdup("PATH=/usr/bin:/bin");
    env[1] = strdup("HOME=/home/user");
    env[2] = strdup("USER=testuser");
    env[3] = strdup("PATHEXT=.exe:.bat");
    env[4] = strdup("PS1=$");
    env[5] = NULL;
    return env;
}

void free_env(char **env)
{
    if (!env) return;
    for (int i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}

void print_env(char **env, const char *label)
{
    printf("%s:\n", label);
    if (!env) {
        printf("  (NULL)\n");
        return;
    }
    for (int i = 0; env[i]; i++)
        printf("  [%d] %s\n", i, env[i]);
    printf("  [%d] (NULL)\n", i);
    printf("\n");
}

int count_env_vars(char **env)
{
    if (!env) return 0;
    int count = 0;
    while (env[count]) count++;
    return count;
}

bool env_contains(char **env, const char *var_name)
{
    if (!env || !var_name) return false;
    int len = strlen(var_name);
    for (int i = 0; env[i]; i++) {
        if (strncmp(env[i], var_name, len) == 0 && 
            (env[i][len] == '=' || env[i][len] == '\0'))
            return true;
    }
    return false;
}

// Test cases
void test_no_arguments(void)
{
    printf("=== TEST 1: No Arguments ===\n");
    
    t_shell shell;
    shell.env = create_test_env();
    
    t_cmds cmd;
    char *args[] = {"unset", NULL};
    cmd.str = args;
    
    int original_count = count_env_vars(shell.env);
    int result = ft_unset(&cmd, &shell);
    int new_count = count_env_vars(shell.env);
    
    printf("Arguments: unset\n");
    printf("Expected: Return 0, no changes to environment\n");
    printf("Result: Return %d, env count %d -> %d\n", result, original_count, new_count);
    printf("Status: %s\n\n", (result == 0 && original_count == new_count) ? "PASS" : "FAIL");
    
    free_env(shell.env);
}

void test_single_existing_var(void)
{
    printf("=== TEST 2: Single Existing Variable ===\n");
    
    t_shell shell;
    shell.env = create_test_env();
    
    t_cmds cmd;
    char *args[] = {"unset", "HOME", NULL};
    cmd.str = args;
    
    print_env(shell.env, "Before unset HOME");
    
    int result = ft_unset(&cmd, &shell);
    
    print_env(shell.env, "After unset HOME");
    
    bool home_still_exists = env_contains(shell.env, "HOME");
    printf("Arguments: unset HOME\n");
    printf("Expected: Return 0, HOME should be removed\n");
    printf("Result: Return %d, HOME exists: %s\n", result, home_still_exists ? "YES" : "NO");
    printf("Status: %s\n\n", (result == 0 && !home_still_exists) ? "PASS" : "FAIL");
    
    free_env(shell.env);
}

void test_multiple_existing_vars(void)
{
    printf("=== TEST 3: Multiple Existing Variables ===\n");
    
    t_shell shell;
    shell.env = create_test_env();
    
    t_cmds cmd;
    char *args[] = {"unset", "PATH", "USER", NULL};
    cmd.str = args;
    
    print_env(shell.env, "Before unset PATH USER");
    
    int result = ft_unset(&cmd, &shell);
    
    print_env(shell.env, "After unset PATH USER");
    
    bool path_exists = env_contains(shell.env, "PATH");
    bool user_exists = env_contains(shell.env, "USER");
    bool home_exists = env_contains(shell.env, "HOME");  // Should still exist
    
    printf("Arguments: unset PATH USER\n");
    printf("Expected: Return 0, PATH and USER removed, others remain\n");
    printf("Result: Return %d, PATH: %s, USER: %s, HOME: %s\n", 
           result, path_exists ? "EXISTS" : "REMOVED", 
           user_exists ? "EXISTS" : "REMOVED",
           home_exists ? "EXISTS" : "REMOVED");
    printf("Status: %s\n\n", (result == 0 && !path_exists && !user_exists && home_exists) ? "PASS" : "FAIL");
    
    free_env(shell.env);
}

void test_nonexistent_var(void)
{
    printf("=== TEST 4: Non-existent Variable ===\n");
    
    t_shell shell;
    shell.env = create_test_env();
    
    t_cmds cmd;
    char *args[] = {"unset", "NONEXISTENT", NULL};
    cmd.str = args;
    
    int original_count = count_env_vars(shell.env);
    int result = ft_unset(&cmd, &shell);
    int new_count = count_env_vars(shell.env);
    
    printf("Arguments: unset NONEXISTENT\n");
    printf("Expected: Return 0, no changes (bash behavior)\n");
    printf("Result: Return %d, env count %d -> %d\n", result, original_count, new_count);
    printf("Status: %s\n\n", (result == 0 && original_count == new_count) ? "PASS" : "FAIL");
    
    free_env(shell.env);
}

void test_partial_name_bug(void)
{
    printf("=== TEST 5: Partial Name Matching Bug Test ===\n");
    printf("*** THIS TEST WILL LIKELY FAIL WITH YOUR CURRENT IMPLEMENTATION ***\n");
    
    t_shell shell;
    shell.env = create_test_env();
    
    t_cmds cmd;
    char *args[] = {"unset", "PATH", NULL};
    cmd.str = args;
    
    print_env(shell.env, "Before unset PATH");
    
    int result = ft_unset(&cmd, &shell);
    
    print_env(shell.env, "After unset PATH");
    
    bool path_exists = env_contains(shell.env, "PATH");
    bool pathext_exists = env_contains(shell.env, "PATHEXT");  // Should NOT be removed!
    
    printf("Arguments: unset PATH\n");
    printf("Expected: Remove PATH only, keep PATHEXT\n");
    printf("Result: PATH: %s, PATHEXT: %s\n", 
           path_exists ? "EXISTS" : "REMOVED",
           pathext_exists ? "EXISTS" : "REMOVED");
    printf("Status: %s\n", (!path_exists && pathext_exists) ? "PASS" : "FAIL");
    printf("*** If PATHEXT was also removed, your string comparison logic is wrong! ***\n\n");
    
    free_env(shell.env);
}

void test_mixed_existing_nonexistent(void)
{
    printf("=== TEST 6: Mixed Existing and Non-existent Variables ===\n");
    
    t_shell shell;
    shell.env = create_test_env();
    
    t_cmds cmd;
    char *args[] = {"unset", "HOME", "FAKE1", "USER", "FAKE2", NULL};
    cmd.str = args;
    
    print_env(shell.env, "Before unset HOME FAKE1 USER FAKE2");
    
    int result = ft_unset(&cmd, &shell);
    
    print_env(shell.env, "After unset HOME FAKE1 USER FAKE2");
    
    bool home_exists = env_contains(shell.env, "HOME");
    bool user_exists = env_contains(shell.env, "USER");
    bool path_exists = env_contains(shell.env, "PATH");  // Should remain
    
    printf("Arguments: unset HOME FAKE1 USER FAKE2\n");
    printf("Expected: Remove HOME and USER, ignore non-existent ones, keep PATH\n");
    printf("Result: HOME: %s, USER: %s, PATH: %s\n", 
           home_exists ? "EXISTS" : "REMOVED",
           user_exists ? "EXISTS" : "REMOVED",
           path_exists ? "EXISTS" : "REMOVED");
    printf("Status: %s\n\n", (!home_exists && !user_exists && path_exists) ? "PASS" : "FAIL");
    
    free_env(shell.env);
}

void test_empty_environment(void)
{
    printf("=== TEST 7: Empty Environment ===\n");
    
    t_shell shell;
    shell.env = malloc(sizeof(char*));
    shell.env[0] = NULL;  // Empty environment
    
    t_cmds cmd;
    char *args[] = {"unset", "ANYTHING", NULL};
    cmd.str = args;
    
    int result = ft_unset(&cmd, &shell);
    
    printf("Arguments: unset ANYTHING (on empty env)\n");
    printf("Expected: Return 0, no crash\n");
    printf("Result: Return %d\n", result);
    printf("Status: %s\n\n", (result == 0) ? "PASS" : "FAIL");
    
    free(shell.env);
}

int main(void)
{
    printf("=== MINISHELL FT_UNSET TEST SUITE ===\n");
    printf("Testing your ft_unset implementation\n");
    printf("Compare results with bash_unset_reference.sh\n\n");
    
    test_no_arguments();
    test_single_existing_var();
    test_multiple_existing_vars();
    test_nonexistent_var();
    test_partial_name_bug();  // This will likely fail with your current code
    test_mixed_existing_nonexistent();
    test_empty_environment();
    
    printf("=== TEST SUITE COMPLETE ===\n");
    printf("Key Issues to Address:\n");
    printf("1. Fix string comparison in unset_array() function\n");
    printf("2. Consider adding variable name validation\n");
    printf("3. Consider adding error messages for invalid names\n");
    printf("\nRun 'bash bash_unset_reference.sh' to see expected bash behavior\n");
    
    return 0;
}