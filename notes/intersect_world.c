#include "minirt.h"

t_world	*def_world(void)
{
	t_world		*world;
	t_light		*lit;
	t_sphere	*s1;
	t_sphere	*s2;
	t_tuple		*origin;
	t_mat		*m;

	world = malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	lit = light(tuple(4, -10.0, 10.0, -10.0, 1.0), tuple(3, 1.0, 1.0, 1.0));
	world->light = calloc(2, sizeof(t_light *));
	world->light[0] = lit;
	world->light[1] = NULL;
	origin = tuple(4, 0.0, 0.0, 0.0, 1.0);
	m = material(tuple(3, 0.8, 1.0, 0.6), tuple(4, 0.1, 0.7, 0.2, 200.0));
	s1 = sphere(copy_t(origin), copy_mat(m), 1.0);
	//s1->t_matrix = translate(4, 0.5, 0.5, 0.0);
	m = material(tuple(3, 1.0, 0.2, 1.0), tuple(4, 0.1, 0.9, 0.9, 200.0));
	s2 = sphere(copy_t(origin),copy_mat(m), 0.5);
	// free_m(s2->t_matrix, len_m(s2->t_matrix));
	// s2->t_matrix = scale(4, 0.5, 0.5, 0.5);
	// s2->t_matrix = mxm(scale(4, 0.5, 0.5, 0.5), translate(4, 0.5, 0.0, 0.0));
	world->object = ft_calloc(3, sizeof(t_obj *));
	world->object[0] = object(s1, 'S');
	world->object[1] = object(s2, 'S');
	world->object[2] = NULL;
	free_mat(m);
	free_t(origin);
	return (world);
}

/* t_world	*def_world(void)
{
	t_world		*world;
	t_light		*lit;
	t_sphere	*right_wall;
	t_sphere	*left_wall;
	t_sphere	*middle;
	t_sphere	*right;
	t_sphere	*left;
	t_sphere	*floor;
	t_tuple		*origin;
	t_mat		*m;

	world = malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	lit = light(tuple(4, -10.0, 10.0, -10.0, 1.0), tuple(3, 1.0, 1.0, 1.0));
	world->light = calloc(2, sizeof(t_light *));
	world->light[0] = lit;
	world->light[1] = NULL;
	origin = tuple(4, 0.0, 0.0, 0.0, 1.0);
	m = material(tuple(3, 1.0, 0.9, 0.9), tuple(4, 0.1, 0.9, 0.0, 200.0));
	floor = sphere(copy_t(origin), copy_mat(m), 1.0);
	floor->t_matrix = scale(4, 10.0, 0.01, 10.0);
	left_wall = sphere(copy_t(origin),copy_mat(m), 1.0);
	left_wall->t_matrix = mxm(rotate(4, 0, M_PI / 2.0), scale(4, 10.0, 0.01, 10.0));
	left_wall->t_matrix = mxm(rotate(4, 1, -M_PI / 4.0), left_wall->t_matrix);
	left_wall->t_matrix = mxm(translate(4, 0.0, 0.0, 5.0), left_wall->t_matrix);
	right_wall = sphere(copy_t(origin),copy_mat(m), 1.0);
	right_wall->t_matrix = mxm(rotate(4, 0, M_PI / 2.0), scale(4, 10.0, 0.01, 10.0));
	right_wall->t_matrix = mxm(rotate(4, 1, M_PI / 4.0), right_wall->t_matrix);
	right_wall->t_matrix = mxm(translate(4, 0.0, 0.0, 5.0), right_wall->t_matrix);
	m = material(tuple(3, 0.5, 1.0, 0.5), tuple(4, 0.1, 0.7, 0.3, 200.0));
	middle = sphere(copy_t(origin), copy_mat(m), 1.0);
	middle->t_matrix = translate(4, -0.5, 1.0, 0.5);
	m = material(tuple(3, 0.5, 1.0, 0.1), tuple(4, 0.1, 0.7, 0.3, 200.0));
	right = sphere(copy_t(origin), copy_mat(m), 1.0);
	right->t_matrix = mxm(translate(4, 1.5, 0.5, -0.5), scale(4, 0.5, 0.5, 0.5));
	m = material(tuple(3, 1.0, 0.8, 0.1), tuple(4, 0.1, 0.7, 0.3, 200.0));
	left = sphere(copy_t(origin), copy_mat(m), 1.0);
	left->t_matrix = mxm(translate(4, -1.5, 0.33, -0.75), scale(4, 0.33, 0.33, 0.33));
	world->object = ft_calloc(7, sizeof(t_obj *));
	world->object[0] = object(floor, 'S');
	world->object[1] = object(left_wall, 'S');
	world->object[2] = object(right_wall, 'S');
	world->object[3] = object(middle, 'S');
	world->object[4] = object(right, 'S');
	world->object[5] = object(left, 'S');
	world->object[6] = NULL;
	free_mat(m);
	free_t(origin);
	return (world);
} */

