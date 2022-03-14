
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

char    *check_remainder(char *remainder, char **line)
{
    char    *p_n;

    p_n = 0;
    if (remainder)
    {
        if ((p_n = ft_strchr(remainder, '\n')))
        {
            *p_n = '\0';
            *line = ft_strdup(remainder);
            p_n++;
            ft_strcpy(remainder, p_n);
        }
        else
        {
             *line = ft_strdup(remainder);
        }
    }
    else
        {
            *line = ft_strnew(1);
        }
        return (p_n);
}

int     get_next_line(int fd, char **line)
{
    int     BUFFER_SIZE = 1000000;
    
    char    buf[BUFFER_SIZE + 1];
    char    *p_n;
    char    *tmp;
    static char     *remainder;
    int     byte_read;

    p_n = check_remainder(remainder, line); 
    while (!p_n && (byte_read = read(fd, buf, BUFFER_SIZE)))
    {
        buf[byte_read] = '\0';
        if ((p_n = ft_strchr(buf, '\n')))
        {
            *p_n = '\0';
            p_n++;
            remainder = ft_strdup(p_n);
        }
        tmp = *line;
        *line = ft_strjoin(*line, buf);
        free(tmp);
    }
    return (0);
}



int     main(void)
{
    char    *line;
    int     fd;

    fd = open("text.txt", O_RDONLY);
    get_next_line(fd, &line);
    printf("\n\n------------------------------------------------------------\n\n");
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));

    get_next_line(fd, &line);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));

    get_next_line(fd, &line);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));

    get_next_line(fd, &line);
    printf("%s -- (%zu)\n\n", line, ft_strlen(line));

    close(fd);
    return (0);
}