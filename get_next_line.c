/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:17:08 by pmethira          #+#    #+#             */
/*   Updated: 2022/03/13 22:24:56 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

const   int BUFFER_SIZE = 42;

char	*read_line(int fd, char *str, char *remain)
{
	char	*buf;
	int		byte_read;

	byte_read = -1;
	while (remain[++byte_read])
		str[byte_read] = remain[byte_read];
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	byte_read = 1;
	while(!(ft_strchr(str, '\n')) && byte_read)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (!byte_read)
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
	while (str[i] && str[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
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
	char	*str;
	char	*line;
	char	*remain;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = read_line(fd, str, remain);
	if (!str)
	{
		return (0);
	}
	line = get_line(str);
	remain = str_left(str);
	return (line);
}

#include <stdio.h>
#include <fcntl.h>

int     main(void)
{
    char    *line;
    int     fd;

    fd = open("text.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("\n\n----------------------------------------------------\n\n");
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));

    line = get_next_line(fd);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));

    line = get_next_line(fd);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));;

    line = get_next_line(fd);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));

    line = get_next_line(fd);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));

    close(fd);

    return (0);
}
