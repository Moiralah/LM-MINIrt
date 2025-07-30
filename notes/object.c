/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:39:26 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:39:27 by huidris          ###   ########.fr       */
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
	// if (obj->type == 'C')
	// 	return (((t_cylinder *)(obj->data))->t_matrix);
	if (obj->type == 'T')
		return (((t_test_shape *)(obj->data))->t_matrix);
	return (NULL);
}

t_tuple	*get_obj_ori(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->ori);
	// if (obj->type == 'C')
	// 	return (((t_cylinder *)(obj->data))->ori);
	return (NULL);
}

t_mat	*get_obj_mat(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->mat);
	if (obj->type == 'P')
		return (((t_plane *)(obj->data))->mat);
	// if (obj->type == 'C')
	// 	return (((t_cylinder *)(obj->data))->mat);
	return (NULL);
}

t_obj	*sphere(t_tuple *origin, t_mat *mat, double radius)
{
	t_sphere	*new_sphere;
	t_obj		*obj;
	t_tuple		*w_ori;
	t_tuple		*move;
	t_tuple		**temp[2];

	w_ori = tuple(4, 0.0, 0.0, 0.0, 1.0);
	move = sub(origin, w_ori);
	new_sphere = calloc(1, sizeof(t_sphere));
	temp[0] = translate(4, move->val[0], move->val[1], move->val[2]);
	temp[1] = scale(4, radius, radius, radius);
	new_sphere->t_matrix = mxm(temp[1], temp[0]);
	free_m(temp[0], len_m(temp[0]));
	free_m(temp[1], len_m(temp[1]));
	new_sphere->mat = mat;
	new_sphere->ori = w_ori;
	new_sphere->rad = radius;
	obj = object(new_sphere, 'S');
	return (obj);
}
