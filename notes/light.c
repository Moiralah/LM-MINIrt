#include "minirt.h"

/* t_tuple	*eye(t_ray *ray)
{
	return (mult(ray->dir->val, -1.0, 4));
}

t_tuple	*light(t_tuple *light_pos, t_tuple *point_pos)
{
	return (sub(light_pos->val, point_pos->val, 4));
} */

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
		return (free_m(point_m, point_m[0]->size), NULL);
	obj_p = mxm(inverse_m, point_m);
	if (obj_p)
		result = obj_p[0];
	free_m(inverse_m, 2);
	free_m(obj_p, 2);
	free_m(point_m, 2);
	return (result);
}

t_tuple	*normal_at_obj(t_tuple **t_matrix, t_tuple *world_p, t_tuple *origin)
{
	t_tuple	**inverse_m;
	t_tuple	**world_n;
	t_tuple	**obj_n;
	t_tuple	*obj_p;

	obj_p = world_to_obj_point(t_matrix, world_p);
	if (!obj_p)
		return (NULL);
	obj_n = matrix(2, sub(obj_p, origin));
	if (!obj_n && !obj_n[0])
		return (free_t(obj_p), NULL);
	free_t(obj_p);
	inverse_m = inverse(t_matrix);
	if (!inverse_m)
		return (free_m(obj_n, 2), free_t(obj_p), NULL);
	transpose(inverse_m);
	world_n = mxm(inverse_m, obj_n);
	if (!world_n)
		return (free_m(obj_n, 2), free_m(inverse_m, 2), NULL);
	world_n[0]->val[3] = 0.0;
	obj_p = norm(world_n[0]);
	return (free_m(inverse_m, 2), free_m(world_n, 2), free_m(obj_n, 2), obj_p);
}

t_tuple	*reflect(t_tuple *in, t_tuple *normal)
{
	t_tuple	*result;
	double	dot_product;

	dot_product = dot(in, normal);
	result = sub(in, mult(normal, 2 * dot_product));
	if (!result)
		return (NULL);
	return (result);
}

t_light	*light(t_tuple *position, int intensity)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = position;
	light->intensity = intensity;
	return (light);
}
