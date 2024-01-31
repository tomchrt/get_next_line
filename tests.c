/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchareto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:41:22 by pantoine          #+#    #+#             */
/*   Updated: 2024/01/17 15:18:13 by tchareto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	char	*res;
	int	fd1;
	int fd2;
	int fd3;
	int fd4;
	int fd5;
	int fd6;
	int fd7;
	int fd8;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	fd4 = open("test4.txt", O_RDONLY);
	fd5 = open("test5.txt", O_RDONLY);
	fd6 = open("test6.txt", O_RDONLY);
	fd7 = open("test7.txt", O_RDONLY);
	fd8 = open("test8.txt", O_RDONLY);

	printf("\nTest n. 1\n");
	res = get_next_line(fd1);
	printf("%s", res);
	free(res);
	printf("\nTest n. 2\n");
	res = get_next_line(fd2);
	printf("%s", res);
	free(res);
	printf("\nTest n. 3\n");
	res = get_next_line(fd3);
	printf("%s", res);
	free(res);
	res = get_next_line(fd3);
	printf("%s", res);
	free(res);
	printf("\nTest n. 4\n");
	res = get_next_line(fd4);
	printf("%s", res);
	free(res);
	res = get_next_line(fd5);
	printf("%s", res);
	free(res);
	res = get_next_line(fd6);
	printf("%s", res);
	free(res);
	res = get_next_line(fd5);
	printf("%s", res);
	free(res);
	printf("\nTest n. 4\n");
	res = get_next_line(fd7);
	printf("%s", res);
	free(res);
	res = get_next_line(fd7);
	printf("%s", res);
	free(res);
	printf("\nTest n. 5\n");
	while (1)
	{
		res = get_next_line(fd8);
		printf("%s", res);
		if (!res)
			break ;
		free(res);
	}
	return (0);
}