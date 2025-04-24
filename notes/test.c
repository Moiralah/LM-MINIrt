#include "minirt.h"

void	render(void)
{
	t_img	img;
	void	*mlx;
	void	*win;
	int	i;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "MiniRT");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	i = -1;
	while (++i <= 100)
		renderPixel(&img, i, i, rgbToHex(i - 3.5, i - 10, i + 9.5));
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_display(mlx);
	free(mlx);
}

int	mEqual(t_tuple **m1, t_tuple **m2)
{
	int	width;
	int	height;
	int	i;

	height = 0;
	width = m1[0]->size;
	while (m1[height] && m2[height])
	{
		if ((m1[height]->size != width) || (m2[height]->size != width))
			return (0);
		height++;
	}
	if (m1[height] != m2[height])
		return (0);
	while (--height >= 0)
	{
		i = width - 1;
		while ((i >= 0) && (m1[height]->val[i] == m2[height]->val[i]))
			i--;
		if (i < 0)
			return (0);
	}
	return (1);
}

void	transpose(t_tuple **m)
{
	double	prev;
	int	i;
	int	q;

	i = -1;
	while (m[++i])
	{
		q = i;
		while (++q < m[i]->size)
		{
			prev = m[i]->val[q];
			m[i]->val[q] = m[q]->val[i];
			m[q]->val[i] = prev;
		}
	}
}

void	printMatrix(t_tuple **m)
{
	int	i;

	i = -1;
	while (m[++i])
		printVector(m[i]->val, m[i]->size);
}

t_tuple	**matrix(int size, ...)
{
	t_tuple	**matrix;
	int	i;

	i = -1;
	matrix = calloc(size, sizeof(t_tuple *));
	va_list	tuples;
	va_start(tuples, size);
	while (++i < (size - 1))
		matrix[i] = va_arg(tuples, t_tuple *);
	matrix[i] = NULL;
	return (matrix);
}

t_tuple	**multMatrix(t_tuple **m1, t_tuple **m2)
{
	t_tuple	**newMatrix;
	int	height;
	int	width;
	int	i;

	height = 0;
	while (m1[height])
		height++;
	width = m2[0]->size;
	newMatrix = matrix(height);
	if (!newMatrix)
		return (NULL);
	transpose(m2);
	while (--height >= 0)
	{
		newMatrix[height] = tuple(width);
		if (!newMatrix[height])
			return (NULL);
		i = -1;
		while (++i < width)
			newMatrix[height]->val[i] = dot(m1[height]->val, m2[i]->val, m1[0]->size);
	}
	return (newMatrix);
}

void	freeMatrix(t_tuple **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		free(matrix[i]->val);
		free(matrix[i]);
	}
	free(matrix);
}

int	main(void)
{
	t_tuple	**m1;
	t_tuple	**m2;
	t_tuple	**m3;
	t_tuple	*t1;
	t_tuple	*t2;
	t_tuple	*t3;
	t_tuple	*t4;
	t_tuple	*t5;
	t_tuple	*t6;
	t_tuple	*t7;
	t_tuple	*t8;

	t1 = tuple(4, 2.2, 5.2, 4.3, 9.8);
	t2 = tuple(4, 7.3, 0.1, 3.4, 2.7);
	t3 = tuple(4, 3.4, 6.4, 1.5, 6.5);
	t4 = tuple(4, 4.5, 9.2, 8.7, 5.9);
	m1 = matrix(5, t1, t2, t3, t4);
	t5 = tuple(4, 3.0, 0.0, -1.0, 5.0);
	t6 = tuple(4, 1.0, 2.0, 9.0, 4.0);
	t7 = tuple(4, 5.0, 4.0, 3.0, 3.0);
	t8 = tuple(4, 9.0, 3.0, 8.0, 6.0);
	m2 = matrix(5, t5, t6, t7, t8);
	if (mEqual(m1, m2))
		printf("M1 equals M2\n");
	else
		printf("M1 doesn't equals M2\n");
	/* printMatrix(m1);
	transpose(m1);
	printf("TRANSPOSE\n");
	printMatrix(m1); */
	m3 = multMatrix(m1, m2);
	printMatrix(m3);
	freeMatrix(m1);
	freeMatrix(m2);
	freeMatrix(m3);
	return (0);
}
