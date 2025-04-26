#include "minirt.h"

int	rgb_hex(double red, double green, double blue)
{
	int	hex;

	hex = 0;
	hex += (red * 255);
	hex = (hex << 8) + (green * 255);
	hex = (hex << 8) + (blue * 255);
	return (hex);
}

void	render_p(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->len) + (x * (img->bpp / 8));
	*(int *)pixel = color;
}
