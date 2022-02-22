#include "../includes/minirt.h"

int open_file(char *filepath)
{
    int fd;

    fd = open(filepath, O_RDONLY);
    if (fd == -1)
    {
        printf("Error ! Could not open file: %s\n", filepath);
        return -1;
    }
    return (fd);
}

static int    wl_read(int fd, char *buf, int *byte)
{
    *byte = read(fd, buf, 1);
    return (*byte);
}

static int    get_next_line(char **line, int fd)
{
    int			i;
    int			r;
    char		c;
    char		*buf;

    buf = (char *)malloc(10000);
    i = 0;
    r = 1;
    while (wl_read(fd, &c, &r) > 0 && c != '\n' && c != '\0')
    {
        if (c != '\n' && c != '\0')
            buf[i] = c;
        i++;
    }
    buf[i] = '\0';
    *line = ft_strdup(buf);
	free(buf);
    return (r);
}

void    parse_scene(t_scene *scene)
{
    char	*line;

	line = NULL;
	while (get_next_line(&line, scene->fd) > 0)
	{
		
	}
}
