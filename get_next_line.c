/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:32:48 by tchareto          #+#    #+#             */
/*   Updated: 2024/01/22 22:42:38 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include "get_next_line.h"

char	*gnl(int fd)
{
	static char			buffer[BUFFER_SIZE +1];
	static ssize_t		buffer_size = 0;
	static ssize_t		buffer_index = 0;
	struct variables	v1;

	v1.line = NULL;
	v1.line_size = 0;
	while (1)
	{
		if (buffer_index >= buffer_size)
		{
			buffer_size = read(fd, buffer, BUFFER_SIZE);
			if (buffer_size <= 0 && v1.line_size > 0 && buffer_size != -1)
				return (v1.line);
			if (buffer_size <= 0)
				return (free(v1.line), NULL);
			buffer_index = 0;
		}
		v1.c = buffer[buffer_index++];
		v1.line = append_char_to_line(v1.line, v1.c, &v1.line_size);
		if (!v1.line || v1.c == '\n')
			break ;
	}
	return (v1.line);
}

char	*get_next_line(int fd)
{
	if (!is_fd_valid(fd))
		return (NULL);
	return (gnl(fd));
}

/*
int main()
{
	int fd = open("bible.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/