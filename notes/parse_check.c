/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 01:41:09 by huidris           #+#    #+#             */
/*   Updated: 2025/07/31 01:41:10 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_freq(char **data, char *s, int *i)
{
	int	j;
	int	k;

	*i = 0;
	j = 0;
	k = 0;
	while (data[k])
	{
		if (ft_strncmp(data[k], s, ft_strlen(s)) == 0)
		{
			j++;
			*i = k;
		}
		k++;
	}
	return (j);
}

int	check_char(char *line, char *s)
{
	if (ft_strncmp(line, s, ft_strlen(s)) != 0)
		return (0);
	return (1);
}

void	check_name(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
		i++;
	if (av[i - 3] == '.')
		if (av[i - 2] == 'r')
			if (av[i - 1] == 't')
				return ;
	return (perr("Invalid file format. File need '.rt' format."), exit(1));
}

void	check_range(float min, float max, float value)
{
	if (value < min || value > max)
		return (perr("Value out of range: %f. Expected range: [%f, %f].",
				value, min, max), exit(1));
}

void	check_format(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (ft_strncmp(data[i], "A ", 2) != 0
			&& ft_strncmp(data[i], "C ", 2) != 0
			&& ft_strncmp(data[i], "L ", 2) != 0
			&& ft_strncmp(data[i], "sp ", 3) != 0
			&& ft_strncmp(data[i], "pl ", 3) != 0
			&& ft_strncmp(data[i], "cy ", 3) != 0)
			return (perr("Error: 'A', 'C', 'L', 'sp', 'pl', or 'cy' only."),
				exit(1));
		i++;
	}
}
