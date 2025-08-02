/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:55 by huidris           #+#    #+#             */
/*   Updated: 2025/08/02 17:22:20 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* int	main(void)
{
	t_sphere	*s1;
	t_sphere	*s2;
	t_ray		*r;
	t_its		*i;
	t_mat		*m;

	m = material(tuple(3, 1.0, 1.0, 1.0), tuple(4, 0.1, 0.1, 0.1, 0.1));
	s1 = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), m, 1.0);
	// s1->t_matrix = translate(4, 5.0, 0.0, 0.0);
	s2 = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), m, 1.0);
	s2->t_matrix = scale(4, 0.5, 0.5, 0.5);
	r = ray(tuple(4, 0.0, 0.0, -5.0, 1.0), tuple(4, 0.0, 0.0, 1.0, 0.0));
	i = sphere_its(r, s1);
	if (i && (i->len))
		printf("1: %f | %f\n", i->len[0], i->len[1]);
	i = sphere_its(r, s2);
	if (i && (i->len))
		printf("2: %f | %f\n", i->len[0], i->len[1]);
	return (0);
} */

/* int	main(int argc, char **argv)
{
	t_its	**list;
	t_its	**sorted;
	double	*len;
	int	neg;
	int	limit;
	int	amnt;
	int	sign;
	int	i;

	if (argc != 4)
		return (printf("Missing: AMNT | LIM | NEG\n"), -1);
	neg = argv[3][0] - '0';
	limit = argv[2][0] - '0';
	amnt = argv[1][0] - '0';
	printf("%d | %d | %d\n", amnt, limit, neg);
	list = malloc((amnt + 1) * sizeof(t_its *));
	list[amnt] = NULL;
	i = -1;
	while (++i < amnt)
	{
		printf("Creating %d... ", i);
		sign = 1;
		if (!(((rand() % limit) / neg) % 2))
			sign = -1;
		len = calloc(2, sizeof(double));
		len[0] = rand() % limit * sign;
		len[1] = rand() % limit * sign;
		list[i] = its(NULL, len, 2);
		printf("t1: %f | t2: %f\n", list[i]->len[0], list[i]->len[1]);
	}
	printf("List created\n");
	sorted = merge(list, amnt);
	i = -1;
	while (sorted[++i])
		printf("[%d] len: %f\n", i, sorted[i]->len[0]);
	return (0);
} */

/* int	main(void)
{
	t_mat	*m;
	t_light	*l;
	t_tuple	*position;
	t_tuple	*normalv;
	t_tuple	*eyev;
	double	result;

	m = material(tuple(3, 1.0, 1.0, 1.0), tuple(4, 0.1, 0.9, 0.9, 200.0));
	l = light(tuple(4, 0.0, 0.0, 10.0, 1.0), tuple(3, 1.0, 1.0, 1.0));
	position = tuple(4, 0.0, 0.0, 0.0, 1.0);
	eyev = tuple(4, 0.0, 0.0, -1.0, 0.0);
	normalv = tuple(4, 0.0, 0.0, -1.0, 0.0);
	result = lighting(m, l, matrix(4, position, eyev, normalv));
	printf("%f\n", result);
	printf("%d\n", rgb_hex(25.0, 25.0, 25.0));
} */

/* int	main(void)
{
	t_sphere	*s;
	t_mat		*m;
	t_tuple		*t1;

	m = material(tuple(3, 1.0, 1.0, 1.0), tuple(4, 0.5, 0.5, 0.5, 100.0));
	s = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), m, 1.0);
	s->t_matrix = mxm(scale(4, 1.0, 0.5, 1.0), rotate(4, 2, M_PI / 5));
	t1 = tuple(4, 0.0, sqrt(2) / 2.0, -sqrt(2) / 2.0, 1.0);
	print_t(normal_at_obj(s->t_matrix, t1, tuple(4, 0.0, 0.0, 0.0, 1.0)));
} */

/* int	main(void)
{
	t_world	*w;
	t_ray	*r;
	t_tuple	*colour;

	r = ray(tuple(4, 0.0, 0.0, 0.75, 1.0), tuple(4, 0.0, 0.0, -1.0, 0.0));
	w = def_world();
	colour = color_at(w, r);
	print_t(colour);
} */

/* int	main(void)
{
	t_world		*w;
	t_camera	*c;
	t_tuple	**vm;
	t_tuple	*from;
	t_tuple	*to;
	t_tuple	*up;
	void	*mlx;
	void	*win;
	t_img	img;
	int	vsize;
	int	hsize;


	hsize = 100;
	vsize = 100;
	img.w = hsize;
	img.h = vsize;
	from = tuple(4, 0.0, 1.5, -5.0, 1.0);
	to = tuple(4, 0.0, 1.0, 0.0, 1.0);
	up = tuple(4, 0.0, 1.0, 0.0, 0.0);
	vm = view_transform(from, to, up);
	c = camera(hsize, vsize, M_PI / 3.0);
	c->transform = vm;
	w = def_world();
	mlx = mlx_init();
	win = mlx_new_window(mlx, img.w, img.h, "Sphere");
	img.img = mlx_new_image(mlx, img.w, img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	render(&img, c, w);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
} */

