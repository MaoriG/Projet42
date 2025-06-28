/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:19:12 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/15 17:28:00 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define I64_MAX "9223372036854775807"
#define I64_MAX_LEN 19

#define I64_MIN "9223372036854775808"
#define I64_MIN_LEN 19

static int64_t	is_less_max_i64(char *text)
{
	int	i;

	i = 0;
	while ('\0' != text[i])
		i++;
	if (i < I64_MAX_LEN)
		return (1);
	if (i > I64_MAX_LEN)
		return (0);
	i = 0;
	while (i < I64_MAX_LEN)
	{
		if (text[i] > I64_MAX[i])
			return (0);
		i++;
	}
	return (1);
}

static int	is_greater_min_i64(char *text)
{
	int	i;

	i = 0;
	while ('\0' != text[i])
		i++;
	if (i < I64_MIN_LEN)
		return (1);
	if (i > I64_MIN_LEN)
		return (0);
	i = 0;
	while (i < I64_MIN_LEN)
	{
		if (text[i] > I64_MIN[i])
			return (0);
		i++;
	}
	return (1);
}

static int	does_fit_in_int(char *text)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if ('-' == text[i])
	{
		i++;
		sign = -1;
	}
	else if ('+' == text[i])
		i++;
	while ('0' == text[i] && '\0' != text[i + 1])
		i++;
	if (sign == -1)
		return (is_greater_min_i64(&text[i]));
	return (is_less_max_i64(&text[i]));
}

static int	is_int(char *text)
{
	int	i;

	i = 0;
	if (('-' == text[i] || '+' == text[i]) && '\0' != text[i + 1])
		i++;
	while ('0' <= text[i] && text[i] <= '9')
		i++;
	if ('\0' != text[i])
		return (0);
	return (does_fit_in_int(text));
}

int	ft_atoi(char *text, int64_t *res)
{
	int	i;
	int	sign;

	if (!is_int(text))
		return (1);
	*res = 0;
	sign = 1;
	i = 0;
	if ('+' == text[i])
		i++;
	else if ('-' == text[i])
	{
		i++;
		sign = -1;
	}
	while ('\0' != text[i])
	{
		if (-1 == sign)
			*res = (*res) * 10 - (text[i] - '0');
		else
			*res = (*res) * 10 + (text[i] - '0');
		i++;
	}
	return (0);
}
