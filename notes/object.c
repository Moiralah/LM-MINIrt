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

void	apply_transform(t_obj *obj, t_tuple **transform)
{
	t_tuple	**t;

	if (obj->type == 'S')
	{
		t = ((t_sphere *)obj->data)->t_matrix;
		((t_sphere *)obj->data)->t_matrix = mxm(transform, t);
	}
	else if (obj->type == 'P')
	{
		t = ((t_plane *)obj->data)->t_matrix;
		((t_plane *)obj->data)->t_matrix = mxm(transform, t);
	}
	else if (obj->type == 'C')
	{
		t = ((t_cylinder *)obj->data)->t_matrix;
		((t_cylinder *)obj->data)->t_matrix = mxm(transform, t);
	}
}
