#include "minirt.h"

t_its	*intersect(t_ray *ray, t_obj *obj)
{
	if (obj->type == 'S')
		return (sphere_its(ray, (t_sphere *)obj->data));
	return (NULL);
}

t_ray	*transform(t_ray *r, t_tuple **t_matrix)
{
	t_tuple	**temp_m;
	t_tuple	**result_m;
	t_ray	*new_ray;
	t_tuple	*temp[2];

	temp[0] = NULL;
	temp[1] = NULL;
	temp_m = matrix(2, r->ori);
	if (!temp_m)
		return (NULL);
	if (!t_matrix)
		return (free_m(temp_m, len_m(temp_m)), NULL);
	result_m = mxm(t_matrix, transpose(temp_m));
	free(temp_m);
	temp_m = transpose(result_m);
	if (!temp_m)
		return (NULL);
	temp[0] = temp_m[0];
	free(temp_m);
	free(result_m);
	temp_m = matrix(2, r->dir);
	if (!temp_m)
		return (free_m(t_matrix, len_m(t_matrix)), NULL);
	result_m = mxm(t_matrix, transpose(temp_m));
	free(temp_m);
	temp_m = transpose(result_m);
	if (!temp_m)
		return (NULL);
	temp[1] = temp_m[0];
	free(temp_m);
	free(result_m);
	new_ray = ray(temp[0], temp[1]);
	if (!new_ray)
		(free_t(temp[0]), free_t(temp[1]));
	return (new_ray);
}

// Calculates the position of a ray at a given time.
t_tuple	*travel(t_ray *ray, double time)
{
	t_tuple	*velo;
	t_tuple	*new_pos;

	velo = mult(ray->dir, time);
	new_pos = add(ray->ori, velo);
	free_t(velo);
	return (new_pos);
}
