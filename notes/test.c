#include "minirt.h"

/* void	cast_rays(t_img img, t_sphere *sphere, t_light *light, t_tuple *ori, int nohit)
{
	t_its	*its;
	t_ray	*r;
	t_tuple	*dir;
	t_tuple	*temp;
	t_tuple	*e;
	t_tuple	*n;
	t_tuple	*hit;
	t_tuple	*hit_colour;
	double	scaled_w;
	double	scaled_h;
	double	wall_size;
	double	wall_p[2];
	int		i[2];
	int	colour_hex;

	i[0] = img.w - 1;
	i[1] = img.h - 1;
	wall_size = 7.0 * RATIO;
	scaled_w = wall_size / img.w;
	scaled_h = wall_size / img.h;
	while (i[0] >= 0)
	{
		// Calculate wall point in world coordinates
		wall_p[0] = (wall_size / 2) - (scaled_w * i[0]);
		wall_p[1] = (wall_size / 2) - (scaled_h * i[1]);

		// Create direction vector from camera to wall point
		dir = tuple(4.0, wall_p[0], wall_p[1], 0.0, 1.0);
		temp = dir;
		dir = sub(dir, ori);
		free_t(temp);
		temp = dir;
		dir = norm(dir);
		free_t(temp);
		r = ray(tuple(4, 0.0, 0.0, -5.0, 1.0), dir);
		its = sphere_its(r, sphere);
		if (!its)
			return (free_ray(r));
		if ((!its->len) || (its->len[0] < 0))
			render_p(&img, i[0], i[1], nohit);
		else
		{
			hit = travel(r, its->len[0]);
			n = normal_at_obj(get_obj_tf(its->obj), hit, tuple(4.0, 0.0, 0.0, 0.0, 1.0));
			e = mult(r->dir, -1);
			hit_colour = lighting(get_obj_mat(its->obj), light, matrix(4, hit, e, n));
			//print_t(hit_colour);
			colour_hex = rgb_hex(hit_colour->val[0], hit_colour->val[1], hit_colour->val[2]);
			render_p(&img, i[0], i[1], colour_hex);
		}
		i[1]--;
		if ((i[1] < 0) && (i[0]--))
			i[1] = img.h - 1;
		free_ray(r);
		free_its(its);
	}
} */

// void	cast_rays(t_img *img, t_sphere *shape, t_light *l, t_tuple *ray_ori, double half, double pixel_size, double wall_z)
// {
// 	t_its	*xs;
// 	t_ray	*r;
// 	t_tuple	*colour;
// 	t_tuple	*normal;
// 	t_tuple	*pos;
// 	t_tuple	*hit;
// 	t_tuple	*eye;
// 	double	world_y;
// 	double	world_x;
// 	int	hex;
// 	int	y;
// 	int	x;

// 	y = -1;
// 	//colour = rgb_hex(red->val[0], red->val[1], red->val[2]);
// 	while (++y < img->w)
// 	{
// 		world_y = half - (pixel_size * y);
// 		x = -1;
// 		while (++x < img->h)
// 		{
// 			world_x = -half + (pixel_size * x);
// 			pos = tuple(4, world_x, world_y, wall_z, 1.0);
// 			r = ray(ray_ori, norm(sub(pos, ray_ori)));
// 			xs = sphere_its(r, shape);
// 			if (xs && xs->len)
// 			{
// 				hit = travel(r, xs->len[0]);
// 				normal = normal_at_obj(get_obj_tf(xs->obj), hit, get_obj_ori(xs->obj));
// 				eye = mult(r->dir, -1);
// 				colour = lighting(get_obj_mat(xs->obj), l, matrix(4, hit, eye, normal));
// 				hex = rgb_hex(colour->val[0], colour->val[1], colour->val[2]);
// 				render_p(img, x, y, hex);
// 			}
// 			else
// 				render_p(img, x, y, 0);
// 		}
// 	}
// }

// int	main(void)
// {
// 	t_img	img;
// 	t_sphere	*s;
// 	t_light	*l;
// 	t_mat	*m;
// 	t_tuple	*ray_ori;
// 	t_tuple	*red;
// 	void	*mlx;
// 	void	*win;
// 	double	pixel_size;
// 	double	wall_size;
// 	double	half;
// 	int	canvas_pixels;
// 	int	wall_z;

// 	ray_ori = tuple(4, 0.0, 0.0, -5.0, 1.0);
// 	wall_z = 10;
// 	wall_size = 7.0;
// 	canvas_pixels = 500;
// 	img.w = canvas_pixels;
// 	img.h = canvas_pixels;
// 	pixel_size = wall_size / canvas_pixels;
// 	half = wall_size / 2.0;
// 	red = tuple(3, 1.0, 0.2, 1.0);
// 	m = material(red, tuple(4, 0.1, 0.9, 0.9, 200.0));
// 	s = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), m, 1.0);
// 	s->t_matrix = mxm(rotate(4, 2, M_PI / 4.0), scale(4, 0.5, 1.0, 1.0));
// 	s->t_matrix = mxm(translate(4, 0.2, 0.5, 0.0), s->t_matrix);
// 	// s->t_matrix = shear(s->t_matrix, 0, 0.5, 0.5);
// 	l = light(tuple(4, -10.0, 10.0, -10.0, 1.0), tuple(3, 1.0, 1.0, 1.0));
// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, img.w, img.h, "Sphere");
// 	img.img = mlx_new_image(mlx, img.w, img.h);
// 	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
// 	cast_rays(&img, s, l, ray_ori, half, pixel_size, wall_z);
// 	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
// 	mlx_loop(mlx);
// 	mlx_destroy_display(mlx);
// 	free(mlx);
// 	return (0);
// }

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


	hsize = 1000;
	vsize = 500;
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

int	main(void)
{
	
	return (0);
}
