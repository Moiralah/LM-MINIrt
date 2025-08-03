#include "minirt.h"

void	free_cylinder(t_cylinder *cy)
{
	free_m(cy->inv_tf, len_m(cy->inv_tf));
	free_t(cy->ori);
	free_mat(cy->mat);
	free(cy);
}

void	free_sphere(t_sphere *sp)
{
	free_m(sp->inv_tf, len_m(sp->inv_tf));
	free_t(sp->ori);
	free_mat(sp->mat);
	free(sp);
}

void	free_plane(t_plane *pl)
{
	free_m(pl->inv_tf, len_m(pl->inv_tf));
	free_t(pl->ori);
	free_mat(pl->mat);
	free(pl);
}
