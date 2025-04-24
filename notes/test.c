#include "minirt.h"

int	main(void)
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
	return (0);
}
