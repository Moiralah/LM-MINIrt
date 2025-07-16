#include "minirt.h"

// Creates a ray with an origin and direction.
t_ray *ray(t_tuple *origin, t_tuple *direction)
{
	t_ray *new_ray;

	new_ray = calloc(1, sizeof(t_ray));
	if (!new_ray)
		return (NULL);
	new_ray->ori = origin;
	new_ray->dir = direction;
	return (new_ray);
}

// Calculates the position of a ray at a given time.
t_tuple *travel(t_ray *ray, double time)
{
	t_tuple *velo;
	t_tuple *new_pos;

	velo = mult(ray->dir, time);
	new_pos = add(ray->ori, velo);
	free_t(velo);
	return (new_pos);
}

// Computes the intersections of a ray with a sphere.
t_its *sphere_its(t_ray *r, t_sphere *sphere)
{
	t_obj *obj;
	t_tuple *rto;
	double *result;
	double rtc;
	double h;

	obj = object(sphere, 'S');
	if (!obj)
		return (NULL);
	transform(r, sphere->t_matrix);
	rto = sub(sphere->ori, r->ori);
	rtc = dot(rto, r->dir);
	h = pow(mag(rto), 2) - pow(rtc, 2);
	if (sqrt(h) > sphere->rad)
		return (free_t(rto), its(obj, NULL, 0));
	h = pow(mag(rto), 2) - pow(rtc, 2);
	result = calloc(2, sizeof(double));
	if (!result)
		return (free_t(rto), free(obj), NULL);
	h = sqrt(pow(sphere->rad, 2) - h);
	result[0] = rtc - h;
	result[1] = rtc + h;
	if (result[0] == result[1])
		return (free_t(rto), its(obj, result, 1));
	return (free_t(rto), its(obj, result, 2));
}

t_its *intersect(t_ray *ray, t_obj *obj)
{
	if (obj->type == 'S')
		return (sphere_its(ray, (t_sphere *)obj->data));
	return (NULL);
}

void transform(t_ray *ray, t_tuple **t_matrix)
{
	t_tuple **temp_m;
	t_tuple **inverse_m;
	t_tuple **result_m;

	temp_m = matrix(2, ray->ori);
	if (!temp_m)
		return;
	inverse_m = inverse(t_matrix);
	if (!inverse_m)
		return (free_m(temp_m, temp_m[0]->size));
	result_m = mxm(temp_m, inverse_m);
	ray->ori = result_m[0];
	free_m(temp_m, temp_m[0]->size);
	free(result_m);
	temp_m = matrix(2, ray->dir);
	if (!temp_m)
		return (free_m(inverse_m, inverse_m[0]->size));
	result_m = mxm(temp_m, inverse_m);
	ray->dir = result_m[0];
	free_m(temp_m, temp_m[0]->size);
	free_m(inverse_m, inverse_m[0]->size);
	free(result_m);
}

// Frees the memory allocated for a ray.
void free_ray(t_ray *ray)
{
	free_t(ray->ori);
	free_t(ray->dir);
	free(ray);
}

// ignore --------------------------------------------
t_ray *ray_transform(t_ray *r, t_tuple **matrix)
{
	t_tuple **result;
	t_ray *new_ray = calloc(1, sizeof(t_ray));
	if (!new_ray)
		return NULL;

	result = mxm(matrix, &r->ori);
	if (!result)
		return (free(new_ray), NULL);
	new_ray->ori = *result;
	free_m(result, result[0]->size);

	t_tuple *temp_dir = tuple(4, r->dir->val[0], r->dir->val[1], r->dir->val[2], 0);
	result = mxm(matrix, &temp_dir);
	if (!result)
		return (free(new_ray), NULL);
	new_ray->dir = *result;
	free_m(result, result[0]->size);
	free_t(temp_dir);

	new_ray->dir = norm(new_ray->dir);

	return new_ray;
}

t_its *sphere_intersect(t_ray *ray, t_sphere *sphere)
{
	t_tuple **inv_matrix = inverse(sphere->t_matrix);
	if (!inv_matrix)
		return NULL;

	t_ray *local_ray = ray_transform(ray, inv_matrix);
	free_m(inv_matrix, inv_matrix[0]->size); // Free after transforming

	t_tuple *center = tuple(4.0, 0.0, 0.0, 0.0, 1.0);
	t_tuple *sphere_to_ray = sub(local_ray->ori, center);

	double a = dot(local_ray->dir, local_ray->dir);
	double b = 2 * dot(local_ray->dir, sphere_to_ray);
	double c = dot(sphere_to_ray, sphere_to_ray) - sphere->rad * sphere->rad;
	double discriminant = b * b - 4 * a * c;

	free_t(center);
	free_t(sphere_to_ray);
	free_ray(local_ray);

	if (discriminant < 0)
		return NULL;

	double sqrt_d = sqrt(discriminant);
	double t1 = (-b - sqrt_d) / (2 * a);
	double t2 = (-b + sqrt_d) / (2 * a);

	double *ts = calloc(2, sizeof(double));
	ts[0] = t1;
	ts[1] = t2;

	t_obj *obj = object(sphere, 'S');
	return its(obj, ts, 2);
}

t_its *intersect_s(t_ray *ray, t_obj *obj)
{
	if (obj->type == 'S')
		return (sphere_intersect(ray, (t_sphere *)obj->data));
	return (NULL);
}
