/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:50:27 by huidris           #+#    #+#             */
/*   Updated: 2025/08/05 17:54:42 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*convert_world_to_obj(t_tuple **inv_m, double x, double y, int *err)
{
	t_tuple	*world;
	t_tuple	*obj;

	*err = 0;
	world = tuple(4, x, y, -1.0, 1.0);
	if (!world)
		return (*err = 1, NULL);
	obj = world_to_obj_point(inv_m, world);
	free_t(world);
	if (!obj)
		return (*err = 1, NULL);
	return (obj);
}

t_tuple	*get_ray_direction(t_tuple **inv_m, int *err)
{
	t_tuple	*world;
	t_tuple	*obj;

	*err = 0;
	world = tuple(4, 0.0, 0.0, 0.0, 1.0);
	if (!world)
		return (*err = 1, NULL);
	obj = world_to_obj_point(inv_m, world);
	free_t(world);
	if (!obj)
		return (*err = 1, NULL);
	return (obj);
}

t_ray	*create_ray(t_tuple **inv_m, double world_x, double world_y)
{
	t_tuple	*obj_p0;
	t_tuple	*obj_p1;
	t_tuple	*dir;
	t_tuple	*norm_dir;
	int		err;

	obj_p0 = convert_world_to_obj(inv_m, world_x, world_y, &err);
	if (err)
		return (NULL);
	obj_p1 = get_ray_direction(inv_m, &err);
	if (err)
		return (free_t(obj_p0), NULL);
	dir = sub(obj_p0, obj_p1);
	free_t(obj_p0);
	if (!dir)
		return (free_t(obj_p1), NULL);
	norm_dir = norm(dir);
	free_t(dir);
	if (!norm_dir)
		return (free_t(obj_p1), NULL);
	return (ray(obj_p1, norm_dir));
}
