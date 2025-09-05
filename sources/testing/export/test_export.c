/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_export.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 15:03:36 by haile         #+#    #+#                 */
/*   Updated: 2025/09/05 15:03:37 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
 * COMPILATION INSTRUCTIONS:
 * 
 * 1. Place this file in your project directory alongside your ft_export.c
 * 2. Compile with your existing files:
 *    gcc -Wall -Wextra -Werror test_export.c [your_export_file.c] [other_required_files.c] -o test_export
 * 3. Run: ./test_export
 * 
 * Your ft_export function signature: int ft_export(t_cmds *cmd, t_shell *shell, char *str)
 * 
 * EXPECTED BEHAVIOR NOTES:
 * - export without args should print sorted environment (like bash)
 * - export VAR=value should add/update variable in environment
 * - export VAR (no =) should mark existing variable for export or create empty
 * - Invalid identifiers (starting with digit, containing special chars) should error
 * - Should return 0 on success, 1 on error
 * - Must handle memory allocation properly (grow environment array)
 * - Format: declare -x VAR="value" when printing all exports
 * - Should validate identifier: [a-zA-Z_][a-zA-Z0-9_]*
 * - export VAR+= should append to existing variable (bonus behavior)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Mock structures for testing (replace with your actual headers)
typedef struct s_cmds {
    char **str;  // Array of command arguments
} t_cmds;

typedef struct s_shell {
    char **env;
    int env_count;
} t_shell;

// Your function prototype (implement this in your export file)
int ft_export(t_cmds *cmd, t_shell *shell, char *str);

// Test helper functions
t_shell *init_test_shell(char **envp)
{
    t_shell *shell = malloc(sizeof(t_shell));
    int count = 0;
    int i = 0;
    
    // Count environment variables
    while (envp[count])
        count++;
    
    shell->env = malloc(sizeof(char*) * (count + 10)); // Extra space
    shell->env_count = count;
    
    // Copy environment
    while (i < count)
    {
        shell->env[i] = strdup(envp[i]);
        i++;
    }
    shell->env[i] = NULL;
    
    return shell;
}

void free_test_shell(t_shell *shell)
{
    int i = 0;
    while (shell->env[i])
    {
        free(shell->env[i]);
        i++;
    }
    free(shell->env);
    free(shell);
}

t_cmds *create_test_cmd(char **args)
{
    t_cmds *cmd = malloc(sizeof(t_cmds));
    int count = 0;
    int i = 0;
    
    // Count arguments
    while (args[count])
        count++;
    
    cmd->str = malloc(sizeof(char*) * (count + 1));
    
    // Copy arguments
    while (i < count)
    {
        cmd->str[i] = strdup(args[i]);
        i++;
    }
    cmd->str[i] = NULL;
    
    return cmd;
}

void free_test_cmd(t_cmds *cmd)
{
    int i = 0;
    while (cmd->str[i])
    {
        free(cmd->str[i]);
        i++;
    }
    free(cmd->str);
    free(cmd);
}

void print_env(t_shell *shell)
{
    int i = 0;
    printf("Current environment:\n");
    while (shell->env[i])
    {
        printf("  %s\n", shell->env[i]);
        i++;
    }
    printf("\n");
}

void test_export_case(t_shell *shell, char **args, char *description)
{
    t_cmds *cmd = create_test_cmd(args);
    int result;
    
    printf("=== %s ===\n", description);
    printf("Command: ");
    int i = 0;
    while (args[i])
    {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
    
    result = ft_export(cmd, shell, NULL);
    printf("Return value: %d\n", result);
    printf("\n");
    
    free_test_cmd(cmd);
}

int main(int argc, char **argv, char **envp)
{
    t_shell *shell = init_test_shell(envp);
    
    printf("=== EXPORT BUILTIN TEST ===\n\n");
    
    // Test 1: export without arguments (should list all exports)
    char *test1[] = {"export", NULL};
    test_export_case(shell, test1, "Export without arguments");
    
    // Test 2: export new variable with value
    char *test2[] = {"export", "TEST_VAR=hello", NULL};
    test_export_case(shell, test2, "Export new variable with value");
    
    // Test 3: export new variable without value
    char *test3[] = {"export", "EMPTY_VAR", NULL};
    test_export_case(shell, test3, "Export variable without value");
    
    // Test 4: export existing variable (modify PATH)
    char *test4[] = {"export", "PATH=/new/test/path", NULL};
    test_export_case(shell, test4, "Modify existing variable");
    
    // Test 5: Invalid identifier - starts with digit
    char *test5[] = {"export", "123INVALID=test", NULL};
    test_export_case(shell, test5, "Invalid identifier (starts with digit)");
    
    // Test 6: Invalid identifier - contains special characters
    char *test6[] = {"export", "VAR-NAME=test", NULL};
    test_export_case(shell, test6, "Invalid identifier (contains dash)");
    
    // Test 7: Invalid identifier - starts with equals
    char *test7[] = {"export", "=value", NULL};
    test_export_case(shell, test7, "Invalid identifier (starts with =)");
    
    // Test 8: export with empty value
    char *test8[] = {"export", "EMPTY=", NULL};
    test_export_case(shell, test8, "Export with empty value");
    
    // Test 9: export multiple variables
    char *test9[] = {"export", "VAR1=value1", "VAR2=value2", NULL};
    test_export_case(shell, test9, "Export multiple variables");
    
    // Test 10: export with special characters in value
    char *test10[] = {"export", "SPECIAL_VAR=hello world test", NULL};
    test_export_case(shell, test10, "Export with spaces in value");
    
    // Show final environment state
    printf("=== FINAL ENVIRONMENT STATE ===\n");
    print_env(shell);
    
    free_test_shell(shell);
    
    printf("=== Test completed ===\n");
    printf("Compare output with bash_export_reference.sh\n");
    
    return 0;
}