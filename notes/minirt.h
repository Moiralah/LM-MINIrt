#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int	bpp;
	int	len;
	int	endian;
}	t_img;

typedef struct	s_tuple
{
	double		*val;
	int		size;
	struct s_tuple	*next;
}	t_tuple;

t_tuple	*tuple(int size, ...);

double	*cross(double *vector1, double *vector2, int size);

double	*schur(double *vector1, double *vector2, int size);

double	*norm(double *vector, int size);

double	*mult(double *vector, double value, int size);

double	*sub(double *vector1, double *vector2, int size);

double	*add(double *vector1, double *vector2, int size);

double	magnitude(double *vector, int size);

double	dot(double *vector1, double *vector2, int size);

int		rgbToHex(double red, double green, double blue);

void		renderPixel(t_img *img, int x, int y, int color);

void		printVector(double *vector, int size);

#endif
