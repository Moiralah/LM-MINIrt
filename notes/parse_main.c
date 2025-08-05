/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:12 by huidris           #+#    #+#             */
/*   Updated: 2025/08/06 04:10:16 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	check_number(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->data[i])
	{
		if ((ft_strncmp(data->data[i], "A ", 2) == 0)
			|| (ft_strncmp(data->data[i], "C ", 2) == 0)
			|| (ft_strncmp(data->data[i], "L ", 2) == 0))
			j = 3;
		else if (((ft_strncmp(data->data[i], "sp ", 3) == 0)
				|| (ft_strncmp(data->data[i], "pl ", 3) == 0)
				|| (ft_strncmp(data->data[i], "cy ", 3) == 0)))
			j = 4;
		while (data->data[i][j])
		{
			if (data->data[i][j] == '.' || data->data[i][j] == ' '
				|| data->data[i][j] == '-'
				|| (data->data[i][j] >= '0' && data->data[i][j] <= '9'))
				j++;
			else
				return (perr("Error: Invalid number format."), exit(1));
		}
		i++;
	}
}

void	content(char *file, t_data *data)
{
	char	*content;
	char	*temp;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perr("Error: Invalid file."), exit(1));
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
	free(temp);
}

void	validate_data(char *file, t_data *data)
{
	check_name(file);
	content(file, data);
	check_format(data->data);
	check_number(data);
	check_ambient(data);
	check_camera(data);
	check_light(data);
	check_sphere(data);
	check_plane(data);
	check_cylinder(data);
}

t_data	*input_data(char *av)
{
	int		i;
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	validate_data(av, data);
	i = -1;
	while (data->data[++i])
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
	}
	obj_amount(data);
	return (data);
}
