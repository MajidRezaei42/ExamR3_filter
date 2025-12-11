/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_cor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arezaei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:24:14 by arezaei           #+#    #+#             */
/*   Updated: 2025/12/11 16:24:16 by arezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_filter(char *buffer, const char *target)
{
	int	i;
	int	j;
	int	target_len;

	target_len = strlen(target);
	i = 0;
	while (buffer[i])
	{
		j = 0;
		while (target[j] && buffer[i + j] == target[j])
			j++;
		if (j == target_len)
		{
			while (j-- > 0)
				write(1, "*", 1);
			i += target_len;
		}
		else
		{
			write(1, &buffer[i], 1);
			i++;
		}
	}
}

int	read_all(char **result)
{
	char	temp[BUFFER_SIZE];
	char	*buffer;
	int		total;
	ssize_t	bytes;

	*result = NULL;
	total = 0;
	bytes = read(0, temp, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer = realloc(*result, total + bytes + 1);
		if (!buffer)
		{
			free(*result);
			perror("Error");
			return (1);
		}
		*result = buffer;
		memmove(*result + total, temp, bytes);
		total += bytes;
		(*result)[total] = '\0';
		bytes = read(0, temp, BUFFER_SIZE);
	}
	if (bytes < 0)
	{
		free(*result);
		perror("Error");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	*result;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	if (read_all(&result))
		return (1);
	if (result)
	{
		ft_filter(result, argv[1]);
		free(result);
	}
	return (0);
}
