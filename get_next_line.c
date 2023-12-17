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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h> 
#include <sys/types.h> 
#define BUFFER_SIZE 1

int	ft_ret_value(int ret, int fd, char *buf)
{
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret > 0)
        buf[ret] = 0;
	return (ret);
}

int	ft_check_return(int ret, char **str)
{
	if (ret == 0 && (*str)[0] == 0)
	{
		free(*str);
		*str = NULL;
		return (0);
	}
	return (1);
}

int	ft_ckeck_error(int fd, char **line)
{
	if ((fd < 0 || fd > 1023) || !line || BUFFER_SIZE <= 0)
		return (-1);
	return (1);
}


size_t ft_strlen(const char *s)
{
    size_t i;
    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    size_t i;
    size_t j;
    i = 0;
    j = 0;
    char *s3;

    while (s1 && s1[i] != '\0')
        i++;
    while (s2 && s2[j] != '\0')
        j++;
    if (!(s3 = malloc(sizeof(char) * (i + j + 1))))
        return NULL;
    i = 0;
    while (s1 && *s1)
        s3[i++] = *s1++;
    while (s2 && *s2)
        s3[i++] = *s2++;
    s3[i] = '\0';
    return s3;
}

char *ft_strchr(const char *str, int c)
{
    unsigned char a;
    a = (unsigned char)c;
    while (*str != '\0' && *str != a)
    {
        str++;
    }
    if (*str == a)
    {
        return (char *)str;
    }
    else
    {
        return NULL;
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
        return NULL;
    i = 0;
    while (buffer && buffer[i] && buffer[i] != '\n')
    {
        dest[i] = buffer[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *ft_select2(char *buffer)
{
    int i;
    int j;
    char *dest;

    i = 0;
    j = 0;

    while (buffer && buffer[i] && buffer[i] != '\n')
        i++;    
    dest = malloc(sizeof(*dest) * (ft_strlen(buffer) - i + 1));
    j = 0;
    while (buffer && buffer[i])
        dest[j++] = buffer[i++];
    dest[j] = '\0';
    return dest;
}

char *get_next_line(int fd)
{
    char *line;
    static char *str;
    ssize_t;
    char buffer[BUFFER_SIZE + 1];
    char *temp;

    temp = NULL;
    str = NULL;
    line = NULL;
    ret = BUFFER_SIZE;
    if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
        return NULL;
    while (ret > 0)
    {
        ret = ft_ret_value(ret, fd, buffer);
        if (ret == -1)
        {
            return NULL;
        }
        temp = ft_strjoin(str, buffer);
        free(str);
        if (!temp)
        {
            return NULL;
        }
        str = temp;
        if (ft_strchr(str, '\n'))
            break;
    }
    line = ft_select(str);
    temp = str;
    str = ft_select2(temp);
    free(temp);
    if (ft_check_return(ret, &str) == 0 && (line == NULL || line[0] == '\0'))
    {
        return NULL;
    }
    return line;
}


#include <stdio.h>
int main() {
    int fd = open("exemple.txt", O_RDONLY);
    if (fd == -1) 
       return 1;

    char *line;
    
    // Obtenez les lignes successives en appelant plusieurs fois get_next_line
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}