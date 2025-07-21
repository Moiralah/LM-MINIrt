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
	double	scaled_w;
	double	scaled_h;
	double	wall_size;
	double	wall_p[2];
	int		i[2];
	int		hit_colour;

	i[0] = img.w - 1;
	i[1] = img.h - 1;
	wall_size = 7.0;
	scaled_w = wall_size / img.w;
	scaled_h = wall_size / img.h;
	while (i[0] >= 0)
	{
		wall_p[0] = (wall_size / 2) - (scaled_w * i[0]);
		wall_p[1] = (wall_size / 2) - (scaled_h * i[1]);
		dir = tuple(4.0, wall_p[0], wall_p[1], sphere->ori->val[2], 1.0);
		temp = dir;
		dir = sub(dir, ori);
		free_t(temp);
		temp = dir;
		dir = norm(dir);
		free_t(temp);
		r = ray(tuple(4.0, 0.0, 0.0, -5.0, 1.0), dir);
		e = mult(r->dir, -1);
		its = sphere_its(r, sphere);
		if (!its)
			return (free_ray(r));
		if ((!its->len) || (its->len[0] < 0))
			render_p(&img, i[0], i[1], nohit);
		else
		{
			hit = travel(r, its->len[0]);
			n = normal_at_obj(get_obj_tf(its->obj), hit, tuple(4.0, 0.0, 0.0, 0.0, 1.0));
			hit_colour = lighting(get_obj_mat(its->obj), light, matrix(4.0, hit, e, n));
			render_p(&img, i[0], i[1], hit_colour);
		}
		i[1]--;
		if ((i[1] < 0) && (i[0]--))
			i[1] = img.h;
		free_ray(r);
		free_its(its);
	}
} 

int	main(void)
{
	t_img		img;
	t_mat		*mat;
	t_sphere	*s;
	t_light		*l;
	t_tuple		*ori;
	void		*mlx;
	void		*win;
	int			black;
	int			blue;
	int			light_colour;

	img.w = 100;
	img.h = 100;
	ori = tuple(4.0, 0.0, 0.0, -5.0, 1.0);
	black = rgb_hex(0.0, 0.0, 0.0);
	blue = rgb_hex(1.0, 0.2, 1.0);
	light_colour = rgb_hex(1.0, 1.0, 1.0);
	l = light(tuple(4.0, -10.0, 10.0, -10.0, 1.0), light_colour);
	mat = material(blue, tuple(5, 1.0, 1.0, 1.0, 1.0));
	s = sphere(tuple(4.0, 0.0, 0.0, 10, 1.0), mat, 1.0);
	mlx = mlx_init();
	win = mlx_new_window(mlx, img.w, img.h, "Sphere");
	img.img = mlx_new_image(mlx, img.w, img.h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	cast_rays(img, s, l, ori, black);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
} */

/* int	main(void)
{
	t_sphere	*s1;
	t_sphere	*s2;
	t_ray		*r;
	t_its		*i;
	t_mat		*m;

	m = material(1, tuple(4, 0.1, 0.1, 0.1, 0.1));
	s1 = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), m, 1.0);
	s1->t_matrix = translate(4, 5.0, 0.0, 0.0);
	s2 = sphere(tuple(4, 0.0, 0.0, 0.0, 1.0), m, 1.0);
	s2->t_matrix = scale(4, 2.0, 2.0, 2.0);
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

int	main(void)
{
	t_tuple	*in;
	t_tuple	*normal;
	t_tuple	*r;

	in = tuple(4, 0.1, 0.2, 0.5, 0.0);
	normal = tuple(4, 0.2, 0.2, 0.4, 0.0);
	r = reflect(in, normal);
	print_t(r);
	return (0);
}
