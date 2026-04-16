/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:32:35 by seramaro          #+#    #+#             */
/*   Updated: 2026/04/16 21:31:32 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static char	*read_until_nl(int fd, char *stash)
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

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	n;

	if (!stash || *stash == '\0')
		return (NULL);
	n = line_size(stash);
	line = malloc(n + 1);
	if (!line)
		return (NULL);
	ft_memmove(line, stash, n);
	line[n] = '\0';
	return (line);
}

static int	update_stash(char **stash)
{
	char	*new_stash;
	size_t	n;
	size_t	len;

	n = line_size(*stash);
	len = ft_strlen(*stash) - n;
	if (len == 0)
		return (free(*stash), *stash = NULL, 1);
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (free(*stash), *stash = NULL, 0);
	ft_memmove(new_stash, *stash + n, len);
	new_stash[len] = '\0';
	free(*stash);
	*stash = new_stash;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = create_buffer(fd);
	stash[fd] = read_until_nl(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	if (*stash[fd] == '\0')
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line = extract_line(stash[fd]);
	if (!line || !update_stash(&stash[fd]))
		return (free(line), NULL);
	return (line);
}
