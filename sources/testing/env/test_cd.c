/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_cd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 15:13:23 by haile         #+#    #+#                 */
/*   Updated: 2025/09/05 15:13:24 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
 * COMPILATION INSTRUCTIONS:
 *
 * 1. Place this file in your project directory alongside your ft_cd.c
 * 2. Compile with your existing files:
 *    gcc -Wall -Wextra -Werror test_cd.c ft_cd.c [other_required_files.c] libft/libft.a -o test_cd
 * 3. Run: ./test_cd
 *
 * Your ft_cd function signature: int ft_cd(t_cmds *cmd, t_shell *shell)
 *
 * EXPECTED BEHAVIOR NOTES:
 * - cd with no arguments should go to HOME directory
 * - cd - should go to OLDPWD and print the destination directory (bash behavior)
 * - cd <path> should change to specified directory
 * - Should update PWD and OLDPWD environment variables correctly
 * - Error messages should match bash format exactly
 * - Return 1 on both success and failure (shell convention, not standard)
 * - Must handle missing HOME/OLDPWD gracefully
 *
 * COMPARISON WITH BASH:
 * - Bash prints destination when using 'cd -'
 * - Bash returns 0 on success, 1 on failure
 * - Your implementation returns 1 always (shell-specific)
 * - Error format: "minishell: cd: <path>: <error_message>"
 * - Missing var format: "minishell: cd: HOME not set" / "minishell: cd: OLDPWD not set"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

// Mock your structures if headers not available
typedef struct s_shell {
    char **env;
} t_shell;

typedef struct s_cmds {
    char **str;
} t_cmds;

// Add your function prototypes here
int ft_cd(t_cmds *cmd, t_shell *shell);
// Add other function prototypes as needed

// Test utility functions
void print_separator(const char *test_name) {
    printf("\n" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "\n");
    printf("TEST: %s\n", test_name);
    printf("=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "\n");
}

void print_current_state(void) {
    char *cwd = getcwd(NULL, 0);
    printf("Current directory: %s\n", cwd ? cwd : "ERROR");
    if (cwd) free(cwd);
}

void print_env_var(t_shell *shell, const char *var_name) {
    int i = 0;
    int len = strlen(var_name);
    
    while (shell->env[i]) {
        if (strncmp(shell->env[i], var_name, len) == 0) {
            printf("%s\n", shell->env[i]);
            return;
        }
        i++;
    }
    printf("%s(not set)\n", var_name);
}

// Create test environment from real environment
char **create_test_env(void) {
    extern char **environ;
    int count = 0;
    int i;
    
    // Count environment variables
    while (environ[count]) count++;
    
    char **test_env = malloc(sizeof(char*) * (count + 1));
    if (!test_env) return NULL;
    
    // Copy environment
    for (i = 0; i < count; i++) {
        test_env[i] = strdup(environ[i]);
        if (!test_env[i]) {
            while (--i >= 0) free(test_env[i]);
            free(test_env);
            return NULL;
        }
    }
    test_env[count] = NULL;
    return test_env;
}

void free_test_env(char **env) {
    int i = 0;
    while (env[i]) {
        free(env[i]);
        i++;
    }
    free(env);
}

// Create test command
t_cmds *create_test_cmd(char **args) {
    t_cmds *cmd = malloc(sizeof(t_cmds));
    if (!cmd) return NULL;
    cmd->str = args;
    return cmd;
}

// Run a single test
void run_test(const char *test_name, char **args, t_shell *shell) {
    t_cmds *cmd;
    int result;
    
    print_separator(test_name);
    
    printf("Command: cd");
    int i = 1;
    while (args[i]) {
        printf(" %s", args[i]);
        i++;
    }
    printf("\n\n");
    
    printf("BEFORE:\n");
    print_current_state();
    print_env_var(shell, "PWD=");
    print_env_var(shell, "OLDPWD=");
    
    printf("\nEXECUTING ft_cd...\n");
    cmd = create_test_cmd(args);
    if (cmd) {
        result = ft_cd(cmd, shell);
        printf("ft_cd returned: %d\n", result);
        free(cmd);
    }
    
    printf("\nAFTER:\n");
    print_current_state();
    print_env_var(shell, "PWD=");
    print_env_var(shell, "OLDPWD=");
}

int main(void) {
    t_shell shell;
    char **args;
    
    printf("MINISHELL FT_CD TESTING FRAMEWORK\n");
    printf("==================================\n");
    printf("Testing your ft_cd implementation against bash behavior\n");
    printf("Run bash_cd_reference.sh to see expected bash output\n");
    
    // Initialize shell with real environment
    shell.env = create_test_env();
    if (!shell.env) {
        printf("ERROR: Failed to create test environment\n");
        return 1;
    }
    
    printf("\nINITIAL STATE:\n");
    print_current_state();
    print_env_var(&shell, "HOME=");
    print_env_var(&shell, "OLDPWD=");
    
    // Test 1: cd with no arguments (go to HOME)
    args = (char*[]){"cd", NULL};
    run_test("cd (no arguments - should go to HOME)", args, &shell);
    
    // Test 2: cd to /tmp
    args = (char*[]){"cd", "/tmp", NULL};
    run_test("cd /tmp", args, &shell);
    
    // Test 3: cd - (go to previous directory)
    args = (char*[]){"cd", "-", NULL};
    run_test("cd - (should go to previous directory and print it)", args, &shell);
    
    // Test 4: cd to home directory explicitly with ~
    args = (char*[]){"cd", "~", NULL};
    run_test("cd ~ (should go to HOME - if supported)", args, &shell);
    
    // Test 5: cd to a non-existent directory
    args = (char*[]){"cd", "/this/path/does/not/exist", NULL};
    run_test("cd /this/path/does/not/exist (should fail)", args, &shell);
    
    // Test 6: cd .. (parent directory)
    args = (char*[]){"cd", "..", NULL};
    run_test("cd .. (parent directory)", args, &shell);
    
    // Test 7: cd . (current directory)
    args = (char*[]){"cd", ".", NULL};
    run_test("cd . (current directory)", args, &shell);
    
    // Test 8: cd with relative path
    args = (char*[]){"cd", "usr", NULL};
    run_test("cd usr (relative path - may fail if usr doesn't exist)", args, &shell);
    
    print_separator("TESTING COMPLETE");
    printf("NOTES:\n");
    printf("1. Compare output with bash_cd_reference.sh\n");
    printf("2. Check that PWD and OLDPWD are updated correctly\n");
    printf("3. Verify error messages match bash format\n");
    printf("4. Test 'cd -' should print destination directory (bash behavior)\n");
    printf("5. All directory changes should be persistent\n");
    printf("6. Your ft_cd should return 1 always (shell convention)\n");
    
    // Cleanup
    free_test_env(shell.env);
    return 0;
}