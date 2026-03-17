/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:15:17 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/17 14:05:36 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	int		i;

	len1 = 0;
	len2 = 0;
	i = 0;
	if(s1 == NULL)
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

char *line_copier(char *stash, int n)
{
	int i;
	char	*line;
	
	i = 0;
	line = malloc(sizeof(char) * (n + 2));
	if (line == NULL)
		return (NULL);
	while (stash[i] != '\0')
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

#include <stdio.h>

int main(void)
{
	char *stash = "abcdef";
	char *line = line_copier(stash, 4);
	return 0;
}
