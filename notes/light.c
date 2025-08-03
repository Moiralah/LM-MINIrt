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
	if (!result)
		return (NULL);
	return (result);
}

int	shadowed(t_world *world, t_tuple *point)
{
	t_its	**hits;
	t_its	*its;
	t_ray	*ray_to_light;
	t_tuple	*to_light[2];
	double	dist;

	to_light[0] = sub(world->light->position, point);
	if (!to_light[0])
		return (-1);
	dist = mag(to_light[0]);
	to_light[1] = norm(to_light[0]);
	free_t(to_light[0]);
	if (!to_light[1])
		return (-1);
	ray_to_light = ray(point, to_light[1]);
	free_t(to_light[1]);
	if (!ray_to_light)
		return (-1);
	hits = its_world(world, ray_to_light);
	its = hit(hits);
	if (its && (its->len < dist))
		return (1);
	return (0);
}

void	free_light(t_light *light)
{
	free_t(light->position);
	free_t(light->intensity);
	free(light);
}
