/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:15:17 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/18 16:24:15 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static char	*cpy(char *src, char *dst, int i, int j)
{
	while (src[i] != '\0')
	{
		dst[i + j] = src[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	if (s1 == NULL)
		s1 = "";
	while (s1[len1] != '\0')
		len1++;
	while (s2[len2] != '\0')
		len2++;
	new = malloc(len1 + len2 + 1);
	if (new == NULL)
		return (NULL);
	cpy(s1, new, 0, 0);
	cpy(s2, new, 0, len1);
	new[len1 + len2] = '\0';
	return (new);
}

char	*line_copier(char *stash, int n)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(sizeof(char) * (n + 2));
	if (line == NULL)
		return (NULL);
	while (stash[i] != '\0' && (i < n))
	{
		if (stash[i] != '\n')
		{
			line[i] = stash[i];
		}
		else if (stash[i] == '\n')
		{
			line[n + 1] = '\n';
			line[n + 2] = '\0';
		}
		i++;
	}
	return (line);
}

char	*fill_buffer(int fd)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	read(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE + 1] = '\0';
	return (buffer);
}

int	new_line_track(char *str)
{
	int	last_char;

	last_char = 0;
	while(str[last_char] && str[last_char] != '\n')
		last_char++;
	return (last_char);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*stash;
	int		read_lines;

	buffer = malloc(BUFFER_SIZE + 1);
	read_lines = read(fd, buffer, BUFFER_SIZE);
	buffer[read_lines] = '\0';

	if(!stash)
		stash = buffer;
	else
	 	stash = ft_strjoin(stash, buffer);

	line = line_copier(stash, new_line_track(stash));

	return (line);
}

int main(void)
{
	int	fd = open("nigga.txt", O_RDONLY);

	char *ret = get_next_line(fd);
	printf("%s", ret);	
	return (0);
}
