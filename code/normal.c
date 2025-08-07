/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:38:50 by huidris           #+#    #+#             */
/*   Updated: 2025/08/02 22:18:50 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*sphere_n(t_obj *obj, t_tuple *p)
{
	t_sphere	*sphere;
	t_tuple		*obj_n;
	t_tuple		*norm_n;

	sphere = (t_sphere *)(obj->data);
	obj_n = sub(p, sphere->ori);
	if (!obj_n)
		return (NULL);
	norm_n = norm(obj_n);
	return (free_t(obj_n), norm_n);
}

t_tuple	*cylinder_n(t_obj *obj, t_tuple *point)
{
	t_cylinder	*cy;
	double		dist;

	cy = (t_cylinder *)(obj->data);
	dist = pow(point->val[0], 2) + pow(point->val[2], 2);
	if ((dist < 1) && (point->val[1] >= (cy->max - EPSILON)))
		return (tuple(4, 0.0, 1.0, 0.0, 0.0));
	else if ((dist < 1) && (point->val[1] <= (cy->min + EPSILON)))
		return (tuple(4, 0.0, -1.0, 0.0, 0.0));
	else
		return (tuple(4, point->val[0], 0.0, point->val[2], 0.0));
	return (NULL);
}

t_tuple	**get_obj_n(t_obj *obj, t_tuple *world_p)
{
	t_tuple	**obj_trans;
	t_tuple	**obj_m;
	t_tuple	*obj_p;
	t_tuple	*obj_n;

	obj_p = world_to_obj_point(get_inv_tf(obj), world_p);
	if (!obj_p)
		return (NULL);
	if (obj->type == 'S')
		obj_n = sphere_n(obj, obj_p);
	else if (obj->type == 'P')
		obj_n = tuple(4, 0.0, 1.0, 0.0, 0.0);
	else if (obj->type == 'C')
		obj_n = cylinder_n(obj, obj_p);
	free_t(obj_p);
	if (!obj_n)
		return (NULL);
	obj_m = matrix(1, obj_n);
	if (!obj_m)
		return (NULL);
	obj_trans = transpose(obj_m);
	if (!obj_trans)
		return (free_m(obj_m, len_m(obj_m)), NULL);
	return (free_m(obj_m, len_m(obj_m)), obj_trans);
}

t_tuple	*normal_at(t_obj *obj, t_tuple *world_p)
{
	t_tuple	**world_trans;
	t_tuple	**world_m;
	t_tuple	**obj_n;
	t_tuple	*world_n[2];

	obj_n = get_obj_n(obj, world_p);
	if (!obj_n)
		return (NULL);
	world_trans = transpose(get_inv_tf(obj));
	if (!world_trans)
		return (free_m(obj_n, len_m(obj_n)), NULL);
	world_m = mxm(world_trans, obj_n);
	free_m(world_trans, len_m(world_trans));
	free_m(obj_n, len_m(obj_n));
	if (!world_m)
		return (NULL);
	world_trans = transpose(world_m);
	free_m(world_m, len_m(world_m));
	if (!world_trans)
		return (NULL);
	world_n[0] = world_trans[0];
	world_n[0]->val[3] = 0;
	world_n[1] = norm(world_n[0]);
	free_m(world_trans, len_m(world_trans));
	return (world_n[1]);
}
