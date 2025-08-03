/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_set_acl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:16 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:41:17 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_ambient(char *line, t_data *data)
{
	char	**temp;

	temp = ft_split(line, ' ');
	data->a_ratio = ft_atof(temp[1]);
	data->a_color = tuple(3, ft_atof(temp[2]),
			ft_atof(temp[3]), ft_atof(temp[4]));
	free2d(temp);
}

void	set_camera(char *line, t_data *data)
{
	char		**temp;

	temp = ft_split(line, ' ');
	data->c_ori = tuple(4, ft_atof(temp[1]),
			ft_atof(temp[2]), ft_atof(temp[3]), 1.0);
	data->c_dir = tuple(4, ft_atof(temp[4]),
			ft_atof(temp[5]), ft_atof(temp[6]), 0.0);
	data->c_fov = ft_atof(temp[7]);
	free2d(temp);
}

void	set_light(char *line, t_data *data)
{
	char	**temp;

	temp = ft_split(line, ' ');
	data->l_pos = tuple(4, ft_atof(temp[1]),
			ft_atof(temp[2]), ft_atof(temp[3]), 1.0);
	data->l_ratio = ft_atof(temp[4]);
	data->l_color = tuple(3, ft_atof(temp[5]),
			ft_atof(temp[6]), ft_atof(temp[7]));
	free2d(temp);
}
