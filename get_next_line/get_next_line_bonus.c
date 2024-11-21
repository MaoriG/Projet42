/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgobert <mgobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:28:26 by mgobert           #+#    #+#             */
/*   Updated: 2024/11/21 18:37:50 by mgobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_store_bonus(int fd, char *stash)
{
	char	*buffer;
	int		rd_bytes;
	char	*temp;

	rd_bytes = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (!ft_strchr_bonus(stash, '\n') && rd_bytes > 0)
	{
		rd_bytes = (int)read(fd, buffer, BUFFER_SIZE);
		if (rd_bytes < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[rd_bytes] = '\0';
		temp = sjoin_bonus(stash, buffer);
		free(stash);
		stash = temp;
	}
	free(buffer);
	return (stash);
}

int	calculate_line_length_bonus(char *stash)
{
	int	i;

	i = 0;
	if (stash == NULL)
		return (0);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	return (i);
}

char	*extract_line_bonus(char *stash)
{
	int		i;
	char	*line;
	int		len;

	i = 0;
	len = calculate_line_length_bonus(stash);
	if (len == 0)
		return (NULL);
	line = malloc((len + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_stash_bonus(char *stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_stdup_bonus(stash + i + 1);
	if (!new_stash)
		return (NULL);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_and_store_bonus(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = extract_line_bonus(buffer[fd]);
	buffer[fd] = update_stash_bonus(buffer[fd]);
	return (line);
}

/* int main(void)
{
	int fd;
	char *line;

	fd = open("dict.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line); // Affiche la ligne
		free(line);         // Libère la mémoire de la ligne
	}

	close(fd);
	return (0);
} */