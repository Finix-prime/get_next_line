/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:17:08 by pmethira          #+#    #+#             */
/*   Updated: 2022/03/18 13:26:20 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *str)
{
	char	*buf;
	int		byte_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	byte_read = 1;
	while (!(ft_strchr(str, '\n')) && byte_read != 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buf);
			return (0);
		}
		buf[byte_read] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_line(char *str)
{
	char	*s;
	int		i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*str_left(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!s)
		return (0);
	i++;
	j = 0;
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	free(str);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*str[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = read_line(fd, str[fd]);
	if (!str[fd])
		return (0);
	line = get_line(str[fd]);
	str[fd] = str_left(str[fd]);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

int     main(void)
{
    char    *line;
    int     fd;

    fd = open("text.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));
	free(line);
    line = get_next_line(fd);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));
	free(line);
    line = get_next_line(fd);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));;
	free(line);
    line = get_next_line(fd);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));
	free(line);
    line = get_next_line(fd);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));
	free(line);
 	line = get_next_line(fd);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));
	free(line);
    close(fd);

    return (0);
}*/

#include <stdio.h>
#include <fcntl.h>

int     main(void)
{
    char    *line;
	char	*buff;
    int     fd[3];
	int 	i;

	i = 0;
    fd[0] = open("text.txt", O_RDONLY);
	fd[1]= open("text.txt", O_RDONLY);
	fd[2] = open("text.txt", O_RDONLY);
	buff = "";

	while (read(fd[0], buff, BUFFER_SIZE) && read(fd[1], buff, BUFFER_SIZE) && read(fd[2], buff, BUFFER_SIZE))
	{
		line = get_next_line(fd[0]);
    	printf("%s -- (%zu)\n\n", line, ft_strlen(line));
		free(line);
		line = get_next_line(fd[1]);
    	printf("%s -- (%zu)\n\n", line, ft_strlen(line));
		free(line);
		line = get_next_line(fd[2]);
    	printf("%s -- (%zu)\n\n", line, ft_strlen(line));
		free(line);
	}
    close(fd[0]);
	close(fd[1]);
	close(fd[2]);

    return (0);
}
