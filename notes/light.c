/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:38:29 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:39:00 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*light(t_tuple *position, t_tuple *intensity)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = position;
	light->intensity = intensity;
	return (light);
}

t_light	*copy_light(t_light *old)
{
	t_light	*new;
	t_tuple	*new_pos;

	new_pos = copy_t(old->position);
	if (!new_pos)
		return (NULL);
	new = light(new_pos, old->intensity);
	return (new);
}

t_tuple	*world_to_obj_point(t_tuple **t_matrix, t_tuple *world_point)
{
	t_tuple	**inverse_m;
	t_tuple	**point_m;
	t_tuple	**obj_p;
	t_tuple	*result;

	result = NULL;
	point_m = matrix(2, world_point);
	if (!point_m)
		return (NULL);
	inverse_m = inverse(t_matrix);
	if (!inverse_m)
		return (free_m(point_m, len_m(point_m)), NULL);
	obj_p = mxm(inverse_m, transpose(point_m));
	if (obj_p)
		result = (transpose(obj_p))[0];
	free_m(inverse_m, 2);
	free(point_m);
	free(obj_p);
	return (result);
}

t_tuple	*reflect(t_tuple *in, t_tuple *normal)
{
	t_tuple	*result;
	t_tuple	*temp;
	double	dot_product;

	dot_product = dot(in, normal);
	temp = mult(normal, 2.0 * dot_product);
	if (!temp)
		return (NULL);
	result = sub(in, temp);
	free_t(temp);
	return (result);
}

int	shadowed(t_world *w, t_tuple *point)
{
	t_its	**its_list;
	t_its	*its;
	t_ray	*temp;
	t_tuple	*to_light;
	double	dist;

	to_light = sub(w->light->position, point);
	dist = mag(to_light);
	to_light = norm(to_light);
	temp = ray(point, to_light);
	its_list = its_world(w, temp);
	its = hit(its_list);
	if (!its)
		return (0);
	else if (its->len >= dist)
		return (0);
	return (1);
}
