#include "minirt.h"

void print_content(t_data *data)
{
	if (!data || !data->data)
		return;
	for (int i = 0; data->data[i]; i++)
		printf("%s\n", data->data[i]);
}

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

void	check_name(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
		i++;
	if (av[i - 3] == '.')
		if (av[i - 2] == 'r')
			if (av[i - 1] == 't')
				return ;
	return (perr("Invalid file format. File need '.rt' format."), exit(1));
}

int	check_char(char *line, char *s)
{
	if (ft_strncmp(line, s, ft_strlen(s)) != 0)
		return (0);
	return (1);
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

void	check_range(float min, float max, float value)
{
	if (value < min || value > max)
		return (perr("Value out of range: %f. Expected range: [%f, %f].",
				value, min, max), exit(1));
}

int	check_freq(char **data, char *s, int *i)
{
	int	j;
	int	k;

	*i = 0;
	j = 0;
	k = 0;
	while (data[k])
	{
		if (ft_strncmp(data[k], s, ft_strlen(s)) == 0)
		{
			j++;
			*i = k;
		}
		k++;
	}
	return (j);
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	check_ambient(t_data *data)
{
	int		i;
	char	**temp;

	if (check_freq(data->data, "A ", &i) != 1)
		return (perr("Error: Ambient light format. Only one 'A' line."),
			exit(1));
	temp = ft_split(data->data[i], ' ');
	if (ft_arraylen(temp) != 5)
	{
		free2d(temp);
		return (perr("Error: Format: 'A <ratio> <R, G, B>'."),
			exit(1));
	}
	check_range(0.0, 1.0, ft_atof(temp[1]));
	check_range(0, 255, ft_atof(temp[2]));
	check_range(0, 255, ft_atof(temp[3]));
	check_range(0, 255, ft_atof(temp[4]));
	free2d(temp);
}

void	check_camera(t_data *data)
{
	int		i;
	char	**temp;

	if (check_freq(data->data, "C ", &i) != 1)
		return (perr("Error: There should be exactly one 'C' line."), exit(1));
	temp = ft_split(data->data[i], ' ');
	if (ft_arraylen(temp) != 8)
	{
		free2d(temp);
		return (perr("Error: Format: 'C <x,y,z> <x,y,z> <FOV>'."), exit(1));
	}
	check_range(-1, 1, ft_atof(temp[4]));
	check_range(-1, 1, ft_atof(temp[5]));
	check_range(-1, 1, ft_atof(temp[6]));
	check_range(0, 180, ft_atof(temp[7]));
	free2d(temp);
}

void	check_light(t_data *data)
{
	int		i;
	char	**temp;

	if (check_freq(data->data, "L ", &i) != 1)
		return (perr("Error: There should be exactly one 'L' line."), exit(1));
	temp = ft_split(data->data[i], ' ');
	if (ft_arraylen(temp) != 8)
	{
		free2d(temp);
		return (perr("Error: Format: 'L <x,y,z> <ratio> <R,G,B>'."), exit(1));
	}
	check_range(0.0, 1.0, ft_atof(temp[4]));
	check_range(0, 255, ft_atof(temp[5]));
	check_range(0, 255, ft_atof(temp[6]));
	check_range(0, 255, ft_atof(temp[7]));
	free2d(temp);
}

void	check_sphere(t_data *data)
{
	int		i;
	char	**temp;

	i = 0;
	while (data->data[i])
	{
		if (check_char(data->data[i], "sp ") == 1)
		{
			temp = ft_split(data->data[i], ' ');
			if (ft_arraylen(temp) != 8)
			{
				free2d(temp);
				return (perr("Error: Format: 'sp <x,y,z> <sp dia.> <R,G,B>'."),
					exit(1));
			}
			check_range(0, 255, ft_atof(temp[5]));
			check_range(0, 255, ft_atof(temp[6]));
			check_range(0, 255, ft_atof(temp[7]));
			free2d(temp);
		}
		i++;
	}
}

void	check_plane(t_data *data)
{
	int		i;
	char	**temp;

	i = 0;
	while (data->data[i])
	{
		if (check_char(data->data[i], "pl ") == 1)
		{
			temp = ft_split(data->data[i], ' ');
			if (ft_arraylen(temp) != 10)
			{
				free2d(temp);
				return (perr("Error:Format:'pl <x,y,z> <x,y,z> <R,G,B>'."),
					exit(1));
			}
			check_range(-1, 1, ft_atof(temp[4]));
			check_range(-1, 1, ft_atof(temp[5]));
			check_range(-1, 1, ft_atof(temp[6]));
			check_range(0, 255, ft_atof(temp[7]));
			check_range(0, 255, ft_atof(temp[8]));
			check_range(0, 255, ft_atof(temp[9]));
			free2d(temp);
		}
		i++;
	}
}

void	check_cylinder(t_data *data)
{
	int		i;
	char	**temp;

	i = 0;
	while (data->data[i])
	{
		if (check_char(data->data[i], "cy ") == 1)
		{
			temp = ft_split(data->data[i], ' ');
			if (ft_arraylen(temp) != 12)
			{
				free2d(temp);
				return (perr("Error:Format:'cy <x,y,z> <x,y,z> <cy dia.> <cy height> <R,G,B>'."),
					exit(1));
			}
			check_range(-1, 1, ft_atof(temp[4]));
			check_range(-1, 1, ft_atof(temp[5]));
			check_range(-1, 1, ft_atof(temp[6]));
			check_range(0, 255, ft_atof(temp[9]));
			check_range(0, 255, ft_atof(temp[10]));
			check_range(0, 255, ft_atof(temp[11]));
			free2d(temp);
		}
		i++;
	}
}

void	check_format(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (ft_strncmp(data[i], "A ", 2) != 0
			&& ft_strncmp(data[i], "C ", 2) != 0
			&& ft_strncmp(data[i], "L ", 2) != 0
			&& ft_strncmp(data[i], "sp ", 3) != 0
			&& ft_strncmp(data[i], "pl ", 3) != 0
			&& ft_strncmp(data[i], "cy ", 3) != 0)
			return (perr("Error: 'A', 'C', 'L', 'sp', 'pl', or 'cy' only."),
				exit(1));
		i++;
	}
}

void	validate_data(char *file, t_data *data)
{
	check_name(file);
	content(file, data);
	print_content(data);
	check_format(data->data);
	check_ambient(data);
	check_camera(data);
	check_light(data);
	check_sphere(data);
	check_plane(data);
	check_cylinder(data);
}

// void	set_ambient(char *line)
// {
// 	char	**temp;
// 	t_mat	*ambient;

// 	temp = ft_split(line, ' ');
// 	//ambient = material(tuple(ft_atof));
// }

// void	input_data(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->data[i])
// 	{
// 		if (ft_strncmp(data->data[i], "A ", 2) == 0)
// 			set_ambient(data->data[i]);
// 		else if (ft_strncmp(data->data[i], "C ", 2) == 0)
// 			set_camera(data->data[i]);
// 		else if (ft_strncmp(data->data[i], "L ", 2) == 0)
// 			set_light(data->data[i]);
// 		else if (ft_strncmp(data->data[i], "sp ", 3) == 0)
// 			set_sphere(data->data[i]);
// 		else if (ft_strncmp(data->data[i], "pl ", 3) == 0)
// 			set_plane(data->data[i]);
// 		else if (ft_strncmp(data->data[i], "cy ", 3) == 0)
// 			set_cylinder(data->data[i]);
// 		i++;
// 	}
// }

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (perr("Invalid input. < ./miniRT xxx.rt >"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	validate_data(av[1], data);
	//input_data(data);
}
