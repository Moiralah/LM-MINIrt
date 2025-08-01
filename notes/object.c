/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:39:26 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 20:43:23 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*object(void *data, char type)
{
	t_obj	*new_obj;

	new_obj = calloc(1, sizeof(t_obj));
	new_obj->data = data;
	new_obj->type = type;
	return (new_obj);
}

t_tuple	**get_obj_tf(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->t_matrix);
	if (obj->type == 'P')
		return (((t_plane *)(obj->data))->t_matrix);
	if (obj->type == 'C')
		return (((t_cylinder *)(obj->data))->t_matrix);
	return (NULL);
}

t_tuple	*get_obj_ori(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->ori);
	if (obj->type == 'P')
		return (((t_plane *)(obj->data))->ori);
	if (obj->type == 'C')
		return (((t_cylinder *)(obj->data))->ori);
	return (NULL);
}

t_mat	*get_obj_mat(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->mat);
	if (obj->type == 'P')
		return (((t_plane *)(obj->data))->mat);
	if (obj->type == 'C')
		return (((t_cylinder *)(obj->data))->mat);
	return (NULL);
}

t_obj	*sphere(t_tuple *origin, t_mat *mat, double radius)
{
	t_obj		*obj;
	t_sphere	*new_sphere;
	t_tuple		*w_ori;
	t_tuple		*move;
	t_tuple		**temp[2];

	w_ori = tuple(4, 0.0, 0.0, 0.0, 1.0);
	move = sub(origin, w_ori);
	new_sphere = calloc(1, sizeof(t_sphere));
	temp[0] = scale(4, radius, radius, radius);
	temp[1] = translate(4, move->val[0], move->val[1], move->val[2]);
	new_sphere->t_matrix = mxm(temp[1], temp[0]);
	free_m(temp[0], len_m(temp[0]));
	free_m(temp[1], len_m(temp[1]));
	new_sphere->mat = mat;
	new_sphere->ori = w_ori;
	new_sphere->rad = radius;
	obj = object(new_sphere, 'S');
	return (obj);
}

t_obj	*cylinder(t_tuple *origin, t_tuple *normal, t_mat *mat, t_tuple *dim)
{
	t_obj		*obj;
	t_cylinder	*new_cy;
	t_tuple		**temp[2];
	t_tuple		*w_ori;
	t_tuple		*move;

	w_ori = tuple(4, 0.0, 0.0, 0.0, 1.0);
	if (!w_ori)
		return (NULL);
	move = sub(origin, w_ori);
	print_t(move);
	if (!move)
		return (NULL);
	new_cy = calloc(1, sizeof(t_cylinder));
	new_cy->t_matrix = rotate(4, 3, normal->val[0] * 90, normal->val[1] * 90, normal->val[2] * 90);
	if (!new_cy->t_matrix)
		return (NULL);
	temp[0] = new_cy->t_matrix;
	temp[1] = scale(4, dim->val[0], dim->val[1], dim->val[0]);
	new_cy->t_matrix = mxm(temp[1], new_cy->t_matrix);
	free_m(temp[0], len_m(temp[0]));
	free_m(temp[1], len_m(temp[1]));
	temp[0] = new_cy->t_matrix;
	temp[1] = translate(4, move->val[0], move->val[1], move->val[2]);
	new_cy->t_matrix = mxm(temp[1], new_cy->t_matrix);
	free_m(temp[0], len_m(temp[0]));
	free_m(temp[1], len_m(temp[1]));
	new_cy->mat = mat;
	new_cy->ori = w_ori;
	new_cy->rad = dim->val[0];
	new_cy->max = 1.0; 
	new_cy->min = -1.0;
	new_cy->h = dim->val[1];
	new_cy->closed = 1;
	obj = object(new_cy, 'C');
	return (obj);
}
