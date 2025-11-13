/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 09:57:15 by owen          #+#    #+#                 */
/*   Updated: 2025/11/11 14:30:42 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>

void	free_mem(char **mem)
{
	if (*mem != NULL)
	{
		free(*mem);
		*mem = NULL;
	}
}

static char	*find_leftovers(char *remain, char *temp, size_t size)
{
	int		i;

	if (remain[size] == '\0')
		return (free_mem(&remain), NULL);
	temp = ft_calloc(ft_strlen(remain) - size + 1, sizeof(char));
	if (!temp)
		return (free_mem(&remain), NULL);
	i = 0;
	while (remain[size + i])
	{
		temp[i] = remain[size + i];
		i++;
	}
	free_mem(&remain);
	remain = ft_strdup(temp);
	if (!remain)
		return (free_mem(&temp), NULL);
	free_mem(&temp);
	return (remain);
}

static char	*find_line(char *remain)
{
	char	*line;
	int		i;

	i = 0;
	if (!remain)
		return (NULL);
	while (remain[i] != '\n' && remain[i] != '\0')
		i++;
	if (remain[i] == '\n' || remain[i] != '\0')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (remain[i] != '\n' && remain[i] != '\0')
	{
		line[i] = remain[i];
		i++;
	}
	if (remain[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	return (line);
}

static char	*read_file(char *remain, char *buffer, int fd)
{
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && nl_checker(remain) == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_mem(&remain), NULL);
		buffer[bytes_read] = '\0';
		temp = ft_strdup(remain);
		if (!temp)
			return (free_mem(&remain), NULL);
		free_mem(&remain);
		remain = ft_strjoin(temp, buffer);
		free_mem(&temp);
		if (!remain)
			return (NULL);
	}
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remain)
		remain = ft_calloc(1, sizeof(char));
	if (!remain)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free_mem(&remain), NULL);
	remain = read_file(remain, buffer, fd);
	free_mem(&buffer);
	if (!remain || remain[0] == '\0')
		return (free_mem(&remain), NULL);
	line = find_line(remain);
	if (!line)
		return (free_mem(&remain), NULL);
	remain = find_leftovers(remain, buffer, ft_strlen(line));
	return (line);
}

// int main(void)
// {
// 	int	fd;
// 	int	count;
// 	char *gnl;

// 	fd = open("multiple_nl.txt", O_RDONLY);
// 	count = 0;
// 	while (true)
// 	{
// 		gnl = get_next_line(fd);
// 		if (gnl == NULL)
// 		{
// 			printf("broke\n");
// 			break;
// 		}
// 		count++;
// 		printf("[%d]%s", count, gnl);
// 		free(gnl);
// 		gnl = NULL;
// 	}
// 	close (fd);
// 	return (0);
// }