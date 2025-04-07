/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:14:34 by mgobert           #+#    #+#             */
/*   Updated: 2025/03/24 18:20:29 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printbanner(void)
{
    p(G"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"
    "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n"
    "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n"
    "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n"
    "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"RST);
}

void *safe_malloc(size_t size)
{
    void *ptr;
    if (size == 0)
        return (NULL);
    ptr = malloc(size);
    if (!ptr)
    {
        perror(RED"Malloc failed"RST);
        exit(EXIT_FAILURE);
    }
    return (ptr);
}
pid_t Fork(void)
{
    pid_t pid;
    
    pid = fork();
    if (pid < 0)
    {
        perror(RED"Fork failed"RST);
        exit(EXIT_FAILURE);
    }
    return (pid);
}
void Execvp(const char *file, char *const argv[])
{
    if (!file || !argv)
    {
        fprintf(stderr, RED"Execvp : invalid arguments\n"RST);
        exit(EXIT_FAILURE);
    }
    if (execvp(file, argv) == -1)
    {
        perror(RED"SHELL_J failed"RST);
        exit(EXIT_FAILURE);
    }
}

pid_t Wait(int *status)
{
    pid_t result;
    
    if (!status)
    {
        fprintf(stderr, RED"Wait : status argument required\n"RST);
        return (-1);
    }
    result = wait(status);
    if (result == -1)
        perror(RED"Wait failed"RST);
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
    return (result);
}
void Getcwd(char *buf, size_t size)
{
    if (NULL == getcwd(buf, size))
        perror(RED"getcwd FAILED"RST);
}
