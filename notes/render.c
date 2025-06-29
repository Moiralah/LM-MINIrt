#include "minirt.h"

// Converts RGB values (0.0 to 1.0) to a hexadecimal color representation.
int	rgb_hex(double red, double green, double blue)
{
	int	hex;

	hex = 0;
	hex += (red * 255);
	hex = (hex << 8) + (green * 255);
	hex = (hex << 8) + (blue * 255);
	return (hex);
}

// Renders a pixel at the specified (x, y) position with the given color.
void	render_p(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->len) + (x * (img->bpp / 8));
	*(int *)pixel = color;
}
