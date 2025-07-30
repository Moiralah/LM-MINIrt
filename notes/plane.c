#include "minirt.h"

void	set_transform(t_obj *obj, t_tuple **transform)
{
	if (obj->type == 'S')
		((t_sphere *)obj->data)->t_matrix = transform;
	else if (obj->type == 'P')
		((t_plane *)obj->data)->t_matrix = transform;
	// else if (obj->type == 'C')
	// 	((t_cylinder *)obj->data)->t_matrix = transform;
	else if (obj->type == 'T')
		((t_test_shape *)obj->data)->t_matrix = transform;
}

t_tuple	*sphere_n(t_obj *obj, t_tuple *p)
{
	t_sphere	*sphere;
	t_tuple		*obj_n;

	sphere = (t_sphere *)obj->data;
	obj_n = sub(p, sphere->ori);
	return (norm(obj_n));
}

t_tuple	*normal_at(t_obj *obj, t_tuple *world_p)
{
	t_tuple	*obj_p;
	t_tuple	*obj_n;
	t_tuple	**transform_matrix;
	t_tuple	**world_normal_matrix;
	t_tuple	*world_normal;

	obj_p = world_to_obj_point(get_obj_tf(obj), world_p);
	if (obj->type == 'S')
		obj_n = sphere_n(obj, obj_p);
	else if (obj->type == 'P')
		obj_n = tuple(4, 0.0, 1.0, 0.0, 0.0);
//	else if (obj->type == 'C')
//		obj_n = cylinder_n(obj, obj_p);
	else if (obj->type == 'T')
		obj_n = tuple(4, obj_p->val[0], obj_p->val[1], obj_p->val[2], 0);
	transform_matrix = transpose(inverse(get_obj_tf(obj)));
	world_normal_matrix = mxm(transform_matrix, transpose(matrix(2, obj_n)));
	world_normal = (transpose(world_normal_matrix))[0];
	world_normal->val[3] = 0;
	free_m(transform_matrix, len_m(transform_matrix));
	free_m(world_normal_matrix, len_m(world_normal_matrix));
	free_t(obj_p);
	free_t(obj_n);
	return (norm(world_normal));
}

t_obj	*plane(t_tuple *color)
{
	t_plane	*p;
	t_obj	*obj;

	p = malloc(sizeof(t_plane));
	if (!p)
		return (NULL);
	p->t_matrix = identity(4);
	p->mat = material(color, tuple(4, 0.1, 0.9, 0.9, 200.0));
	obj = object(p, 'P');
	return (obj);
}

t_its	**plane_its(t_obj *obj, t_ray *ray)
{
	t_tuple	**inv;
	t_tuple	*origin;
	t_tuple	*dir;
	double	t;

	inv = inverse(get_obj_tf(obj));
	origin = transform_ori(inv, ray->ori);
	dir = transform_dir(inv, ray->dir);
	if (fabs(dir->val[1]) < __DBL_EPSILON__)
		return (NULL);
	t = -origin->val[1] / dir->val[1];
	return (its_s(1, its(obj, t)));
}

// t_obj *test_shape(void)
// {
// 	t_test_shape *ts = malloc(sizeof(t_test_shape));
// 	if (!ts)
// 		return NULL;

// 	ts->t_matrix = identity(4);
// 	ts->inverse = NULL;
// 	ts->transpose = NULL;
// 	ts->mat = material(tuple(3, 1, 1, 1), tuple(4, 0.1, 0.9, 0.9, 200.0));
// 	ts->saved_ray = NULL;

// 	t_obj *obj = malloc(sizeof(t_obj));
// 	if (!obj)
// 	{
// 		free(ts);
// 		return NULL;
// 	}
// 	obj->data = ts;
// 	obj->type = 'T';
// 	return obj;
// }

t_its	**test_its(t_obj *obj, t_ray *ray)
{
	t_test_shape	*ts;
	t_ray			*local_ray;

	ts = (t_test_shape *)obj->data;
	local_ray = copy_ray(ray);
	local_ray->ori = transform_ori(inverse(ts->t_matrix), ray->ori);
	local_ray->dir = transform_dir(inverse(ts->t_matrix), ray->dir);
	ts->saved_ray = local_ray;
	return (NULL);
}

// void test_intersect_transformed_shape(void)
// {
// 	t_obj *s;
// 	t_ray *r;

// 	s = test_shape();
// 	((t_test_shape *)s->data)->t_matrix = scale(4, 2.0, 2.0, 2.0, 0.0);
// 	r = ray(tuple(4, 0.0, 0.0, -5.0, 1.0), tuple(4, 0.0, 0.0, 1.0, 0.0));
// 	intersect(r, s);
// 	t_ray *saved = ((t_test_shape *)s->data)->saved_ray;
// 	print_t(saved->ori);
// 	print_t(saved->dir);
// }

// t_tuple *normal_at(t_obj *obj, t_tuple *world_point)
// {
// 	t_tuple *obj_p = world_to_obj_point(get_obj_tf(obj), world_point);
// 	t_tuple *obj_n;

// 	if (obj->type == 'S')
// 		obj_n = sphere_local_normal(obj, obj_p);
// 	else if (obj->type == 'P')
// 		obj_n = plane_local_normal(obj, obj_p);
// //	else if (obj->type == 'C')
// //		obj_n = cylinder_local_normal(obj, obj_p);
// 	else if (obj->type == 'T')
// 		obj_n = tuple(4, obj_p->val[0], obj_p->val[1], obj_p->val[2], 0);
// 	t_tuple *world_normal = (mxm(transpose(inverse(get_obj_tf(obj))), &obj_n));
// 	world_normal->val[3] = 0;
// 	return norm(world_normal);
// }
