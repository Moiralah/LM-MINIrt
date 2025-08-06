/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:39:13 by huidris           #+#    #+#             */
/*   Updated: 2025/08/07 02:02:10 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIDTH	500
# define HEIGHT	500
# define EPSILON	0.00001
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_tuple
{
	double	*val;
	int		size;
}	t_tuple;

typedef struct s_sp
{
	t_tuple		*color;
	t_tuple		*ori;
	double		rad;
	struct s_sp	*next;
}	t_sp;

typedef struct s_pl
{
	t_tuple		*ori;
	t_tuple		*normalv;
	t_tuple		*color;
	struct s_pl	*next;
}	t_pl;

typedef struct s_cy
{
	t_tuple		*color;
	t_tuple		*ori;
	t_tuple		*n;
	double		rad;
	double		h;
	struct s_cy	*next;
}	t_cy;

typedef struct s_data
{
	t_cy	*cy;
	t_sp	*sp;
	t_pl	*pl;
	t_tuple	*a_color;
	t_tuple	*l_color;
	t_tuple	*l_pos;
	t_tuple	*c_ori;
	t_tuple	*c_dir;
	char	**data;
	double	a_ratio;
	double	l_ratio;
	double	c_fov;
	int		obj_amt;
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

typedef struct s_material
{
	t_tuple	*color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_mat;

typedef struct s_camera
{
	t_tuple	**inverse_transform;
	double	half_width;
	double	half_height;
	double	pixel_size;
	double	fov;
	int		hsize;
	int		vsize;
}	t_camera;

typedef struct s_cylinder
{
	t_tuple	**inv_tf;
	t_tuple	*ori;
	t_mat	*mat;
	double	rad;
	double	max;
	double	min;
	double	h;
	int		closed;
}	t_cylinder;

typedef struct s_sphere
{
	t_tuple	**inv_tf;
	t_tuple	*ori;
	t_mat	*mat;
	double	rad;
}	t_sphere;

typedef struct s_plane
{
	t_tuple	**inv_tf;
	t_tuple	*ori;
	t_mat	*mat;
}	t_plane;

typedef struct s_its
{
	t_obj	*obj;
	double	len;
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
	t_obj		**obj;
	t_light		*light;
	t_tuple		*a_color;
	double		a_ratio;
	t_camera	*c;
}	t_world;

typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
}	t_mlx_data;

typedef struct s_comps
{
	t_obj	*obj;
	t_tuple	*over_point;
	t_tuple	*normalv;
	t_tuple	*point;
	t_tuple	*eyev;
	double	t;
	bool	inside;
}	t_comps;

t_its		**its_s(int size, ...);

t_its		**merge(t_its **ori, int size);

t_its		**merge_its_s(t_its **list1, t_its **list2);

t_its		**calculate_its(t_obj *obj, t_ray *r);

t_its		*its(t_obj *obj, double len_from_ori);

t_its		*hit(t_its **its_s);

t_its		**its_world(t_world *world, t_ray *ray);

t_ray		*ray(t_tuple *origin, t_tuple *direction);

t_ray		*ray_for_pixel(t_camera *cam, int px, int py);

t_ray		*copy_ray(t_ray *old);

t_tuple		**matrix(int size, ...);

t_tuple		**copy_m(t_tuple **old);

t_tuple		**subm(t_tuple **m, int row, int col);

t_tuple		**inverse(t_tuple **m);

t_tuple		**mxm(t_tuple **m1, t_tuple **m2);

t_tuple		**identity(int size);

t_tuple		**transpose(t_tuple **m);

t_tuple		**translate(int m_size, ...);

t_tuple		**scale(int m_size, ...);

t_tuple		**rotate_axis(int m_size, int axis, double degree);

t_tuple		**rotate(int m_size, int axis_amnt, ...);

t_tuple		**get_inv_tf(t_obj *obj);

t_tuple		**view_transform(t_tuple *from, t_tuple *to, t_tuple *up);

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

t_tuple		*cylinder_n(t_obj *obj, t_tuple *point);

t_tuple		*sphere_n(t_obj *ob, t_tuple *p);

t_tuple		*reflect(t_tuple *in, t_tuple *normal);

t_tuple		*shade_hit(t_world *world, t_comps *comps);

t_tuple		*transform_ori(t_tuple **t_matrix, t_tuple *ori);

t_tuple		*transform_dir(t_tuple **t_matrix, t_tuple *dir);

t_tuple		*color_at(t_world *world, t_ray *ray);

t_tuple		*lighting(t_mat *mat, t_light *light, t_tuple **m, int shadowed);

t_obj		*object(void *data, char type);

t_obj		*sphere(t_tuple *origin, t_mat *mat, double radius);

t_obj		*cylinder(t_tuple **val_m, t_mat *mat, t_tuple *dim, int closed);

t_light		*light(t_tuple *position, t_tuple *intensity);

t_mat		*material(t_tuple *color, t_tuple *values);

t_mat		*copy_mat(t_mat *old);

t_mat		*get_obj_mat(t_obj *obj);

t_world		*world(t_data *data);

t_comps		*prepare_computations(t_its *intersection, t_ray *ray);

t_camera	*camera(t_tuple **tm, double fov, int hsize, int vsize);

double		det(t_tuple **m, int size);

double		mag(t_tuple *tuple);

double		dot(t_tuple *tuple1, t_tuple *tuple2);

int			shadowed(t_world *w, t_tuple *point);

int			rgb_hex(double red, double green, double blue);

int			len_m(t_tuple **m);

void		render(t_img *canvas, t_camera *cam, t_world *world);

void		mult_m(t_tuple **m, double val);

void		clamp(t_tuple *tuple, double min, double max);

void		render_p(t_img *img, int x, int y, int color);

void		free_cylinder(t_cylinder *sp);

void		free_sphere(t_sphere *sp);

void		free_plane(t_plane *pl);

void		free_world(t_world *world);

void		free_data(t_data *data);

void		free_obj(t_obj *obj);

void		free_light(t_light *light);

void		free_m(t_tuple **matrix, int stop);

void		free_mat(t_mat *material);

void		free_t(t_tuple *tuple);

void		free_ray(t_ray *ray);

void		free_its_s(t_its **its_s);

void		print_m(t_tuple **matrix);

void		print_t(t_tuple *tuple);

void		free_comps(t_comps *comps);

float		ft_atof(const char *str);

void		remove_commas(char *str);

void		check_name(char *av);

int			check_char(char *line, char *s);

void		content(char *file, t_data *data);

void		check_range(float min, float max, float value);

int			check_freq(char **data, char *s, int *i);

void		obj_amount(t_data *data);

void		check_ambient(t_data *data);

void		check_camera(t_data *data);

void		check_light(t_data *data);

void		check_sphere(t_data *data);

void		check_plane(t_data *data);

void		check_cylinder(t_data *data);

void		check_format(char **data);

void		validate_data(char *file, t_data *data);

void		set_ambient(char *line, t_data *data);

void		set_camera(char *line, t_data *data);

void		set_light(char *line, t_data *data);

void		set_sphere(char *line, t_data *data);

void		set_plane(char *line, t_data *data);

void		set_cylinder(char *line, t_data *data);

void		obj_amount(t_data *data);

t_data		*input_data(char *av);

void		apply_tf(t_obj *obj, t_tuple **transform);

t_tuple		*normal_at(t_obj *obj, t_tuple *world_p);

t_obj		*plane(t_tuple *origin, t_tuple *normal, t_mat *mat);

t_its		**cylinder_its(t_obj *obj, t_cylinder *cy, t_ray *r);

t_its		**sphere_its(t_obj *obj, t_sphere *sp, t_ray *r);

t_its		**plane_its(t_obj *obj, t_ray *ray);

void		set_obj(t_world *world, t_data *data);

t_ray		*create_ray(t_tuple **inv_m, double world_x, double world_y);

#endif
