/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:32:35 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/24 01:10:57 by seramaro         ###   ########.fr       */
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

int	main(void)
{
	int		fd;
	char	*line1;
	char	*line2;
	char	*line3;

	fd = open("nigga.txt", O_RDONLY);
	line1 = get_next_line(fd);
	line2 = get_next_line(fd);
	line3 = get_next_line(fd);
	printf("%s%s%s", line1, line2, line3);
	return (0);
}
