/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_set_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:20 by huidris           #+#    #+#             */
/*   Updated: 2025/08/05 22:17:07 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_sphere(char *line, t_data *data)
{
	char	**t;
	t_sp	*new_sp;
	t_sp	*cur_sp;

	t = ft_split(line, ' ');
	new_sp = ft_calloc(1, sizeof(t_sp));
	new_sp->ori = tuple(4, ft_atof(t[1]), ft_atof(t[2]), ft_atof(t[3]), 1);
	new_sp->rad = ft_atof(t[4]) / 2;
	new_sp->color = tuple(3, ft_atof(t[5]) / 255.0,
			ft_atof(t[6]) / 255.0, ft_atof(t[7]) / 255.0);
	new_sp->next = NULL;
	if (!data->sp)
		data->sp = new_sp;
	else
	{
		cur_sp = data->sp;
		while (cur_sp->next)
			cur_sp = cur_sp->next;
		cur_sp->next = new_sp;
	}
	free2d(t);
}

void	set_plane(char *line, t_data *data)
{
	char	**t;
	t_pl	*new_pl;
	t_pl	*cur_pl;

	t = ft_split(line, ' ');
	new_pl = ft_calloc(1, sizeof(t_pl));
	new_pl->ori = tuple(4, ft_atof(t[1]), ft_atof(t[2]), ft_atof(t[3]), 1);
	new_pl->normalv = tuple(4, ft_atof(t[4]), ft_atof(t[5]), ft_atof(t[6]), 0);
	new_pl->color = tuple(3, ft_atof(t[7]) / 255.0,
			ft_atof(t[8]) / 255.0, ft_atof(t[9]) / 255.0);
	new_pl->next = NULL;
	if (!data->pl)
		data->pl = new_pl;
	else
	{
		cur_pl = data->pl;
		while (cur_pl && (cur_pl->next != NULL))
			cur_pl = cur_pl->next;
		cur_pl->next = new_pl;
	}
	free2d(t);
}

void	set_cylinder(char *line, t_data *data)
{
	char	**t;
	t_cy	*new_cy;
	t_cy	*cur_cy;

	t = ft_split(line, ' ');
	new_cy = ft_calloc(1, sizeof(t_cy));
	new_cy->ori = tuple(4, ft_atof(t[1]),
			ft_atof(t[2]), ft_atof(t[3]), 1);
	new_cy->n = tuple(4, ft_atof(t[4]), ft_atof(t[5]), ft_atof(t[6]), 0);
	new_cy->rad = ft_atof(t[7]) / 2;
	new_cy->h = ft_atof(t[8]);
	new_cy->color = tuple(3, ft_atof(t[9]) / 255.0,
			ft_atof(t[10]) / 255.0, ft_atof(t[11]) / 255.0);
	new_cy->next = NULL;
	if (!data->cy)
		data->cy = new_cy;
	else
	{
		cur_cy = data->cy;
		while (cur_cy->next)
			cur_cy = cur_cy->next;
		cur_cy->next = new_cy;
	}
	free2d(t);
}

void	obj_amount(t_data *data)
{
	int	i;

	i = 0;
	while (data->data[i])
	{
		if (check_char(data->data[i], "sp ") == 1
			|| check_char(data->data[i], "pl ") == 1
			|| check_char(data->data[i], "cy ") == 1)
			data->obj_amt++;
		i++;
	}
}
