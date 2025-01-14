/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:48:43 by npederen          #+#    #+#             */
/*   Updated: 2025/01/14 16:48:43 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;
	ssize_t		nbytes;
	char		*tmp;

	line = NULL;
	nbytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return(NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!stash)
		stash = ft_strdup("");
	while (nbytes > 0)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if(nbytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[nbytes] = '\0';
		stash = ft_strjoin(stash, buffer);
		if ((ft_strchr(buffer, '\n')))
			break ;
	}
	free(buffer);
	if (*stash == '\0')
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
	nbytes = 0;
	while (stash[nbytes] != '\n' && stash[nbytes] != '\0')
		nbytes++;
	if (stash[nbytes] == '\n')
		nbytes++;
	line = malloc((nbytes + 1) * sizeof(char));
	if (!line)
		return (NULL);
	line[nbytes] = '\0';
	nbytes--;
	while (0 <= nbytes)
	{
		line[nbytes] = stash[nbytes];
		nbytes--;
	}
	nbytes = 0;
	while (stash[nbytes] != '\n' && stash[nbytes] != '\0')
		nbytes++;
	if (stash[nbytes] == '\n')
		nbytes++;
	tmp = malloc((ft_strlen(stash) - nbytes + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	int	i;
	i = 0;
	while (stash[nbytes])
	{
		tmp[i] = stash[nbytes];
		i++;
		nbytes++;
	}
	free(stash);
	tmp[i] = '\0';
	stash = tmp;
	return(line);
}

/*int	main(void)
{
	int		fd;

	fd = open("test.txt", O_RDONLY);
	char* line = get_next_line(fd);
	printf("line 1: %s", line);
	free(line);
	//printf("line 2: %s", get_next_line(fd));
	//printf("line 3: %s", get_next_line(fd));
	close(fd);
	char *line;
    printf("Saisissez du texte (Ctrl+D pour terminer) :\n");
    while ((line = get_next_line(0)) != NULL)
    {
        printf("Lu : %s", line);
        free(line);
    }*/
//	return (0);
//}*/