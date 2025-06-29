#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_tuple
{
	double			*val;
	int				size;
	struct s_tuple	*next;
}	t_tuple;

typedef struct s_ray
{
	t_tuple	*ori;
	t_tuple	*dir;
}	t_ray;

typedef struct s_sphere
{
	t_tuple	**t_matrix;
	t_tuple	*ori;
	double	rad;
}	t_sphere;

typedef union u_obj
{
	void	*data;
	char	type;
}	t_obj;

typedef struct s_its
{
	t_obj	*obj;
	double	*len;
	int		cnt;
}	t_its;

t_tuple		**matrix(int size, ...);

t_tuple		**subm(t_tuple **m, int row, int col);

t_tuple		**inverse(t_tuple **m);

t_tuple		**mxm(t_tuple **m1, t_tuple **m2);

t_tuple		**identity(int size);

t_tuple		**translate(int m_size, ...);

t_tuple		**scale(int m_size, ...);

t_tuple		**rotate(int m_size, int axis, double degree);

t_tuple		**shear(t_tuple **ori_matrix, int axis, ...);

t_tuple		*travel(t_ray *ray, double time);

t_its		**its_s(int size, ...);

t_its		**merge(t_its **ori, int size);

t_tuple		*tuple(int size, ...);

t_its		*its(t_obj *obj, double *len_from_ori, int cnt);

t_its		*hit(t_its **its_s);

t_its		*sphere_its(t_ray *r, t_sphere *sphere);

t_ray		*ray(t_tuple *origin, t_tuple *direction);

t_obj		*object(void *data, char type);

t_sphere	*sphere(t_tuple *origin, double radius);

double		*cross(double *tuple1, double *tuple2, int size);

double		*schur(double *tuple1, double *tuple2, int size);

double		*norm(double *tuple, int size);

double		*mult(double *tuple, double value, int size);

double		*sub(double *tuple1, double *tuple2, int size);

double		*add(double *tuple1, double *tuple2, int size);

double		det(t_tuple **m, int size);

double		mag(double *tuple, int size);

double		dot(double *tuple1, double *tuple2, int size);

int			rgb_hex(double red, double green, double blue);

int			len_m(t_tuple **m);

int			equal_m(t_tuple **m1, t_tuple **m2);

void		transpose(t_tuple **m);

void		transform(t_ray *ray, t_tuple **t_matrix);

void		mult_m(t_tuple **m, double val);

void		render_p(t_img *img, int x, int y, int color);

void		free_m(t_tuple **matrix, int stop);

void		free_t(t_tuple *tuple);

void		free_ray(t_ray *ray);

void		free_its(t_its *its);

void		free_its_s(t_its **its_s);

void		print_m(t_tuple **matrix);

void		print_t(double *tuple, int size);

#endif
