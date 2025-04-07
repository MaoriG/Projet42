/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:39:16 by mgobert           #+#    #+#             */
/*   Updated: 2025/04/07 21:13:05 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

// Couleur
#define Y "\033[1;33m" // Yellow
#define G "\033[1;32m" // Green
#define C "\033[1;36m" // Cyan
#define RED "\033[1;31m"
#define RST "\033[0m" // Reset

#define p(...) printf(__VA_ARGS__)
#define DEL "\n\t \v\f\r"
#define SHELL_J 0

// Command structure
typedef struct s_cmd
{
    char **line_r;
    char **args_r;
    bool is_chevron_r;
    bool is_chevron_l;
    bool is_append_r;
    bool is_append_l;
    bool is_pipe;
} t_cmd;

// Function prototypes
void printbanner(void);
void *safe_malloc(size_t size);
void init(char *line, t_cmd *tab);
char	**ft_split(char const *s, char c);
pid_t Fork(void);
void Execvp(const char *file, char *const argv[]);
pid_t Wait(int *status);
int shell_exit(char **args);
int shell_env(char **args);
void Getcwd(char *buf, size_t size);

typedef struct s_builtin
{
    const char *builtin_name;
    int (*foo)(char **);
}       t_builtin;

#endif
