/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:31:44 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/20 14:35:22 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

void	print_error_exit(char *str, int exit_code)
{
	if (str == NULL)
		exit(exit_code);
	write(STDERR_FILENO, "Error:\n\t", 8);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	exit(exit_code);
}

void	print_error(char *str)
{
	if (str == NULL)
		return ;
	write(STDERR_FILENO, str, ft_strlen(str));
}

void	print_error_acces(char *filename)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, filename, ft_strlen(filename));
	write(STDERR_FILENO, ": could not access\n", 19);
}

void	print_error_found(char *filename)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, filename, ft_strlen(filename));
	write(STDERR_FILENO, ": command not found\n", 20);
}

void	print_error_op(char *op)
{
	write(STDERR_FILENO,
		"minishell: syntax error near unexpected token `", 47);
	write(STDERR_FILENO, op, ft_strlen(op));
	write(STDERR_FILENO, "'\n", 2);
}
