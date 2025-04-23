#include "minirt.h"

void	renderPixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (x * img->len) + (y * (img->bpi / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	t_img	img;
	void	*mlx;
	// double	colour[3];

	/* colour[0] = 1;
	colour[1] = 4;
	colour[2] = 5; */
	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpi, &img.len, &img.endian);
	renderPixel(&img, 0, 0, 255);
	return (0);
}
