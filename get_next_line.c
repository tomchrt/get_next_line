/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:23:25 by tchareto          #+#    #+#             */
/*   Updated: 2023/12/12 17:16:20 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "get_next_line.h"
#define BUFFER_SIZE 1

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	s3 = malloc (sizeof(char) * (i + j) + 1);
	if (!s3)
		return (NULL);
	i = -1;
	while (++i, s1[i] != '\0')
		s3[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned char a;

	a = (unsigned char) c;
	while (*str != '\0' && *str != a)
	{
		str++;
	}
	if (*str == a)
	{
		return ((char *) str);
	} else
	{
		return (0);
	}
}
char *ft_select(char *buffer)
{
	int i;
	char *dest;

	i = 0;
	while (buffer && buffer[i] && buffer[i] != '\n')
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return(NULL);
	i = 0;
	if (ft_strchr(buffer, '\n')!=0)
		while (buffer && buffer[i] && buffer[i] != '\n')
		{
			dest[i] = buffer[i];
			i++;
		}
		dest[i] = '\0';
	return (dest);

}

char *ft_select2(char *buffer)
{
	int i;
	int j;
	char *dest;

	i = 0;
	while (buffer && buffer[i] && buffer[i] != '\n')
		i++;
	dest = malloc(sizeof (*dest) * ft_strlen(buffer) - i + 1);
	j = 0;
	while (buffer && buffer [i])
		dest[j++] = buffer[i++];
	return (dest);
}

char	*get_next_line(int fd)

{
	char			*line;
	static char		*str;
	ssize_t			ret;
	char			*buffer;
	char			*temp;

	ret = 1;

	if (fd < 0 || !str|| BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return(NULL);
	while ((ret = read(fd, buffer, BUFFER_SIZE))> 0)
	{
		buffer[ret] = 0;
		temp = str;
		str = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(str, '\n'))
			break;
	}
	if (ret == -1)
		return (NULL);
	line = ft_select (str);
	temp =str;
	str = ft_select2(temp);
	free (temp);
	if (ret == 0 && (str[0] == 0))
	{
		free (str);
		*str = (0);
	}
	return (line);
	}