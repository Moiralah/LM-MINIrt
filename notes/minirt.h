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

t_tuple	**submatrix(t_tuple **m, int row, int col);

t_tuple	**mult_m(t_tuple **m1, t_tuple **m2);

t_tuple	*tuple(int size, ...);

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

int		equal_m(t_tuple **m1, t_tuple **m2);

void	transpose(t_tuple **m);

void	render_p(t_img *img, int x, int y, int color);

void	free_m(t_tuple **matrix);

void	free_t(t_tuple *tuple);

void	print_m(t_tuple **matrix);

void	print_t(double *tuple, int size);

#endif
