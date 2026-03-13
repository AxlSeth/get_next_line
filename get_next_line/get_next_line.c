/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:15:17 by seramaro          #+#    #+#             */
/*   Updated: 2028/03/13 09:23:44 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include<fcntl.h>
#  include <stddef.h>
#  include <stdlib.h>
#  include <unistd.h>

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
	return (length + 2);
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

char	*line(int fd, int n)
{
	static char		*stash;
	int			length;
	char			*line;
	int			i;

	//take input from the file descriptor and put it into stash
	read(fd, stash, n);
	
	//look for the length of thestring in stashfrom the beginning to the \n
	length = line_length(stash);

	//allocate memory for the line depending on the length
	line = malloc(sizeof(char) * (length + 2));	

	//copy every character up to \n from stash to line and the add \1 in the end
	c_memcpy(line, stash, length);
	stash[length + 2] = '\0'; 

	return (line);
}
