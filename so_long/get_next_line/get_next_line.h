/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:32:57 by mgobert           #+#    #+#             */
/*   Updated: 2025/01/13 20:33:40 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*extract_line(char *stash);
char	*read_and_store(int fd, char *stash);
int		ft_strchrn(char *s, int c);
char	*sjoin(const char *s1, const char *s2);
int		ftslen(const char *s);
char	*ft_stdup(const char *s);
char	*get_next_line(int fd);

#endif