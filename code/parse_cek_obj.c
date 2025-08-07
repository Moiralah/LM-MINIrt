/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cek_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:05 by huidris           #+#    #+#             */
/*   Updated: 2025/08/07 04:38:15 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_sphere(t_data *data)
{
	char	**temp;
	char	*error_msg;
	int		i;

	i = -1;
	error_msg = "Error: Format: 'sp <x,y,z> <dia.> <R,G,B>'.";
	while (data->data[++i])
	{
		if (check_char(data->data[i], "sp ") != 1)
			continue ;
		temp = ft_split(data->data[i], ' ');
		if (!temp)
			return ;
		if (ft_arraylen(temp) != 8)
		{
			free2d(temp);
			return (perr(error_msg), exit(1));
		}
		check_range(0.1, 1000, ft_atof(temp[4]));
		check_range(0, 255, ft_atof(temp[5]));
		check_range(0, 255, ft_atof(temp[6]));
		check_range(0, 255, ft_atof(temp[7]));
		free2d(temp);
	}
}

void	check_plane(t_data *data)
{
	char	**temp;
	char	*error_msg;
	int		i;

	i = -1;
	error_msg = "Error: Format:'pl <x,y,z> <x,y,z> <R,G,B>'.";
	while (data->data[++i])
	{
		if (check_char(data->data[i], "pl ") != 1)
			continue ;
		temp = ft_split(data->data[i], ' ');
		if (!temp)
			return ;
		if (ft_arraylen(temp) != 10)
			return (perr(error_msg), free2d(temp), exit(1));
		check_range(-1, 1, ft_atof(temp[4]));
		check_range(-1, 1, ft_atof(temp[5]));
		check_range(-1, 1, ft_atof(temp[6]));
		check_range(0, 255, ft_atof(temp[7]));
		check_range(0, 255, ft_atof(temp[8]));
		check_range(0, 255, ft_atof(temp[9]));
		free2d(temp);
	}
}

void	check_cylinder(t_data *data)
{
	char	**temp;
	char	*error_msg;
	int		i;

	i = -1;
	error_msg = "Error: Format:'cy <x,y,z> <x,y,z> <dia.> <height> <R,G,B>'.";
	while (data->data[++i])
	{
		if (check_char(data->data[i], "cy ") != 1)
			continue ;
		temp = ft_split(data->data[i], ' ');
		if (!temp)
			return ;
		if (ft_arraylen(temp) != 12)
			return (perr(error_msg), free2d(temp), exit(1));
		check_range(-1, 1, ft_atof(temp[4]));
		check_range(-1, 1, ft_atof(temp[5]));
		check_range(-1, 1, ft_atof(temp[6]));
		check_range(0.1, 1000, ft_atof(temp[7]));
		check_range(0.1, 1000, ft_atof(temp[8]));
		check_range(0, 255, ft_atof(temp[9]));
		check_range(0, 255, ft_atof(temp[10]));
		check_range(0, 255, ft_atof(temp[11]));
		free2d(temp);
	}
}
