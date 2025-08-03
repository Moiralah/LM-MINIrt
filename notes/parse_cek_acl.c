/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cek_acl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:01 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:41:02 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_ambient(t_data *data)
{
	char	**temp;
	char	*error_msg;
	int		i;

	error_msg = "Error: Ambient light format. Only one 'A' line.";
	if (check_freq(data->data, "A ", &i) != 1)
		return (perr(error_msg), exit(1));
	temp = ft_split(data->data[i], ' ');
	if (!temp)
		return ;
	if (ft_arraylen(temp) != 5)
	{
		free2d(temp);
		error_msg = "Error: Ambient light format. Only one 'A' line.";
		return (perr(error_msg), exit(1));
	}
	check_range(0.0, 1.0, ft_atof(temp[1]));
	check_range(0, 255, ft_atof(temp[2]));
	check_range(0, 255, ft_atof(temp[3]));
	check_range(0, 255, ft_atof(temp[4]));
	free2d(temp);
}

void	check_camera(t_data *data)
{
	char	**temp;
	char	*error_msg;
	int		i;

	error_msg = "Error: There should be exactly one 'C' line.";
	if (check_freq(data->data, "C ", &i) != 1)
		return (perr(error_msg), exit(1));
	temp = ft_split(data->data[i], ' ');
	if (!temp)
		return ;
	if (ft_arraylen(temp) != 8)
	{
		free2d(temp);
		error_msg = "Error: Format: 'C <x,y,z> <x,y,z> <FOV>'.";
		return (perr(error_msg), exit(1));
	}
	check_range(-1, 1, ft_atof(temp[4]));
	check_range(-1, 1, ft_atof(temp[5]));
	check_range(-1, 1, ft_atof(temp[6]));
	check_range(0, 180, ft_atof(temp[7]));
	free2d(temp);
}

void	check_light(t_data *data)
{
	char	**temp;
	char	*error_msg;
	int		i;

	error_msg = "Error: There should be exactly one 'C' line.";
	if (check_freq(data->data, "L ", &i) != 1)
		return (perr(error_msg), exit(1));
	temp = ft_split(data->data[i], ' ');
	if (!temp)
		return ;
	if (ft_arraylen(temp) != 8)
	{
		free2d(temp);
		error_msg = "Error: Format: 'L <x,y,z> <ratio> <R,G,B>'.";
		return (perr(error_msg), exit(1));
	}
	check_range(0.0, 1.0, ft_atof(temp[4]));
	check_range(0, 255, ft_atof(temp[5]));
	check_range(0, 255, ft_atof(temp[6]));
	check_range(0, 255, ft_atof(temp[7]));
	free2d(temp);
}
