/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:09:05 by tchareto          #+#    #+#             */
/*   Updated: 2024/01/19 18:46:12 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct variables
{
	char		*line;
	ssize_t		line_size;
	char		c;
}	t_variables;

char	*append_char_to_line(char *line, char c, ssize_t *size);
int		is_fd_valid(int fd);
char	*get_next_line(int fd);
char	*gnl(int fd);

#endif