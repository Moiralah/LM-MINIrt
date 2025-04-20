#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct	s_tuple
{
	float	w;
	float	x;
	float	y;
	float	z;
	struct s_tuple	*next;
}	t_tuple;

#endif
