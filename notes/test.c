/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:55 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 21:44:52 by huidris          ###   ########.fr       */
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
	t_tuple	*result;

	m = material(tuple(3, 1.0, 1.0, 1.0), tuple(4, 0.1, 0.9, 0.9, 200.0));
	l = light(tuple(4, 0.0, 0.0, -10.0, 1.0), tuple(3, 1.0, 1.0, 1.0));
	position = tuple(4, 0.0, 0.0, 0.0, 1.0);
	eyev = tuple(4, 0.0, 0.0, -1.0, 0.0);
	normalv = tuple(4, 0.0, 0.0, -1.0, 0.0);
	result = lighting(m, l, matrix(3, position, eyev, normalv), 0);
	print_t(result);
} */

/* int main(void)
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

	img.w = 1000;
	img.h = 500;

	// Create world
	world = malloc(sizeof(t_world));

	// Create light
	lit = light(tuple(4, -10.0, 10.0, -10.0, 1.0), tuple(3, 1.0, 1.0, 1.0));
	world->light = lit;

	// Create floor plane
	floor_mat = material(tuple(3, 1.0, 0.9, 0.9), tuple(4, 0.1, 0.9, 0.9, 200.0));
	floor_plane = plane(tuple(4, 0.0, 0.0, 0.0, 1.0), floor_mat);

	// Create sphere above the plane
	sphere_mat = material(tuple(3, 1.0, 0.2, 1.0), tuple(4, 0.1, 0.7, 0.3, 200.0));
	sphere_obj = sphere(tuple(4, 0.0, 1.0, 0.0, 1.0), sphere_mat, 1.0);
	apply_transform(sphere_obj, translate(4, -1.0, 0.0, 0.0));
	
	sphere_mat = material(tuple(3, 1.0, 0.0, 0.0), tuple(4, 0.1, 0.7, 0.3, 200.0));
	cy = cylinder(matrix(3, tuple(4, 0.0, 1.0, 0.0, 1.0), tuple(4, 0.0, 1.0 , 0.0)), sphere_mat, tuple(4, 0.5, 1.0, 1.0, -1.0), 1);

	// Add objects to world
	world->object = calloc(4, sizeof(t_obj *));
	world->object[0] = floor_plane;
	world->object[1] = cy;
	// world->object[2] = NULL;
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

	// Setup MLX
	mlx = mlx_init();
	win = mlx_new_window(mlx, img.w, img.h, "Plane Render");
	img.img = mlx_new_image(mlx, img.w, img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);

	// Render
	render(&img, cam, world);

	// Display
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);

	return 0;
} */

void	start_engine(t_world *w, t_camera *c, int hsize, int vsize)
{
	void		*mlx;
	void		*win;
	t_img		img;

	mlx = mlx_init();
	img.w = hsize;
	img.h = vsize;
	img.img = mlx_new_image(mlx, img.w, img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	win = mlx_new_window(mlx, img.w, img.h, "Render");
	render(&img, c, w);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}

t_camera	*set_up_cam(t_data *data, int hsize, int vsize)
{
	t_camera	*cam;
	t_tuple		**orient;
	t_tuple		*up;

	up = tuple(4, 0.0, 1.0, 0.0, 0.0);
	orient = matrix(3, data->c_ori, add(data->c_ori, data->c_dir), up);
	cam = camera(orient, data->c_fov, hsize, vsize);
	free_m(orient, 3);
	return (cam);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_world		*w;
	t_camera	*c;
	int			size[2];

	if (ac != 2)
		return (perr("Invalid input. < ./miniRT xxx.rt >"), -1);
	size[0] = 100;
	size[1] = 100;
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	validate_data(av[1], data);
	input_data(data);
	w = world(data);
	c = set_up_cam(data, size[0], size[1]);
	free_data(data);
	start_engine(w, c, size[0], size[1]);
	free_world(w);
	free(c->inverse_transform);
	free(c);
	return (0);
 }
