#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <stdbool.h>
# include <stdbool.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_data
{
	char **data;
}	t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		h;
	int		w;
}	t_img;

typedef struct s_obj
{
	void	*data;
	char	type;
}	t_obj;

typedef struct s_tuple
{
	double			*val;
	int				size;
}	t_tuple;

typedef struct s_material
{
	t_tuple	*color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_mat;

typedef struct s_sphere
{
	t_tuple	**t_matrix;
	t_tuple	*ori;
	t_mat	*mat;
	double	rad;
}	t_sphere;

typedef struct s_its
{
	t_obj	*obj;
	double	*len;
	int		cnt;
}	t_its;

typedef struct s_ray
{
	t_tuple	*ori;
	t_tuple	*dir;
}	t_ray;

typedef struct s_light
{
	t_tuple	*position;
	t_tuple	*intensity;
}	t_light;

typedef struct s_world
{
	t_light	*light;
	t_obj	**object;
}	t_world;

typedef struct s_comps
{
	double	t;
	t_obj	*obj;
	t_tuple	*point;
	t_tuple	*eyev;
	bool	inside;
	t_tuple	*normalv;
}	t_comps;

typedef struct s_camera
{
	int		hsize;
	int		vsize;
	double	field_of_view;
	t_tuple	**transform;
	double	half_width;
	double	half_height;
	double	pixel_size;
}	t_camera;

t_img		*render(t_camera *cam, t_world *world);

t_its		**its_s(int size, ...);

t_its		**merge(t_its **ori, int size);

t_its		*its(t_obj *obj, double *len_from_ori, int cnt);

t_its		*hit(t_its **its_s);

t_its		*sphere_its(t_ray *r, t_sphere *sphere);

t_its		*intersect(t_ray *ray, t_obj *obj);

t_its		**intsect_world(t_world *world, t_ray *ray);

t_its		**add_its(t_its **intersections, t_its *obj_its, int *total_its);

t_its		**intsect_world(t_world *world, t_ray *ray);

t_ray		*ray(t_tuple *origin, t_tuple *direction);

t_ray		*ray_for_pixel(t_camera *cam, int px, int py);

t_ray		*copy_ray(t_ray *old);

t_tuple		*transform_ori(t_tuple **t_matrix, t_tuple *ori);

t_tuple		*transform_dir(t_tuple **t_matrix, t_tuple *dir);

t_tuple		**matrix(int size, ...);

t_tuple		**copy_m(t_tuple **old);

t_tuple		**subm(t_tuple **m, int row, int col);

t_tuple		**inverse(t_tuple **m);

t_tuple		**mxm(t_tuple **m1, t_tuple **m2);

t_tuple		**identity(int size);

t_tuple		**transpose(t_tuple **m);

t_tuple		**translate(int m_size, ...);

t_tuple		**scale(int m_size, ...);

t_tuple		**rotate(int m_size, int axis, double degree);

t_tuple		**shear(t_tuple **ori_matrix, int axis, ...);

t_tuple		**get_obj_tf(t_obj *obj);

t_tuple		*tuple(int size, ...);

t_tuple		*copy_t(t_tuple *old);

t_tuple		*travel(t_ray *ray, double time);

t_tuple		*cross(t_tuple *tuple1, t_tuple *tuple2);

t_tuple		*schur(t_tuple *tuple1, t_tuple *tuple2);

t_tuple		*norm(t_tuple *tuple);

t_tuple		*mult(t_tuple *tuple, double value);

t_tuple		*sub(t_tuple *tuple1, t_tuple *tuple2);

t_tuple		*add(t_tuple *tuple1, t_tuple *tuple2);

t_tuple		*world_to_obj_point(t_tuple **t_matrix, t_tuple *world_point);

t_tuple		*normal_at_obj(t_tuple **t_m, t_tuple *world_p, t_tuple *ori);

t_tuple		*reflect(t_tuple *in, t_tuple *normal);

t_tuple		*get_obj_ori(t_obj *obj);

t_tuple		**view_transform(t_tuple *from, t_tuple *to, t_tuple *up);

t_obj		*object(void *data, char type);

t_sphere	*sphere(t_tuple *origin, t_mat *mat, double radius);

t_light		*light(t_tuple *position, t_tuple *intensity);

t_light		*copy_light(t_light *old);

t_mat		*material(t_tuple *color, t_tuple *values);

t_mat		*get_obj_mat(t_obj *obj);

t_world		*def_world(void);

t_comps		*prepare_computations(t_its *intersection, t_ray *ray);

t_camera	*camera(double hsize, double vsize, double field_of_view);

double		det(t_tuple **m, int size);

double		mag(t_tuple *tuple);

double		dot(t_tuple *tuple1, t_tuple *tuple2);

double		spclr(t_tuple *r, t_tuple *eye, t_mat *mat, t_light *light);

int			rgb_hex(double red, double green, double blue);

int			len_m(t_tuple **m);

// int			equal_m(t_tuple **m1, t_tuple **m2);

t_tuple		*lighting(t_mat *mat, t_light *light, t_tuple **m);

void		mult_m(t_tuple **m, double val);

void		render_p(t_img *img, int x, int y, int color);

void		free_m(t_tuple **matrix, int stop);

void		free_t(t_tuple *tuple);

void		free_ray(t_ray *ray);

void		free_its(t_its *its);

void		free_its_s(t_its **its_s);

void		print_m(t_tuple **matrix);

void		print_t(t_tuple *tuple);

void		test_intersect_world(void);

int			shade_hit(t_world *world, t_comps *comps);

int			color_at(t_world *world, t_ray *ray);

void		free_comps(t_comps *comps);



#endif
