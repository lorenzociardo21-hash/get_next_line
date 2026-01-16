/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciardo <lciardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:37:31 by lciardo           #+#    #+#             */
/*   Updated: 2026/01/16 19:48:26 by lciardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciardo <lciardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:18:13 by lciardo           #+#    #+#             */
/*   Updated: 2026/01/16 18:55:04 by lciardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*memory;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	memory = ft_read_memory(fd, memory);
	if (!memory)
		return (NULL);
	line = ft_get_line(memory);
	memory = ft_new_memory(memory);
	return (line);
}
