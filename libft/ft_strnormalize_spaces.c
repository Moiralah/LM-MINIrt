/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnormalize_spaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:30:55 by huidris           #+#    #+#             */
/*   Updated: 2025/08/03 21:32:16 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

static size_t	skip_leading_whitespace(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && is_whitespace(s[i]))
		i++;
	return (i);
}

static void	process_character(char c, char *result, size_t *j, int *in_space)
{
	if (is_whitespace(c))
	{
		if (!*in_space)
		{
			result[*j] = ' ';
			(*j)++;
			*in_space = 1;
		}
	}
	else
	{
		result[*j] = c;
		(*j)++;
		*in_space = 0;
	}
}

static void	remove_trailing_space(char *result, size_t *j)
{
	if (*j > 0 && result[*j - 1] == ' ')
		(*j)--;
}

// Normalizes multiple consecutive spaces to single spaces while
// preserving newlines
char	*ft_strnormalize_spaces(const char *s)
{
	size_t	i;
	size_t	j;
	char	*result;
	int		in_space;

	if (!s)
		return (NULL);
	result = (char *)malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	i = skip_leading_whitespace(s);
	j = 0;
	in_space = 0;
	while (s[i])
	{
		process_character(s[i], result, &j, &in_space);
		i++;
	}
	remove_trailing_space(result, &j);
	result[j] = '\0';
	return (result);
}
