/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:33:29 by axlleres          #+#    #+#             */
/*   Updated: 2025/05/20 20:05:49 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>

extern int	g_last_signal;

typedef struct s_msh_cmd
{
	char	*path;
	char	**argv;
	int		argc;
	char	*name;
	uint8_t	is_builtin;
	char	*redir_out; // >
	char	*redir_in; // <
	char	*here_doc; // <<
	char	*append_out; // >>
	int		type_out;
	int		type_in;
}	t_msh_cmd;

typedef struct s_msh_cmd_pipes
{
	t_msh_cmd	*cmd;
	int			len;
}	t_msh_cmd_pipes;

typedef struct s_msh_env_var_t
{
	char	*name;
	char	*value; // if NULL no =
}	t_msh_env_var_t;

typedef struct s_msh_ctx
{
	t_msh_env_var_t	*env;
	int				env_len;
	int				last_status;
	int				heredoc_canceled;
}	t_msh_ctx;

typedef struct s_msh_process
{
	int			pipes[2];
	int			heredoc_pipes[2];
	t_msh_cmd	*cmd;
	t_msh_ctx	*ctx;
}	t_msh_process;

typedef struct s_pipeline_data
{
	char			**segments;
	int				*i;
	int				*k;
	int				*start;
	char			*quote;
}					t_pipeline_data;

# define Y "\033[1;33m"
# define G "\033[1;32m"
# define C "\033[1;36m"
# define RED "\033[1;31m"
# define RST "\033[0m"

//-----------------Strings------------------//
int		ft_strlen(const char *str);
int		ftstrcmp(const char *s1, const char *s2);
int		msh_array_len(char **array);
char	*ft_strdup(const char *str);
void	ft_strcpy(char *dest, char *src);
char	*sub_str(char *str, int start, int end);
void	ft_strcat(char *dest, const char *src);
void	ft_memcpy(void *dest, const void *src, int len);
int		ft_strchr(char *str, int c);
int		ft_is_space(char c);
int		ft_strstart(char *big, char *little);
void	ft_strcat_start(char *str, char *start);
char	*ft_itoa(int n);
int		ft_atoi(char *text, int64_t *res);
char	**ft_split(char const *s, char c);
char	*ft_substr(const char *s, int start, int len);
int		ft_isspace(char c);
int		only_spaces(const char *line);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcount(const char *str, char c);

//-----------------Path------------------//
char	*join_path(char *dir, char *cmd);

//-----------------Env------------------//
void	msh_unset_env(t_msh_ctx *ctx, char *name);
char	*msh_get_env(t_msh_ctx *ctx, char *name, int *exists);
char	*get_env_key(char *env_var);
char	*get_env_val(char *env_var);
void	msh_set_env(t_msh_ctx *ctx, char *name, char *value);
char	**msh_build_env(t_msh_ctx *ctx);

//-----------------Exec------------------//
void	exec_builtin(t_msh_ctx *ctx, t_msh_cmd *cmd);
int		msh_launch_file(t_msh_ctx *ctx, t_msh_cmd *cmd);
int		is_executing(int set_val, int val);
void	msh_exec_cmd_single(t_msh_ctx *ctx, t_msh_cmd *cmd);
void	msh_exec_cmd_pipes(t_msh_ctx *ctx, t_msh_cmd *cmd, int cmd_len);
void	msh_exec(t_msh_ctx *ctx, t_msh_cmd *cmds, int cmds_len);
char	*msh_find_cmd(char *name, uint8_t *is_builtin, t_msh_ctx *ctx);
int		msh_redir_in(t_msh_cmd *cmd);
int		msh_redir_out(t_msh_cmd *cmd);
int		msh_redir_append(t_msh_cmd *cmd);
int		msh_is_executable(char *path);
int		msh_do_redir_pipe(t_msh_process *processes, int cmd_len, int i);
void	init_processes(t_msh_process *processes,
			t_msh_cmd *cmd, int cmd_len, t_msh_ctx *ctx);
void	msh_close_heredocs(t_msh_process *processes, int cmd_len);
void	close_pipes(t_msh_process *processes, int cmd_len);
void	replace_var_loop(char *input, char *res, t_msh_ctx *ctx);

//-----------------Builtins------------------//

int		builtin_env(t_msh_ctx *ctx);
int		builtin_export(int argc, char **argv, t_msh_ctx *ctx);
int		builtin_unset(int argc, char **argv, t_msh_ctx *ctx);
int		msh_blt_cd(int argc, char **argv, t_msh_ctx *ctx);
int		msh_blt_echo(int argc, char **argv);
int		msh_blt_exit(t_msh_cmd *cmd, t_msh_ctx *ctx, int old_fd);
int		msh_blt_pwd(int argc, char **argv, t_msh_ctx *ctx);
void	msh_blt_exit2(t_msh_process *processes, int cmd_len,
			t_msh_ctx *ctx, int i);

//-----------------Init/Free------------------//
void	msh_init(char **env, t_msh_ctx *ctx);
void	msh_init_ctx(t_msh_ctx *ctx);
void	msh_free_ctx(t_msh_ctx *ctx);
void	msh_free_cmds(t_msh_cmd *cmds, int cmds_len);
void	free_segments(char **segments);
void	free_tokens(char **tokens);
void	free_split(char **array);
void	free_tab(char **tab);
void	*safe_malloc(size_t size);

//-----------------Error------------------//
void	print_error_found(char *filename);
void	print_error_acces(char *filename);
void	print_error_exit(char *str, int exit_code);
void	print_error(char *str);
void	print_error_op(char *op);

//-----------------Parsing------------------//
void	set_redir_1(char **redir, const char *value, t_msh_cmd *cmd, int is_in);
int		set_redir_2(char *value, t_msh_cmd *cmd, int is_in, t_msh_ctx *ctx);
int		set_redir(t_msh_cmd *cmd, t_msh_ctx *ctx, char **tokens);
int		init_command(char *line, t_msh_cmd *cmd, t_msh_ctx *ctx);
void	init_tab(t_msh_cmd *cmd);
void	update_quote(char c, char *quote);
int		skip_spaces(const char *line, int i);
char	**split_pipeline(const char *line);
int		parse_pipeline(char *line, t_msh_cmd **cmds_out, t_msh_ctx *ctx);
int		is_whitespace(const char *line);
int		count_segments(const char *line);
char	**get_tokens(char *line, t_msh_ctx *ctx);
int		tab_len(char **tokens);
int		parse_clean_help(t_msh_cmd *cmds, char **segments, int i);
int		parse_error_pipe(char **segments, t_msh_ctx *ctx);
int		token_count(char *line);
void	append_token(char **res, int *res_len, char *line, int *i);
void	parse_env(char **env, t_msh_ctx *ctx);
char	*get_token_redir(char *line, int *i);
int		is_op(char *tok);

//-----------------Input------------------//
char	*msh_get_input(t_msh_ctx *ctx);
char	*replace_var(char *input, t_msh_ctx *ctx);
int		replace_append_var(char **input, char *res,
			t_msh_ctx *ctx, int in_dquote);
int		get_input_size(char *input, t_msh_ctx *ctx);
int		is_var_sep(char c);
char	*get_var_name(char *input);
int		get_var_val_len(char *input, t_msh_ctx *ctx);
char	*msh_get_prompt(t_msh_ctx *ctx);
int		msh_get_heredoc(t_msh_cmd *cmd, t_msh_ctx *ctx);
void	replace_var_heredoc(char **input, char *res, int *k);
int		ft_check_quote(char *input);
void	print_banner(void);

//-----------------Signals------------------//
void	msh_sig_handler(int signum);

//-----------------Memory------------------//
void	ft_memset(void *ptr, int c, int len);
void	*ft_calloc(size_t size, size_t n);

#endif
