/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:15:17 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/12 15:07:26 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line_length(char *str)
{
	int	length;

	length = 0;
	while (str[length] != '\n')
	{
		if (str[length] == '\0')
		{
			return (length);
		}
		length++;
	}
	return (length + 1);
}

char	*c_memcpy(char *dest, char *src, size_t l)
{
	unsigned char	*char_dest;
	unsigned char	*char_src;

	char_dest = (unsigned char *)dest;
	char_src = (unsigned char *)src;
	if (char_dest < char_src)
	{
		while (l--)
			*char_dest++ = *char_src++;
	}
	else if (char_dest > char_src)
	{
		while (l--)
			char_dest[l] = char_src[l];
	}
	return (dest);
}

char	*line_copier(int fd, int n)
{
	static char		*stash;
	char		*line;
	int	i;

	i = 0;
	stash = malloc(sizeof(char) * n);
	read(fd, stash, n);

	while(stash[i] != '\0')
	{
		if(stash[i] == '\n')

	}
	return (line);
}
