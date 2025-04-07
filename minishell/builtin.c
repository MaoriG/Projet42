/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:30:31 by mgobert           #+#    #+#             */
/*   Updated: 2025/03/24 18:29:16 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int shell_exit(char **args)
{
    (void)args;
    exit(EXIT_SUCCESS);
}

int shell_env(char **args)
{
    extern char **environ;
    (void)args;
    if (!environ)
        return (1);
    for (int i = 0; environ[i]; i++)
        p("%s\n", environ[i]);
    return (0);
}