/* t_world	*world(t_data *data)
{
	t_world		*w;
	t_cylinder	*c;
	t_sphere	*s;
	t_plane		*p;
	t_mat		*m;
	double		sh;
	double		sp;
	double		df;
	int		i;

	spclr = 0.9;
	diff = 0.9;
	w = malloc(sizeof(t_world));
	if (!w)
		return (NULL);
	w->light = light(data->l_ori, mult(l_color, l_ratio));
	w->object = malloc((data->obj_amt + 1) * sizeof(t_obj *));
	w->object[data->obj_amt] = NULL;
	i = -1;
	while (w->sp)
	{
		m = material(w->sp->color, tuple(4, data->a_ratio, sp, df, sh));
		s = sphere(w->sp->ori, m, w->sp->rad);
		w->object[++i] = s;
		w->sp = w->sp->next;
	}
	while (w->pl)
	{
		m = material(w->pl->color, tuple(4, data->a_ratio, sp, df, sh));
		p = plane(w->pl->ori, m, w->pl->rad);
		w->object[++i] = p;
		w->pl = w->pl->next;
	}
	while (w->cy)
	{
		m = material(w->cy->color, tuple(4, data->a_ratio, sp, df, sh));
		c = cylinder(w->cy->ori, m, w->cy->normalv, w->cy->rad, w->cy->height);
		w->object[++i] = c;
		w->cy = w->cy->next;
	}
	return (w);
} */

/* t_its	**add_its(t_its **intersections, t_its *obj_its, int *total_its)
{
	t_its	**temp;
	int		i;

	temp = ft_calloc(*total_its + 2, sizeof(t_its *));
	i = -1;
	while (++i < *total_its)
		temp[i] = intersections[i];
	temp[*total_its] = obj_its;
	temp[*total_its + 1] = NULL;
	free(intersections);
	(*total_its)++;
	return (temp);
}

t_its	**its_world(t_world *world, t_ray *ray)
{
	t_its	**intersections;
	t_its	*obj_its[2];
	int		total;
	int		i;
	int		j;

	intersections = ft_calloc(1, sizeof(t_its *));
	total = 0;
	i = -1;
	while (world->object[++i])
	{
		obj_its[0] = intersect(ray, world->object[i]);
		j = -1;
		while (++j < obj_its[0]->cnt)
		{
			obj_its[1] = its(obj_its[0]->obj, NULL, 1);
			obj_its[1]->len = malloc(sizeof(double));
			obj_its[1]->len[0] = obj_its[0]->len[j];
			intersections = add_its(intersections, obj_its[1], &total);
		}
	}
	intersections = merge(intersections, total);
	return (intersections);
} */

t_its	**merge_its_s(t_its **list1, t_its **list2)
{
	t_its	**merged;
	int	len1;
	int	len2;

	len1 = 0;
	len2 = 0;
	while (list1[len1])
		len1++;
	while (list2[len2])
		len2++;
	merged = calloc(len1 + len2 + 1, sizeof(t_its *));
	merged[len1 + len2] = NULL;
	while (--len2 >= 0)
		merged[len2 + len1] = list2[len2];
	while (--len1 >= 0)
		merged[len1] = list1[len1];
	free(list1);
	free(list2);
	return (merged);
}

t_its	**its_world(t_world *world, t_ray *ray)
{
	t_its	**merged_list;
	t_its	**its_list;
	int	i;

	i = -1;
	merged_list = NULL;
	while (world->object[++i])
	{
		its_list = intersect(ray, world->object[i]);
		if (!merged_list)
			merged_list = its_list;
		else if (its_list)
			merged_list = merge_its_s(merged_list, its_list);
	}
	if (!merged_list)
		return (NULL);
	i = 0;
	while(merged_list[i])
		i++;
	return (merge(merged_list, i));
}
/*
void	test_intersect_world(void)
{
	t_its	**xs;
	t_world	*world;
	t_ray	*r;
	int	cnt;
	int	i;

	world = def_world();
	r = ray(tuple(4, 0.0, 0.0, -5.0, 1.0), tuple(4, 0.0, 0.0, 1.0, 0.0));
	xs = its_world(world, r);
	cnt = 0;
	while (xs && xs[cnt])
		cnt++;
	printf("xs.count = %d\n", cnt);
	i = -1;
	while (++i < cnt)
		printf("xs[%d].t = %f\n", i, xs[i]->len);
	free_its_s(xs);
	free_ray(r);
}
*/
