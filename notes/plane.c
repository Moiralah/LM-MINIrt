#include "minirt.h"

t_obj *test_shape(void)
{
	t_test_shape *ts = malloc(sizeof(t_test_shape));
	if (!ts)
		return NULL;

	ts->t_matrix = identity(4);
	ts->inverse = NULL;
	ts->transpose = NULL;
	ts->mat = material(tuple(3, 1, 1, 1), tuple(4, 0.1, 0.9, 0.9, 200.0));
	ts->saved_ray = NULL;

	t_obj *obj = malloc(sizeof(t_obj));
	if (!obj) {
		free(ts);
		return NULL;
	}

	obj->data = ts;
	obj->type = 'T';
	return obj;
}

t_its **test_its(t_obj *obj, t_ray *ray)
{
	t_test_shape *ts = (t_test_shape *)obj->data;
	t_ray *local_ray = copy_ray(ray);
	local_ray->ori = transform_ori(inverse(ts->t_matrix), ray->ori);
	local_ray->dir = transform_dir(inverse(ts->t_matrix), ray->dir);
	ts->saved_ray = local_ray;
	return NULL; // No real intersections
}

void test_intersect_transformed_shape(void)
{
	t_obj *s = test_shape();
	t_tuple **tf = scale(4, 2.0, 2.0, 2.0, 0.0);
	((t_test_shape *)s->data)->t_matrix = tf;
	t_ray *r = ray(tuple(4, 0, 0, -5, 1), tuple(4, 0, 0, 1, 0));

	intersect(r, s);
	t_ray *saved = ((t_test_shape *)s->data)->saved_ray;

	print_t(saved->ori); // Should be (0, 0, -2.5)
	print_t(saved->dir); // Should be (0, 0, 0.5)
}

t_tuple *sphere_local_normal(t_obj *obj, t_tuple *p)
{
	t_sphere *sphere = (t_sphere *)obj->data;
	t_tuple *local_normal = sub(p, sphere->ori);
	return norm(local_normal);
}

t_tuple *plane_local_normal(t_obj *obj, t_tuple *p)
{
	(void)obj;  // Unused parameter
	(void)p;    // Unused parameter
	return tuple(4, 0, 1, 0, 0);  // Always (0, 1, 0) for xz plane
}

t_tuple *local_normal_at(t_tuple *p)
{
	return (tuple(4, p[1], p[2], p[3], 0));
}

t_tuple *normal_at(t_obj *obj, t_tuple *world_point)
{
    t_tuple *local_point = world_to_obj_point(get_obj_tf(obj), world_point);
    t_tuple *local_normal;

    if (obj->type == 'S')
        local_normal = sphere_local_normal(obj, local_point);
    else if (obj->type == 'P')
        local_normal = plane_local_normal(obj, local_point);
    else if (obj->type == 'T')
        local_normal = tuple(4, local_point->val[0], local_point->val[1], local_point->val[2], 0);
    else
        return NULL;

    t_tuple **local_normal_matrix = matrix(2, local_normal);
    t_tuple **transform_matrix = transpose(inverse(get_obj_tf(obj)));
    t_tuple **world_normal_matrix = mxm(transform_matrix, transpose(local_normal_matrix));
    t_tuple *world_normal = (transpose(world_normal_matrix))[0];
    world_normal->val[3] = 0;

    // Free intermediate matrices
    free_m(local_normal_matrix, 2);
    free_m(transform_matrix, len_m(transform_matrix));
    free_m(world_normal_matrix, len_m(world_normal_matrix));
    free_t(local_point);
    free_t(local_normal);

    return norm(world_normal);
}

// t_tuple *normal_at(t_obj *obj, t_tuple *world_point)
// {
// 	t_tuple *local_point = world_to_obj_point(get_obj_tf(obj), world_point);
// 	t_tuple *local_normal;

// 	if (obj->type == 'S')
// 		local_normal = sphere_local_normal(obj, local_point);
// 	else if (obj->type == 'P')
// 		local_normal = plane_local_normal(obj, local_point);
// 	else if (obj->type == 'C')
// 		local_normal = cylinder_local_normal(obj, local_point);
// 	else if (obj->type == 'T')
// 		local_normal = tuple(4, local_point->val[0], local_point->val[1], local_point->val[2], 0);
// 	t_tuple *world_normal = (mxm(transpose(inverse(get_obj_tf(obj))), &local_normal));
// 	world_normal->val[3] = 0;
// 	return norm(world_normal);
// }

t_its **plane_its(t_obj *obj, t_ray *ray)
{
	t_tuple **inv = inverse(get_obj_tf(obj));
	t_tuple *origin = transform_ori(inv, ray->ori);
	t_tuple *dir = transform_dir(inv, ray->dir);
	if (fabs(dir->val[1]) < __DBL_EPSILON__)
		return NULL;
	double t = -origin->val[1] / dir->val[1];
	return its_s(1, its(obj, t));
}

t_obj *plane(void)
{
    t_plane *p = malloc(sizeof(t_plane));
    if (!p)
        return NULL;

    p->t_matrix = identity(4);
    p->mat = material(tuple(3, 1, 1, 1), tuple(4, 0.1, 0.9, 0.9, 200.0));

    t_obj *obj = malloc(sizeof(t_obj));
    if (!obj) {
        free(p);
        return NULL;
    }

    obj->data = p;
    obj->type = 'P';
    return obj;
}

int main()
{
	test_intersect_transformed_shape();
}
