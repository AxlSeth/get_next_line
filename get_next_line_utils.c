/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:43:30 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/24 01:46:54 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	has_new_line(char *stash)
{
	int	i;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*append(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

char	*create_buffer(int fd)
{
	char	*buffer;
	int		end;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	end = read(fd, buffer, BUFFER_SIZE);
	if (end == 0)
	{
		free(buffer);
		return (NULL);
	}
	else if (end == -1)
		return (NULL);
	buffer[end] = '\0';
	return (buffer);
}

int	line_size(char *stash)
{
	int	position;

	position = 0;
	while (stash[position])
	{
		if (stash[position] == '\n')
			return (position + 1);
		position++;
	}
	if (has_new_line(stash))
		return (position + 1);
	else
		return (position);
}
