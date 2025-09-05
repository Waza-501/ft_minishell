/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_pwd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 14:55:47 by haile         #+#    #+#                 */
/*   Updated: 2025/09/05 14:56:19 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
 * COMPILATION INSTRUCTIONS:
 *
 * 1. Place this file in your project directory alongside your ft_pwd.c and minishell.h
 * 2. Compile with your existing files:
 *    gcc -Wall -Wextra -Werror test_pwd.c [your_pwd_file.c] [libft files] -o test_pwd
 * 3. Run: ./test_pwd
 *
 * Your ft_pwd function signature: int ft_pwd(void)
 *
 * EXPECTED BEHAVIOR NOTES:
 * - Your ft_pwd() function should take no parameters (correct!)
 * - Should always print absolute path followed by newline
 * - Should return 0 on success, 1 on failure (bash-compatible)
 * - Your ft_getcwd() helper function uses PATH_MAX buffer (good practice)
 * - Memory management looks correct with ft_malloc/free pattern
 * - No option parsing needed - pwd accepts no arguments per minishell spec
 * - Should work in any directory (root, deep paths, special chars, etc.)
 * - Unlike echo, pwd can legitimately fail (rare filesystem errors)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>

// Mock the dependencies for your ft_pwd function
// Replace these with your actual headers/functions
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

// Mock ft_malloc if you don't have libft linked
#ifndef HAVE_LIBFT
void *ft_malloc(size_t size)
{
    return malloc(size);
}
#endif

// Include your actual ft_pwd implementation here or link it during compilation
// This is just a placeholder - use your actual function
extern int ft_pwd(void);
extern char *ft_getcwd(void);

/**
 * @brief Test ft_pwd in current directory
 */
void test_basic_pwd(void)
{
    int result;
    
    printf("=== Test 1: Basic pwd functionality ===\n");
    printf("Your ft_pwd output: ");
    fflush(stdout);
    result = ft_pwd();
    printf("Return value: %d\n", result);
    printf("Expected return: 0 (success)\n\n");
}

/**
 * @brief Test ft_pwd in different directories
 */
void test_pwd_different_directories(void)
{
    char *original_dir;
    char buffer[PATH_MAX];
    int result;
    
    printf("=== Test 2: pwd in different directories ===\n");
    
    // Save current directory
    original_dir = getcwd(buffer, sizeof(buffer));
    if (!original_dir)
    {
        printf("Error: Could not get current directory for test setup\n");
        return;
    }
    
    // Test in root directory
    if (chdir("/") == 0)
    {
        printf("Testing in root directory:\n");
        printf("Your ft_pwd output: ");
        fflush(stdout);
        result = ft_pwd();
        printf("Return value: %d\n", result);
        
        // Return to original directory
        chdir(original_dir);
    }
    
    // Test in /tmp if it exists
    if (chdir("/tmp") == 0)
    {
        printf("\nTesting in /tmp directory:\n");
        printf("Your ft_pwd output: ");
        fflush(stdout);
        result = ft_pwd();
        printf("Return value: %d\n", result);
        
        // Return to original directory
        chdir(original_dir);
    }
    
    // Test in parent directory
    if (chdir("..") == 0)
    {
        printf("\nTesting in parent directory:\n");
        printf("Your ft_pwd output: ");
        fflush(stdout);
        result = ft_pwd();
        printf("Return value: %d\n", result);
        
        // Return to original directory
        chdir(original_dir);
    }
    
    printf("\n");
}

/**
 * @brief Test ft_getcwd helper function independently
 */
void test_ft_getcwd_helper(void)
{
    char *pwd_result;
    
    printf("=== Test 3: ft_getcwd helper function ===\n");
    pwd_result = ft_getcwd();
    
    if (pwd_result)
    {
        printf("ft_getcwd returned: %s\n", pwd_result);
        printf("String length: %zu\n", strlen(pwd_result));
        printf("Starts with '/': %s\n", (pwd_result[0] == '/') ? "Yes" : "No");
        free(pwd_result);
        printf("Helper function test: PASSED\n");
    }
    else
    {
        printf("ft_getcwd returned: NULL\n");
        printf("Helper function test: FAILED\n");
    }
    printf("\n");
}

