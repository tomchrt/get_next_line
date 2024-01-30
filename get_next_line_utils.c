/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:51:22 by tchareto          #+#    #+#             */
/*   Updated: 2024/01/19 18:51:46 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include "get_next_line.h"

int	is_fd_valid(int fd)
{
	return (fd >= 0);
}

char	*append_char_to_line(char *line, char c, ssize_t *size)
{
	char		*new_line;
	ssize_t		i;

	i = 0;
	new_line = malloc((*size) + 2);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	while (i < (*size))
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i++] = c;
	new_line[i] = '\0';
	free(line);
	*size = i;
	return (new_line);
}
