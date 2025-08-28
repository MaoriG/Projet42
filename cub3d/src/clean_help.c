/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:19:06 by mgobert           #+#    #+#             */
/*   Updated: 2025/08/28 21:02:03 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	drain_gnl_fd(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}

void	free_gnl_leak(void)
{
	int		fd;
	char	*line;

	fd = open("/dev/null", O_RDONLY);
	line = get_next_line(fd);
	if (line)
		free(line);
	close(fd);
}
