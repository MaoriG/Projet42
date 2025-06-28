/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlleres <axlleres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:21:59 by mgobert           #+#    #+#             */
/*   Updated: 2025/05/20 03:37:42 by axlleres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_pipe_outside_quotes(const char *line, int i, char quote)
{
	return (line[i] == '|' && quote == 0);
}

static int	save_segment(const char *line, char **segments, int start,
		int end)
{
	*segments = ft_substr(line, start, end - start);
	return (1);
}

static void	process_pipeline_segment(const char *line, t_pipeline_data *data)
{
	update_quote(line[*data->i], data->quote);
	if (is_pipe_outside_quotes(line, *data->i, *data->quote))
	{
		*(data->k) += save_segment(line,
				&data->segments[*(data->k)], *data->start, *data->i);
		(*data->i)++;
		*data->i = skip_spaces(line, *data->i);
		*data->start = *data->i;
	}
	else
		(*data->i)++;
}

char	**split_pipeline(const char *line)
{
	t_pipeline_data	data;
	char			**segments;
	int				i_k_start[3];
	char			quote;

	quote = 0;
	i_k_start[0] = 0;
	i_k_start[1] = 0;
	i_k_start[2] = 0;
	segments = safe_malloc(sizeof(char *) * (count_segments(line) + 1));
	data.segments = segments;
	data.i = &i_k_start[0];
	data.k = &i_k_start[1];
	data.start = &i_k_start[2];
	data.quote = &quote;
	while (line[*data.i])
		process_pipeline_segment(line, &data);
	if (*data.start < *data.i)
		*(data.k) += save_segment(line,
				&data.segments[*(data.k)], *data.start, *data.i);
	data.segments[*data.k] = NULL;
	return (data.segments);
}

int	parse_pipeline(char *line, t_msh_cmd **cmds_out, t_msh_ctx *ctx)
{
	char		**segments;
	int			count;
	int			i;
	t_msh_cmd	*cmds;

	if (line == NULL || *line == '\0' || is_whitespace(line))
		return (0);
	segments = split_pipeline(line);
	count = 0;
	i = 0;
	while (segments[count])
		count++;
	if (count != count_segments(line))
		return (parse_error_pipe(segments, ctx));
	cmds = safe_malloc(sizeof(t_msh_cmd) * count);
	ft_memset(cmds, 0, sizeof(t_msh_cmd) * count);
	while (i < count)
	{
		if (init_command(segments[i], &cmds[i], ctx) || cmds[i].argv == NULL)
			return (parse_clean_help(cmds, segments,
					i + ctx->heredoc_canceled));
		i++;
	}
	*cmds_out = cmds;
	return (free_segments(segments), count);
}
