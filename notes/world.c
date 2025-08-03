/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:39:57 by huidris           #+#    #+#             */
/*   Updated: 2025/08/03 23:04:17 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world	*world(t_data *data)
{
	t_world		*w;

	w = malloc(sizeof(t_world));
	if (!w)
		return (NULL);
	w->a_ratio = data->a_ratio;
	w->a_color = copy_t(data->a_color);
	w->light = light(data->l_pos, mult(data->l_color, data->l_ratio));
	w->object = malloc((data->obj_amt + 1) * sizeof(t_obj *));
	w->object[data->obj_amt] = NULL;
	set_obj(w, data);
	w->c = camera(WIDTH, HEIGHT, data->c_fov);
	w->c->transform = view_transform(data->c_ori, add(data->c_ori, data->c_dir),
			tuple(4, 0.0, 1.0, 0.0, 0.0));
	w->c->inverse_transform = inverse(w->c->transform);
	return (w);
}

#define SP	0.9
#define DF	0.9
#define SH	200.0

void	set_obj(t_world *w, t_data *data)
{
	t_mat		*m;
	int			i;

	i = -1;
	while (d->sp)
	{
		m = material(data->sp->color, tuple(4, data->a_ratio, SP, DF, SH));
		w->object[++i] = sphere(data->sp->ori, m, data->sp->rad);
		data->sp = data->sp->next;
	}
	while (d->pl)
	{
		m = material(data->pl->color, tuple(4, data->a_ratio, SP, DF, SH));
		w->object[++i] = plane(data->pl->ori, m);
		data->pl = data->pl->next;
	}
	while (d->cy)
	{
		m = material(data->cy->color, tuple(4, data->a_ratio, SP, DF, SH));
		w->object[++i] = cylinder(matrix(3, data->cy->ori, data->cy->normalv),
				m, tuple(2, data->cy->rad, data->cy->height, 1.0, -1.0), 1);
		data->cy = data->cy->next;
	}
}

t_its	**its_world(t_world *world, t_ray *ray)
{
	t_its	**merged_list;
	t_its	**its_list;
	int		i;

	i = -1;
	merged_list = NULL;
	while (world->obj[++i])
	{
		its_list = calculate_its(world->obj[i], ray);
		if (!merged_list)
			merged_list = its_list;
		else if (its_list)
			merged_list = merge_its_s(merged_list, its_list);
	}
	if (!merged_list)
		return (NULL);
	i = 0;
	while (merged_list[i])
		i++;
	return (merge(merged_list, i));
}

t_tuple	*world_to_obj_point(t_tuple **t_matrix, t_tuple *world_point)
{
	t_tuple	**point_m[2];
	t_tuple	**obj_p[2];
	t_tuple	*result;

	result = NULL;
	point_m[0] = matrix(1, world_point);
	point_m[1] = transpose(point_m[0]);
	free(point_m[0]);
	obj_p[0] = mxm(t_matrix, point_m[1]);
	free_m(point_m[1], len_m(point_m[1]));
	if (obj_p[0])
	{
		obj_p[1] = transpose(obj_p[0]);
		result = obj_p[1][0];
		free(obj_p[1]);
	}
	free_m(obj_p[0], len_m(obj_p[0]));
	return (result);
}

void	free_world(t_world * world)
{
	int	i;

	i = -1;
	while (world->obj[++i])
		free_obj(world->obj[i]);
	free_light(world->light);
	free_t(world->a_color);
	free(world);
}
