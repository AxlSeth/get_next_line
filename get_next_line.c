/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:15:17 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/17 14:05:47 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd, int buffer_size)
{
	char		*line;
	char		*buffer;
	static char	*stash;
	int			i;

	i = 0;
	buffer = malloc(sizeof(char) * buffer_size);
	read(fd, buffer, buffer_size);
	
	while(stash[i])
	{
		if (stash[i] != '\n')
			stash = ft_strjoin(stash, buffer);
		else if (stash[i] == '\n')
		{
			line = malloc(sizeof(char) * i);
		}
		i++;
	}
	return (line);
}