/**
 * @brief Test memory management - multiple calls
 */
void test_memory_management(void)
{
    int i;
    int all_passed = 1;
    
    printf("=== Test 4: Memory management (multiple calls) ===\n");
    printf("Calling ft_pwd 10 times to test for memory leaks...\n");
    
    for (i = 0; i < 10; i++)
    {
        int result = ft_pwd();
        if (result != 0)
        {
            printf("Call %d failed with return value %d\n", i + 1, result);
            all_passed = 0;
        }
    }
    
    printf("Memory test: %s\n", all_passed ? "PASSED" : "FAILED");
    printf("Note: Run with valgrind to check for actual memory leaks\n");
    printf("Command: valgrind --leak-check=full ./test_pwd\n\n");
}

/**
 * @brief Test edge cases and error conditions
 */
void test_edge_cases(void)
{
    printf("=== Test 5: Edge cases ===\n");
    printf("Testing pwd in current directory (edge case testing):\n");
    
    // Test with very long path (if possible)
    char long_path[PATH_MAX];
    char *cwd = getcwd(long_path, sizeof(long_path));
    
    if (cwd && strlen(cwd) > 100)
    {
        printf("Current path is long (%zu chars), testing:\n", strlen(cwd));
        printf("Your ft_pwd output: ");
        fflush(stdout);
        ft_pwd();
    }
    else
    {
        printf("Current path is normal length, no special edge case\n");
        printf("Your ft_pwd output: ");
        fflush(stdout);
        ft_pwd();
    }
    
    printf("Edge case testing completed\n\n");
}

/**
 * @brief Compare output format with system pwd
 */
void test_output_format(void)
{
    char system_pwd[PATH_MAX];
    FILE *fp;
    
    printf("=== Test 6: Output format comparison ===\n");
    
    // Get system pwd output
    fp = popen("pwd", "r");
    if (fp && fgets(system_pwd, sizeof(system_pwd), fp))
    {
        // Remove trailing newline from system_pwd for comparison
        size_t len = strlen(system_pwd);
        if (len > 0 && system_pwd[len - 1] == '\n')
            system_pwd[len - 1] = '\0';
        
        printf("System pwd output: %s\n", system_pwd);
        printf("Your ft_pwd output: ");
        fflush(stdout);
        ft_pwd();
        
        pclose(fp);
        printf("Compare the two outputs above - they should be identical\n");
    }
    else
    {
        printf("Could not run system pwd for comparison\n");
        printf("Your ft_pwd output: ");
        fflush(stdout);
        ft_pwd();
    }
    
    printf("\n");
}

int main(void)
{
    printf("=== MINISHELL FT_PWD TEST HARNESS ===\n");
    printf("Testing your ft_pwd implementation\n");
    printf("Make sure to compile with: gcc -Wall -Wextra -Werror test_pwd.c [your_files] -o test_pwd\n\n");
    
    test_basic_pwd();
    test_pwd_different_directories();
    test_ft_getcwd_helper();
    test_memory_management();
    test_edge_cases();
    test_output_format();
    
    printf("=== TEST SUMMARY ===\n");
    printf("✅ If all outputs show absolute paths starting with '/'\n");
    printf("✅ If return values are 0 (success)\n");
    printf("✅ If output matches system pwd exactly\n");
    printf("✅ If no memory leaks when run with valgrind\n");
    printf("\n");
    printf("❌ If any return values are 1 (unless in broken filesystem)\n");
    printf("❌ If output doesn't start with '/'\n");
    printf("❌ If output differs from system pwd\n");
    printf("❌ If memory leaks detected by valgrind\n");
    printf("\n");
    printf("Run bash_pwd_reference.sh to see expected bash behavior\n");
    
    return 0;
}