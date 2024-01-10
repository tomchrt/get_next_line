/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:23:25 by tchareto          #+#    #+#             */
/*   Updated: 2024/01/10 19:37:37 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include "fcntl.h"
#include "get_next_line.h"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif
char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*str;

	i = 0;
	while (src[i] != '\0')
		i++;
	//str = malloc(sizeof (char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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
	s3 = malloc(sizeof(char) * (i + j + 2));
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

char	*ft_strchr(const char *str, int c)
{
	unsigned char	a;

	a = (unsigned char)c;
	while (*str != '\0' && *str != a)
	{
		str++;
	}
	if (*str == a)
	{
		return ((char *)str);
	}
	else
	{
		return (NULL);
	}
}

char	*ft_select(char *buffer)
{
	if (!buffer)
		return (NULL);
	int		i;
	char	*dest;

	i = 0;
	while (buffer && buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	//dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (buffer && buffer[i] && buffer[i] != '\n')
	{
		dest[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

char *ft_select2(char *str, size_t k, ssize_t ret)
{
	int j;
	char *dest;

	if (!str)
		return (NULL);
	dest = malloc(sizeof(char) * (ret - k + 1));
	if (!dest)
		return (NULL);
	j = 0;
	while (str && str[k])
		dest[j++] = str[k++];
	dest[j] = '\0';
	//free(str);
	return (dest);
}


ssize_t ft_ret_value(int fd, char *buf)
{
	ssize_t	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret > 0)
		buf[ret] = 0;
	return (ret);
}

int	ft_check_return(ssize_t ret, char **str)
{
	if (ret == 0 && *str && (*str)[0] == 0)
	{
		free(*str);
		*str = NULL;
		return (0);
	}
	return (1);
}

char	*read_and_join_lines(char **str, int fd, ssize_t *ret)
{
	static char	buffer[BUFFER_SIZE];
	char	*temp;

	while (*ret > 0)
	{
		*ret = ft_ret_value(fd, buffer);
		if (*ret == -1)
			return (NULL);
		if (*ret == 0)
			break ;
		temp = ft_strjoin(*str, buffer);
		//free(*str);
		if (!temp)
			return (NULL);
		*str = ft_strdup(temp);
		free(temp);
		if (ft_strchr(*str, '\n'))
			break ;
	}
	return (*str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	str[BUFFER_SIZE];

	ssize_t		ret;


	line = NULL;
	ret = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	if (read_and_join_lines(&str, fd, &ret) == NULL)
		return (NULL);
	line = ft_select(str);
	str = ft_select2(str, ft_strlen(line), ret);
	if (ft_check_return(ret, &str) == 0 && (line == NULL || line[0] == '\0'))
		return (NULL);
	//free(str);
	return (line);
}

int main()
{
	int fd = open("2.txt", O_RDONLY);
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