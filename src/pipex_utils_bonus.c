/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:00:45 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/15 03:17:35 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

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

//need test
//need fixing to just trim the needed
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

