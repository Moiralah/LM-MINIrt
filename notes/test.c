#include "minirt.h"

int	rgbToHex(double red, double green, double blue)
{
	int	hex;

	hex = 0;
	hex += (red * 255);
	hex = (hex << 8) + (green * 255);
	hex = (hex << 8) + (blue * 255);
	return (hex);
}

void	renderPixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->len) + (x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	main(void)
{
	t_img	img;
	void	*mlx;
	void	*win;
	int	hex;
	int	i;
	int	q;

	hex = rgbToHex(1, -1.2, 0.3);
	printf("%d", hex);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "MiniRT");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	i = -1;
	while (++i <= 100)
	{
		renderPixel(&img, i, i, rgbToHex(i - 3.5, i - 10, i + 9.5));
		q = -1;
		while (++q <= i)
			renderPixel(&img, i, q, rgbToHex(i - 3.5, i - 10, i + 9.5));
		while (q <= 100)
			renderPixel(&img, i, q++, rgbToHex(i + 3.5, i + 10, i - 9.5));
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}
