/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:32:35 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/24 01:47:40 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t l)
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

char	*create_line(char *stash)
{
	char	*line;

	line = malloc(sizeof(char) * (line_size(stash) + 1));
	line = (char *)ft_memmove(line, stash, (line_size(stash)));
	line[line_size(stash)] = '\0';
	return (line);
}

char	*store_remainder(char *stash)
{
	int		len;
	char	*remainder;

	len = ft_strlen(stash) - line_size(stash);
	remainder = malloc(sizeof(char) * (len + 1));
	remainder = ft_memmove(remainder, (stash + line_size(stash)), len);
	remainder[len] = '\0';
	return (remainder);
}

void	update_line(char **stash, char **remainder, char **line)
{
	if (has_new_line(*stash))
	{
		*line = create_line(*stash);
		*remainder = store_remainder(*stash);
		free(*stash);
		*stash = *remainder;
	}
	else if (*stash != NULL)
	{
		*line = create_line(*stash);
		free(*stash);
		*stash = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*remainder;
	char		*old_stash;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash == NULL)
		stash = create_buffer(fd);
	while (!has_new_line(stash))
	{
		old_stash = stash;
		buf = create_buffer(fd);
		if (!buf)
			break ;
		stash = append(old_stash, buf);
		free(old_stash);
		free(buf);
	}
	update_line(&stash, &remainder, &line);
	return (line);
}
