#include "minirt.h"

void	sort(t_its **ori, t_its **l, t_its **r, int size)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while ((i + q) < size)
	{
		if (q >= ceil(size / 2))
			ori[i + q] = l[i];
		else if (i >= floor(size / 2))
			ori[q + i] = r[q];
		else if ((l[i]->len[0] < r[q]->len[0]) || (l[i]->len[1] < r[q]->len[1]))
			ori[i + q] = l[i];
		else
			ori[q + i] = r[q];
		if (q >= ceil(size / 2))
			i++;
		else if (i >= floor(size / 2))
			q++;
		else if ((l[i]->len[0] < r[q]->len[0]) || (l[i]->len[1] < r[q]->len[1]))
			i++;
		else
			q++;
	}
}

t_its	**merge(t_its **ori, int size)
{
	t_its	**left;
	t_its	**right;
	int		mid;

	mid = floor(size / 2);
	if (mid == 0)
		return (ori);
	left = calloc(mid, sizeof(t_its *));
	if (!left)
		return (NULL);
	while (--mid >= 0)
		left[mid] = ori[mid];
	mid = ceil(size / 2);
	right = calloc(mid, sizeof(t_its *));
	if (!right)
		return (NULL);
	while (++mid <= size)
		right[size - mid] = ori[((int)floor(mid / 2)) + size - mid];
	/* int	x;
	x = -1;
	while (left[++x])
		printf("L [%f]\n", left[x]->len[0]);
	x = -1;
	while (right[++x])
		printf("R [%f]\n", right[x]->len[0]);
	printf("Start merging\n"); */
	left = merge(left, floor(size / 2));
	right = merge(right, floor(size / 2));
	/* printf("Start sorting\n"); */
	sort(ori, left, right, size);
	free(left);
	free(right);
	/* int	q;
	q = -1;
	while (ori[++q])
		printf("%f\n", ori[q]->len[0]); */
	return (ori);
}
