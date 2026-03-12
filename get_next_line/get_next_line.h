/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seramaro <seramaro@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:02:59 by seramaro          #+#    #+#             */
/*   Updated: 2026/03/12 08:39:38 by seramaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#  include <fcntl.h>
#  include <stddef.h>
#  include <stdlib.h>
#  include <unistd.h>

int	line_length(char *str);
char	*copier(char *dest, char *src, size_t l);
char	*line(int fd, int n);

# endif
