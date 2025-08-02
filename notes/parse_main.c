/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:12 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:41:13 by huidris          ###   ########.fr       */
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
	obj_amount(data);
}

void	print_content(t_data *data)
{
	int	i;

	i = -1;
	if (!data || !data->data)
		return ;
	while (data->data[++i])
		printf("%s\n", data->data[i]);
}
