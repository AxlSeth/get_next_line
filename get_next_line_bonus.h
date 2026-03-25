/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:12:31 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/24 01:58:01 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 07
# endif

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_strlen(char *str);
int		has_new_line(char *stash);
char	*append(char *s1, char *s2);
char	*create_buffer(int fd);
int		line_size(char *stash);
void	*ft_memmove(void *dest, const void *src, size_t l);
char	*create_line(char *stash);
char	*store_remainder(char *stash);
void	update_line(char **stash, char **remainder, char **line);
char	*get_next_line(int fd);

#endif
