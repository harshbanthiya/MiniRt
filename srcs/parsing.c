#include "../includes/minirt.h"
#include "../includes/structs.h"

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

void    detect_elem(char *line, t_scene *scene)
{
	if (line[0] == 'A') //amb
		parse_amb(line, scene);
	if (line[0] == 'C') //cam
		parse_cam(line, scene);
	if (line[0] == 'L') //light
		parse_light(line, scene);
	if (line[0] == 'p' && line[1] == 'l') //plane
		parse_plane(line, scene);
	if (line[0] == 's' && line[1] == 'p') //sphere
		parse_sphere(line, scene);
	if (line[0] == 'c' && line[1] == 'y') //cylinder
		parse_cylinder(line, scene);
}

void    parse_scene(t_scene *scene)
{
	char	*line;

	line = NULL;
	while (get_next_line(&line, scene->fd) > 0)
	{
		detect_elem(line, scene);
		free(line);
	}
	close(scene->fd);
}
