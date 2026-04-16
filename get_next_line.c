/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:32:35 by seramaro          #+#    #+#             */
/*   Updated: 2026/04/16 13:24:58 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t l)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d < s)
		while (l--)
			*d++ = *s++;
	else
		while (l--)
			d[l] = s[l];
	return (dest);
}

static char	*read_line(int fd, char *stash)
{
	char	*buf;
	char	*tmp;

	while (stash && !has_new_line(stash))
	{
		buf = create_buffer(fd);
		if (!buf)
			break ;
		tmp = stash;
		stash = append(tmp, buf);
		free(tmp);
		free(buf);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*extract_line_and_update_stash(char **stash)
{
	char	*line;
	char	*new_stash;
	int		n;
	size_t	len;

	if (!stash || !*stash || **stash == '\0')
		return (free(*stash), *stash = NULL, NULL);
	n = line_size(*stash);
	line = malloc(n + 1);
	if (!line)
		return (NULL);
	ft_memmove(line, *stash, n);
	line[n] = '\0';
	len = ft_strlen(*stash) - n;
	if (!len)
		return (free(*stash), *stash = NULL, line);
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (free(*stash), *stash = NULL, free(line), NULL);
	ft_memmove(new_stash, *stash + n, len);
	new_stash[len] = '\0';
	free(*stash);
	*stash = new_stash;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = create_buffer(fd);
	stash = read_line(fd, stash);
	if (!stash)
		return (NULL);
	return (extract_line_and_update_stash(&stash));
}
