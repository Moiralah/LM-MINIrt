#include "minirt.h"

void	remove_commas(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			str[i] = ' ';
		i++;
	}
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	content(char *file, t_data *data)
{
	char	*content;
	char	*temp;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perr("Invalid file."), exit(1));
	file = get_next_line(fd);
	while (file)
	{
		content = get_next_line(fd);
		if (content == NULL)
			break ;
		temp = file;
		file = ft_strjoin(temp, content);
	}
	close(fd);
	remove_commas(file);
	temp = ft_strnormalize_spaces(file);
	free(file);
	data->data = ft_split(temp, '\n');
}

void	validate_data(char *file, t_data *data)
{
	check_name(file);
	content(file, data);
	check_format(data->data);
	check_ambient(data);
	check_camera(data);
	check_light(data);
	check_sphere(data);
	check_plane(data);
	check_cylinder(data);
}

void	input_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->data[i])
	{
		if (ft_strncmp(data->data[i], "A ", 2) == 0)
			set_ambient(data->data[i], data);
		else if (ft_strncmp(data->data[i], "C ", 2) == 0)
			set_camera(data->data[i], data);
		else if (ft_strncmp(data->data[i], "L ", 2) == 0)
			set_light(data->data[i], data);
		else if (ft_strncmp(data->data[i], "sp ", 3) == 0)
			set_sphere(data->data[i], data);
		else if (ft_strncmp(data->data[i], "pl ", 3) == 0)
			set_plane(data->data[i], data);
		else if (ft_strncmp(data->data[i], "cy ", 3) == 0)
			set_cylinder(data->data[i], data);
		i++;
	}
}

void print_content(t_data *data)
{
	if (!data || !data->data)
		return;
	for (int i = 0; data->data[i]; i++)
		printf("%s\n", data->data[i]);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (perr("Invalid input. < ./miniRT xxx.rt >"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	validate_data(av[1], data);
	print_content(data);
	input_data(data);
	world(data);
}
