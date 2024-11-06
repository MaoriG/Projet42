/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:13:32 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/06 17:14:27 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef libft_h
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>

int		ft_atoi(const char *str);
void	ft_bzero(void *ptr, unsigned int n);
void	*ft_calloc(size_t num, size_t size);
void	ft_isalnum(int c);
void	ft_isalpha(int c);
void	ft_isascii(int c);
void	ft_isdigit(int c);
void	ft_isascii(int c);
void	*ft_memchr(const void *ptr, int value, size_t num);
int		ft_memcmp(const void *ptr1, const void *ptr2, unsigned int num);
void	ft_memcpy(void *dest, void *src, unsigned int n);
void	ft_memmove(void *dest, const void *src, size_t n);
void	ft_memset(void *ptr, int value, unsigned int num);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	*ft_strnstr(const char *haystack, const char *needle, unsigned int len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);

int	ft_toupper(int c)

#endif
