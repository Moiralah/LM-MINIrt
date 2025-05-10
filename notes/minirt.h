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

t_tuple	**matrix(int size, ...);

t_tuple	**subm(t_tuple **m, int row, int col);

t_tuple	**inverse(t_tuple **m);

t_tuple	**mxm(t_tuple **m1, t_tuple **m2);

t_tuple	*tuple(int size, ...);

t_tuple	**identity(int size);

t_tuple	**translate(int m_size, ...);

t_tuple	**scale(int m_size, ...);

t_tuple	**rotate(int m_size, int axis, double degree)

double	*cross(double *tuple1, double *tuple2, int size);

double	*schur(double *tuple1, double *tuple2, int size);

double	*norm(double *tuple, int size);

double	*mult(double *tuple, double value, int size);

double	*sub(double *tuple1, double *tuple2, int size);

double	*add(double *tuple1, double *tuple2, int size);

double	det(t_tuple **m, int size);

double	magnitude(double *tuple, int size);

double	dot(double *tuple1, double *tuple2, int size);

int		rgb_hex(double red, double green, double blue);

int		len_m(t_tuple **m);

int		equal_m(t_tuple **m1, t_tuple **m2);

void	transpose(t_tuple **m);

void	mult_m(t_tuple **m, double val);

void	render_p(t_img *img, int x, int y, int color);

void	free_m(t_tuple **matrix, int stop);

void	free_t(t_tuple *tuple);

void	print_m(t_tuple **matrix);

void	print_t(double *tuple, int size);

#endif
