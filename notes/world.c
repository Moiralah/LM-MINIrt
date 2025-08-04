/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:39:57 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 22:54:03 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_objs(t_data *d, t_world *w, double *n)
{
	t_tuple	**v;
	t_mat	*m;
	t_tuple	*dim;
	int		i;

	i = -1;
	while (d->sp)
	{
		m = material(d->sp->color, tuple(4, d->a_ratio, n[0], n[1], n[2]));
		w->obj[++i] = sphere(d->sp->ori, m, d->sp->rad);
		d->sp = d->sp->next;
	}
	while (d->pl)
	{
		m = material(d->pl->color, tuple(4, d->a_ratio, n[0], n[1], n[2]));
		w->obj[++i] = plane(d->pl->ori, d->pl->normalv, m);
		d->pl = d->pl->next;
	}
	while (d->cy)
	{
		m = material(d->cy->color, tuple(4, d->a_ratio, n[0], n[1], n[2]));
		v = matrix(2, d->cy->ori, d->cy->n);
		dim = tuple(4, d->cy->rad, d->cy->h, 1.0, -1.0);
		w->obj[++i] = cylinder(v, m, dim, 1);
		d->cy = d->cy->next;
	}
}

t_world	*world(t_data *data)
{
	t_world		*world;
	double		mat_vals[3];

	mat_vals[0] = 0.9;
	mat_vals[1] = 0.9;
	mat_vals[2] = 200.0;
	world = ft_calloc(1, sizeof(t_world));
	if (!world)
		return (NULL);
	world->a_ratio = data->a_ratio;
	world->a_color = data->a_color;
	world->light = light(data->l_pos, mult(data->l_color, data->l_ratio));
	world->obj = ft_calloc(data->obj_amt + 1, sizeof(t_obj *));
	if (!world->obj)
		return (NULL);
	world->obj[data->obj_amt] = NULL;
	add_objs(data, world, mat_vals);
	return (world);
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
