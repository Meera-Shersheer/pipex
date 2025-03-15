/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:00:45 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/15 03:17:22 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlen_d(char **s)
{
	size_t	n;

	n = 0;
	if (s == NULL || *s == NULL)
		return (0);
	while (s[n] != NULL)
		n++;
	return (n);
}

char	*ft_strtrim_start(char const *s1, char const *set)
{
	int		t;
	char	*ptr;
	int		r;

	r = 0;
	t = ft_strlen(s1);
	while (s1[r] && ft_strchr(set, s1[r]))
		r++;
	ptr = malloc(t - r + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy((void *)ptr, &s1[r], t - r);
	if (!ptr)
		return (NULL);
	ptr[t - r] = '\0';
	return (ptr);
}

void	ft_free(char **matrix)
{
	size_t	row;

	row = 0;
	if (!matrix)
		return ;
	if (!(*matrix))
		return (free(matrix));
	while (row < ft_strlen_d(matrix))
	{
		free (matrix[row]);
		row++;
	}
	free (matrix);
}
