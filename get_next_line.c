/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:23:25 by tchareto          #+#    #+#             */
/*   Updated: 2024/01/16 19:35:01 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	while (s1 && s1[i] != '\0')
		i++;
	while (s2 && s2[j] != '\0')
		j++;
	s3 = malloc(sizeof(char) * (i + j +1));
	if (!s3)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		s3[i++] = *s1++;
	while (s2 && *s2)
		s3[i++] = *s2++;
	s3[i] = '\0';
	return (s3);
}

char	*ft_strchr(const char *str1, int c)
{
	unsigned char	a;

	a = (unsigned char)c;
	while (*str1 != '\0' && *str1 != a)
	{
		str1++;
	}
	if (*str1 == a)
	{
		return ((char *)str1);
	}
	else
	{
		return (NULL);
	}
}

char	*ft_select(char *buffer1)
{
	int		i;
	char	*dest;

	i = 0;
	if (!buffer1)
		return (NULL);
	while (buffer1 && buffer1[i] && buffer1[i] != '\n')
		i++;
	if (buffer1[i] == '\n')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (buffer1 && buffer1[i] && buffer1[i] != '\n')
	{
		dest[i] = buffer1[i];
		i++;
	}
	if (buffer1[i] == '\n')
		dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

char	*ft_select2(char *str1, size_t k, ssize_t ret)
{
	int		j;
	char	*dest;

	if (!str1)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(str1) - k + 1));
	if (!dest)
		return (NULL);
	j = 0;
	while (str1[k] && ret != 0)
	{
		dest[j++] = str1[k++];
	}
	dest[j] = '\0';
	free(str1);
	return (dest);
}

char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*str1;

	i = 0;
	while (src[i] != '\0')
		i++;
	str1 = malloc(sizeof (char) * (i + 1));
	if (!str1)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		str1[i] = src[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}

ssize_t	ft_ret_value(int fd, char *buf)
{
	ssize_t	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret > 0)
		buf[ret] = 0;
	return (ret);
}

int	ft_check_return(ssize_t ret, char **str1)
{
	if (ret == 0 && *str1 && (*str1)[0] == '\0')
	{
		free(*str1);
		*str1 = NULL;
		return (0);
	}
	return (1);
}

char	*read_and_join_lines(char **str1, int fd, ssize_t *ret)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*temp;

	while (*ret > 0)
	{
		*ret = ft_ret_value(fd, buffer);
		if (*ret == -1 || (*ret == 0 && !str1))
			return (NULL);
		temp = ft_strjoin(*str1, buffer);
		if (!temp)
			return (NULL);
		free(*str1);
		*str1 = ft_strdup(temp);
		free(temp);
		if (ft_strchr(*str1, '\n'))
			break ;
	}
	return (*str1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str = NULL;
	ssize_t		ret;

	line = NULL;
	ret = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	if (read_and_join_lines(&str, fd, &ret) == NULL)
		return (NULL);
	line = ft_select(str);
	str = ft_select2(str, ft_strlen(line), ret);
	if (line == NULL)
			return (NULL);
	if (ft_check_return(ret, &str) == 0 && (line[0] == '\0'))
		return (NULL);
	return (line);
}

int main()
{
	int fd = open("test2.txt", O_RDONLY);
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
}