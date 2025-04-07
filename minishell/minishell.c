/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:16:47 by mgobert           #+#    #+#             */
/*   Updated: 2025/04/07 21:33:40 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int status = 0;

void shell_lauch(char **args) 
{
    char **test;
    
    if (!args || !args[0]) {
        fprintf(stderr, "Erreur : commande vide\n");
        return;
    }
    pid_t pid = Fork();
    if (pid == 0) 
    {
        p("%s", args[0]);
        execvp(args[0], args);  // Utilise PATH pour trouver l'exécutable
    } else {  // Parent
        Wait(&status);
    }
}

/* t_builtin g_builtin[] = 
{
    //{.builtin_name="echo", .foo=shell_echo};
    {.builtin_name="env", .foo=shell_env},
    {.builtin_name="env", .foo=shell_exit},
    {.builtin_name= NULL, .foo = NULL}
} */

/* void shell_exec (char **args)
{
    int i;
    const char *curr;

    i = 0;
    while ((curr =g_builtin[i].builtin_name))
    {
        if (!strcmp(curr, args[0]))
        {
            status = g_builtin[i].foo(args);
            return;
        }
        i++;
    }
    shell_lauch(args);
} */
void init_bool(char *str, t_cmd *tab)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            tab->is_pipe = true;
        else if (str[i] == '>' && str[i + 1] != '>')
            tab->is_chevron_r = true;
        else if (str[i] == '>' && str[i + 1] == '>')
            tab->is_append_r = true;
        else if (str[i] == '<' && str[i + 1] != '<')
            tab->is_chevron_l = true;
        else if (str[i] == '<' && str[i + 1] == '<')
            tab->is_append_l = true;
        i++;
    }
}
void init(char *line, t_cmd *tab)
{
    tab->is_append_l = false;
    tab->is_append_r = false;
    tab->is_chevron_l = false;
    tab->is_chevron_r = false;
    tab->is_pipe = false;
    init_bool(line, tab);
    tab->line_r = ft_split(line, '|');
    tab->args_r = ft_split(line, ' ');
}

char *shell_read_line(void)
{
    char *buf;
    size_t bufsize;
    char cwd[BUFSIZ];

    Getcwd(cwd, sizeof(cwd));
    p(C" %s"RST"$>", cwd);
    buf = NULL; // pour getline on connait pas encore la taille du buffer
    if (getline(&buf, &bufsize, stdin) == -1)
    {
        free(buf);
        buf = NULL; // important de remettre le null parce qu'a l'echec ca change le buf
        if (feof(stdin))
            p(RED"[EOF]"RST);
        else
            p(RED"Getline failed"RST);
    }
    return (buf);
}
int main (int ac, char **av)
{
    (void)ac;
    char *line;
    int i = 0;
    t_cmd *arg;

    arg = safe_malloc(sizeof(t_cmd));
    printbanner();
    while ((line = shell_read_line()))
    {
        printf("%s", line);
        init(line, arg);
        /* for (int i = 0; result->args[i]; ++i)
        p("%s\n", result->args[i]); */
       /*  execvp(result->args[0], result->args);
        shell_exec(result->args);
        free(line); */
    }

    
}