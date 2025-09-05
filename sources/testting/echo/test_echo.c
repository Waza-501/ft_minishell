/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_echo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 14:01:31 by haile         #+#    #+#                 */
/*   Updated: 2025/09/05 14:35:22 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "libft.h"

// Forward declaration of your ft_echo function
int ft_echo(t_cmds *cmd);

/**
 * @brief Create a mock command structure for testing
 * @param args Null-terminated array of string arguments
 * @return Allocated t_cmds structure
 */
t_cmds *create_test_cmd(char **args)
{
    t_cmds *cmd;
    int argc = 0;
    
    // Count arguments
    while (args[argc])
        argc++;
    
    cmd = malloc(sizeof(t_cmds));
    if (!cmd)
        return NULL;
    
    // Initialize structure
    cmd->str = malloc((argc + 1) * sizeof(char *));
    if (!cmd->str) {
        free(cmd);
        return NULL;
    }
    
    // Copy arguments
    for (int i = 0; i < argc; i++) {
        cmd->str[i] = strdup(args[i]);
        if (!cmd->str[i]) {
            // Cleanup on allocation failure
            for (int j = 0; j < i; j++)
                free(cmd->str[j]);
            free(cmd->str);
            free(cmd);
            return NULL;
        }
    }
    cmd->str[argc] = NULL;
    
    // Initialize other fields
    cmd->redir = NULL;
    cmd->n = argc;
    cmd->pid = 0;
    cmd->pipefd[0] = -1;
    cmd->pipefd[1] = -1;
    cmd->heredoc = NULL;
    cmd->next = NULL;
    
    return cmd;
}

/**
 * @brief Free a test command structure
 * @param cmd Command structure to free
 */
void free_test_cmd(t_cmds *cmd)
{
    if (!cmd)
        return;
    
    if (cmd->str) {
        for (int i = 0; cmd->str[i]; i++) {
            free(cmd->str[i]);
        }
        free(cmd->str);
    }
    
    free(cmd);
}

/**
 * @brief Test runner function
 * @param test_name Name of the test case
 * @param args Arguments to pass to ft_echo (including "echo" as first arg)
 */
void run_test(const char *test_name, char **args)
{
    printf("\n=== TEST: %s ===\n", test_name);
    
    // Show the command being tested
    printf("Command: ");
    for (int i = 0; args[i]; i++) {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
    }
    printf("\n");
    
    // Test your implementation
    printf("Your ft_echo output: ");
    fflush(stdout);
    
    t_cmds *cmd = create_test_cmd(args);
    if (cmd) {
        int exit_code = ft_echo(cmd);
        printf("(exit: %d)", exit_code);
        free_test_cmd(cmd);
    } else {
        printf("ERROR: Failed to create test command");
    }
    
    printf("\nReal bash output:    ");
    fflush(stdout);
    
    // Compare with real bash
    char bash_cmd[1024] = "";
    for (int i = 0; args[i]; i++) {
        if (i > 0)
            strcat(bash_cmd, " ");
        
        // Handle arguments with spaces or special characters
        if (strchr(args[i], ' ') || strchr(args[i], '\t')) {
            strcat(bash_cmd, "'");
            strcat(bash_cmd, args[i]);
            strcat(bash_cmd, "'");
        } else {
            strcat(bash_cmd, args[i]);
        }
    }
    
    system(bash_cmd);
    printf("---\n");
}

int main(void)
{
    printf("MINISHELL FT_ECHO TESTING SUITE\n");
    printf("===============================\n");
    printf("Testing your ft_echo implementation against bash behavior\n");
    
    // Test cases based on your implementation and bash behavior
    
    // Test 1: Basic echo
    char *test1[] = {"echo", "Hello", "World", NULL};
    run_test("Basic echo", test1);
    
    // Test 2: Echo with single -n flag
    char *test2[] = {"echo", "-n", "Hello", "World", NULL};
    run_test("Single -n flag", test2);
    
    // Test 3: Echo with no arguments
    // char *test3[] = {"echo", NULL};
    // run_test("No arguments", test3);
    
    // Test 4: Echo with -n only
    // char *test4[] = {"echo", "-n", NULL};
    // run_test("Only -n flag", test4);
    
    // Test 5: Multiple -n flags (your implementation should handle this)
    char *test5[] = {"echo", "-n", "-n", "test", NULL};
    run_test("Multiple -n flags", test5);
    
    // Test 6: Extended -n flag (-nn, -nnn)
    char *test6[] = {"echo", "-nn", "test", NULL};
    run_test("Extended -n flag (-nn)", test6);
    
    // Test 7: Mixed extended -n flags
    char *test7[] = {"echo", "-nnn", "-nn", "hello", NULL};
    run_test("Mixed extended -n flags", test7);
    
    // Test 8: Invalid -n flag (mixed with other chars)
    char *test8[] = {"echo", "-nx", "hello", NULL};
    run_test("Invalid -n flag (-nx)", test8);
    
    // Test 9: -n not at beginning
    char *test9[] = {"echo", "hello", "-n", "world", NULL};
    run_test("-n not at beginning", test9);
    
    // Test 10: Empty string arguments
    char *test10[] = {"echo", "Hello", "", "World", NULL};
    run_test("Empty string argument", test10);
    
    // Test 11: Multiple spaces between args (handled by shell parsing)
    char *test11[] = {"echo", "Hello", "World", NULL};
    run_test("Regular spacing", test11);
    
    // Test 12: Special characters
    char *test12[] = {"echo", "Hello\tWorld", NULL};
    run_test("Tab character", test12);
    
    // Test 13: Long argument list
    char *test13[] = {"echo", "-n", "This", "is", "a", "very", "long", 
                     "list", "of", "arguments", "to", "test", NULL};
    run_test("Long argument list", test13);
    
    // Test 14: Edge case - argument starting with -n but not a flag
    char *test14[] = {"echo", "-ntest", NULL};
    run_test("Argument starting with -n", test14);
    
    // Test 15: Multiple different -n variations
    char *test15[] = {"echo", "-n", "-nn", "-nnn", "test", NULL};
    run_test("Multiple -n variations", test15);
    
    printf("\n=== TESTING COMPLETE ===\n");
    printf("Your implementation should match bash output exactly.\n");
    printf("Pay special attention to:\n");
    printf("1. Newline handling with -n flags\n");
    printf("2. Multiple consecutive -n flags\n");
    printf("3. Extended -n flags (-nn, -nnn, etc.)\n");
    printf("4. Invalid -n combinations\n");
    printf("5. Exit codes (should always be 0)\n");
    
    return 0;
}

/*
 * COMPILATION INSTRUCTIONS:
 * 
 * 1. Place this file in your project directory alongside your ft_echo.c
 * 2. Compile with your existing files:
 *    gcc -Wall -Wextra -Werror test_echo.c [your_echo_file.c] [other_required_files.c] -o test_echo
 * 3. Run: ./test_echo
 * 
 * Your ft_echo function signature: int ft_echo(t_cmds *cmd)
 * 
 * EXPECTED BEHAVIOR NOTES:
 * - Your implementation handles consecutive -n flags (good!)
 * - The last_check function should properly advance through multiple -n args
 * - check_n function validates the first -n flag correctly
 * - Should always return 0 (success)
 */