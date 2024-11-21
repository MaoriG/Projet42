/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:28:43 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/21 18:37:40 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*extract_line_bonus(char *stash);
char	*read_and_store_bonus(int fd, char *stash);
int		ft_strchr_bonus(char *s, int c);
char	*sjoin_bonus(const char *s1, const char *s2);
int		ftslen_bonus(const char *s);
char	*ft_stdup_bonus(const char *s);
char	*get_next_line(int fd);

#endif