/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciardo <lciardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:05:21 by lciardo           #+#    #+#             */
/*   Updated: 2026/02/02 12:13:05 by lciardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_memory(int fd, char *memory)
{
	char	*buffer;
	int		byte_read;
	char	*temp;

	buffer = malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byte_read = 1;
	while (ft_strchr(memory, '\n') == NULL && byte_read != 0)
	{
		byte_read = read (fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free (buffer);
			free (memory);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		temp = ft_strjoin(memory, buffer);
		free (memory);
		memory = temp;
	}
	free (buffer);
	return (memory);
}

char	*ft_get_line(char *memory)
{
	size_t	x;
	char	*line;

	if (!memory || memory[0] == '\0')
		return (NULL);
	x = 0;
	while (memory[x] != '\n' && memory[x])
		x++;
	line = malloc (sizeof(char) * (x + 1 + (memory[x] == '\n')));
	if (!line)
		return (NULL);
	x = 0;
	while (memory[x])
	{
		line[x] = memory[x];
		if (line[x] == '\n')
		{
			x++;
			break ;
		}
		x++;
	}
	line[x] = '\0';
	return (line);
}

char	*ft_new_memory(char *memory)
{
	size_t	x;
	size_t	y;
	char	*temp;

	x = 0;
	while (memory[x] != '\n' && memory[x])
		x++;
	if (memory[x] == '\0')
	{
		free (memory);
		return (NULL);
	}
	temp = malloc ((ft_strlen(memory) - x) * sizeof(char));
	if (!temp)
	{
		free (memory);
		return (NULL);
	}
	y = 0;
	x++;
	while (memory[x])
		temp[y++] = memory[x++];
	temp[y] = '\0';
	free (memory);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*memory[FD_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	memory[fd] = ft_read_memory(fd, memory[fd]);
	if (!memory[fd])
		return (NULL);
	line = ft_get_line(memory[fd]);
	memory[fd] = ft_new_memory(memory[fd]);
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	return (0);
} */