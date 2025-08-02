/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:38:50 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 21:48:42 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*sphere_n(t_obj *obj, t_tuple *p)
{
	t_sphere	*sphere;
	t_tuple		*obj_n;

	sphere = (t_sphere *)obj->data;
	obj_n = sub(p, sphere->ori);
	return (norm(obj_n));
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

t_tuple	*normal_at(t_obj *obj, t_tuple *world_p)
{
	t_tuple	*obj_p;
	t_tuple	*obj_n;
	t_tuple	**transform_matrix;
	t_tuple	**world_normal_matrix;
	t_tuple	*world_normal;

	obj_p = world_to_obj_point(get_obj_tf(obj), world_p);
	if (obj->type == 'S')
		obj_n = sphere_n(obj, obj_p);
	else if (obj->type == 'P')
		obj_n = tuple(4, 0.0, 1.0, 0.0, 0.0);
	else if (obj->type == 'C')
		obj_n = cylinder_n(obj, obj_p);
	transform_matrix = transpose(inverse(get_obj_tf(obj)));
	world_normal_matrix = mxm(transform_matrix, transpose(matrix(2, obj_n)));
	world_normal = (transpose(world_normal_matrix))[0];
	world_normal->val[3] = 0;
	free_m(transform_matrix, len_m(transform_matrix));
	free_m(world_normal_matrix, len_m(world_normal_matrix));
	free_t(obj_p);
	free_t(obj_n);
	return (norm(world_normal));
}
