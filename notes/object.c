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

void	free_obj(t_obj *obj)
{
	if (obj->type == 'S')
		free_sphere((t_sphere *)(obj->data));
	if (obj->type == 'P')
		free_plane((t_plane *)(obj->data));
	if (obj->type == 'C')
		free_cylinder((t_cylinder *)(obj->data));
}

void	apply_tf(t_obj *obj, t_tuple **transform)
{
	t_tuple	**final_tf;
	t_tuple	**inv_tf;

	inv_tf = get_inv_tf(obj);
	if (!inv_tf)
		final_tf = transform;
	else
	{
		final_tf = mxm(transform, inv_tf);
		free_m(transform, len_m(transform));
		free_m(inv_tf, len_m(inv_tf));
	}
	if (obj->type == 'S')
		((t_sphere *)obj->data)->inv_tf = final_tf;
	else if (obj->type == 'P')
		((t_plane *)obj->data)->inv_tf = final_tf;
	else if (obj->type == 'C')
		((t_cylinder *)obj->data)->inv_tf = final_tf;
}
