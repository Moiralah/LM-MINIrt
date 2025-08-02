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

	new_obj = ft_calloc(1, sizeof(t_obj));
	if (!new_obj)
		return (NULL);
	new_obj->data = data;
	new_obj->type = type;
	return (new_obj);
}

t_tuple	**get_inv_tf(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->inv_tf);
	if (obj->type == 'P')
		return (((t_plane *)(obj->data))->inv_tf);
	if (obj->type == 'C')
		return (((t_cylinder *)(obj->data))->inv_tf);
	return (NULL);
}

/* t_tuple	*get_obj_ori(t_obj *obj)
{
	if (obj->type == 'S')
		return (((t_sphere *)(obj->data))->ori);
	if (obj->type == 'P')
		return (((t_plane *)(obj->data))->ori);
	if (obj->type == 'C')
		return (((t_cylinder *)(obj->data))->ori);
	return (NULL);
} */

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
		t = ((t_sphere *)obj->data)->inv_tf;
		((t_sphere *)obj->data)->inv_tf = mxm(transform, t);
	}
	else if (obj->type == 'P')
	{
		t = ((t_plane *)obj->data)->inv_tf;
		((t_plane *)obj->data)->inv_tf = mxm(transform, t);
	}
	else if (obj->type == 'C')
	{
		t = ((t_cylinder *)obj->data)->inv_tf;
		((t_cylinder *)obj->data)->inv_tf = mxm(transform, t);
	}
}