/* int	main(void)
{
	// t_its		**its;
	// t_obj		*obj;
	t_cylinder	*c;
	t_tuple		*p;
	// t_ray		*r;

	c = cylinder(tuple(4, 0.0, 0.0, 0.0, 1.0), NULL, 1.0, 1.0);
	p = tuple(4, 0.0, 2.0, 0.5, 1.0);
	print_t(normal_at_cy(c, p));
	// r = ray(tuple(4, 0.0, -1.0, -2.0, 1.0), norm(tuple(4, 0.0, 1.0, 1.0, 0.0)));
	obj = object(c, 'C');
	its = calculate_its(obj, r);
	if (!its)
		printf("No Hits\n");
	else if (its[1])
		printf("%f | %f\n", its[0]->len, its[1]->len);
	else
		printf("%f\n", its[0]->len);
	return (0);
} */

/*
int main(void)
{
	t_img img;
	t_camera *cam;
	t_world *world;
	t_light *lit;
	t_obj *floor_plane;
	t_obj *sphere_obj;
	t_obj *cy;
	t_mat *floor_mat;
	t_mat *sphere_mat;
	void *mlx;
	void *win;

	// Setup MLX
	mlx = mlx_init();
	img.w = 1000;
	img.h = 500;
	win = mlx_new_window(mlx, img.w, img.h, "Plane Render");
	img.img = mlx_new_image(mlx, img.w, img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);

	// Create world
	world = malloc(sizeof(t_world));
	world->a_color = tuple(3, 0.2, 0.2, 0.2);
	world->a_ratio = 0.2;

	// Create light
	lit = light(tuple(4, -10.0, 10.0, -10.0, 1.0), tuple(3, 1.0, 1.0, 1.0));
	world->light = lit;

	// Create floor plane
	floor_mat = material(tuple(3, 1.0, 0.9, 0.9), tuple(4, 0.1, 0.9, 0.9, 200.0));
	floor_plane = plane(tuple(4, 0.0, 0.0, 0.0, 1.0), floor_mat);
	// ((t_plane *)(floor_plane->data))->t_matrix = rotate(4, 3, 0.0, 0.0, 10.0);
	// ((t_plane *)(floor_plane->data))->t_matrix = scale(4, 0.1, 0.1, 0.1);

	// Create sphere above the plane
	sphere_mat = material(tuple(3, 1.0, 0.2, 1.0), tuple(4, 0.1, 0.7, 0.3, 200.0));
	sphere_obj = sphere(tuple(4, 0.0, 1.0, 0.0, 1.0), sphere_mat, 1.0);
	sphere_mat = material(tuple(3, 1.0, 0.2, 1.0), tuple(4, 0.1, 0.7, 0.3, 200.0));
	cy = cylinder(tuple(4, 0.0, -1.0, 0.0, 1.0), tuple(4, 0.5, 1.0 , 0.7), copy_mat(sphere_mat), tuple(2, 2.0, 2.0));

	// Add objects to world
	world->object = calloc(4, sizeof(t_obj *));
	world->object[0] = floor_plane;
	world->object[1] = cy;
	world->object[2] = sphere_obj;
	world->object[3] = NULL;

	// Create camera
	cam = camera(img.w, img.h, M_PI / 3);
	cam->transform = view_transform(
	    tuple(4, 0.0, 1.5, -5.0, 1.0),  // from
	    tuple(4, 0.0, 1.0, 0.0, 1.0),   // to
	    tuple(4, 0.0, 1.0, 0.0, 0.0)    // up
	);
	cam->inverse_transform = inverse(cam->transform);

	// Render
	render(&img, cam, world);

	// Display
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);

	return 0;
}
*/

int	main(int ac, char **av)
{
	t_data		*data;
	t_world		*w;
	t_camera	*c;
	void		*mlx;
	void		*win;
	t_img		img;

	if (ac != 2)
		return (perr("Invalid input. < ./miniRT xxx.rt >"), -1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	validate_data(av[1], data);
	input_data(data);
	w = world(data);
	img.w = 300;
	img.h = 300;
	c = camera(img.w, img.h, data->c_fov);
	c->transform = view_transform(data->c_ori, add(data->c_ori, data->c_dir), tuple(4, 0.0, 1.0, 0.0, 0.0));
	c->inverse_transform = inverse(c->transform);
	mlx = mlx_init();
	win = mlx_new_window(mlx, img.w, img.h, "Render");
	img.img = mlx_new_image(mlx, img.w, img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	render(&img, c, w);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
