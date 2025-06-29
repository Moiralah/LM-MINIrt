#include "minirt.h"

// Creates a ray with an origin and direction.
t_ray	*ray(t_tuple *origin, t_tuple *direction)
{
	t_ray	*new_ray;

	new_ray = calloc(1, sizeof(t_ray));
	if (!new_ray)
		return (NULL);
	new_ray->ori = origin;
	new_ray->dir = direction;
	return (new_ray);
}

// Calculates the position of a ray at a given time.
t_tuple	*travel(t_ray *ray, double time)
{
	t_tuple	*new_t_pos;
	double	*velo;
	double	*new_pos;

	velo = mult(ray->dir->val, time, ray->dir->size);
	new_pos = add(ray->ori->val, velo, ray->ori->size);
	new_t_pos = tuple(0.0);
	new_t_pos->val = new_pos;
	new_t_pos->size = ray->ori->size;
	free(velo);
	return (new_t_pos);
}

// Computes the intersections of a ray with a sphere.
t_its	*sphere_its(t_ray *r, t_sphere *sphere)
{
	t_obj		*obj;
	double		*result;
	double		*rto;
	double		rtc;
	double		h;

	obj = object(sphere, 's');
	if (!obj)
		return (NULL);
	rto = sub(sphere->ori->val, r->ori->val, r->ori->size);
	rtc = dot(rto, r->dir->val, r->dir->size);
	h = pow(mag(rto, r->ori->size), 2) - pow(rtc, 2);
	if (sqrt(h) > sphere->rad)
		return (free(rto), its(obj, NULL, 0));
	result = calloc(2, sizeof(double));
	if (!result)
		return (free(rto), free(obj), NULL);
	h = sqrt(pow(sphere->rad, 2) - h);
	result[0] = rtc - h;
	result[1] = rtc + h;
	if (result[0] == result[1])
		return (free(rto), its(obj, result, 1));
	return (free(rto), its(obj, result, 2));
}

void	transform(t_ray *ray, t_tuple **t_matrix)
{
	t_tuple	**temp_m;
	t_tuple	**result_m;

	temp_m = matrix(2, ray->ori);
	result_m = mxm(temp_m, inverse(t_matrix));
	ray->ori = result_m[0];
	free_m(temp_m, temp_m[0]->size);
	free(result_m);
	temp_m = matrix(2, ray->dir);
	result_m = mxm(temp_m, inverse(t_matrix));
	ray->dir = result_m[0];
	free_m(temp_m, temp_m[0]->size);
	free(result_m);
}

void	transform(t_ray *ray, t_tuple **t_matrix)
{
	t_tuple	**temp_m;
	t_tuple	**result_m;

	temp_m = matrix(2, ray->ori);
	result_m = mxm(temp_m, inverse(t_matrix));
	ray->ori = result_m[0];
	free_m(temp_m, temp_m[0]->size);
	free(result_m);
	temp_m = matrix(2, ray->dir);
	result_m = mxm(temp_m, inverse(t_matrix));
	ray->dir = result_m[0];
	free_m(temp_m, temp_m[0]->size);
	free(result_m);
}

// Frees the memory allocated for a ray.
void	free_ray(t_ray *ray)
{
	free_t(ray->ori);
	free_t(ray->dir);
	free(ray);
}
