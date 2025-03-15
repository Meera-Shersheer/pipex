/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:29:05 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/15 16:26:12 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	gnl_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_strdup(char *str)
{
	int		i;
	char	*dup;

	i = 0;
	if (!str)
		return (NULL);
	dup = malloc(gnl_strlen(str) + 1);
	if (dup == NULL)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (!str1 || !str2)
		return (NULL);
	s = malloc(gnl_strlen(str1) + gnl_strlen(str2) + 1);
	if (!s)
		return (NULL);
	while (str1[i])
	{
		s[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		s[i + j] = str2[j];
		j++;
	}
	s[i + j] = '\0';
	free(str1);
	return (s);
}

char	*gnl_substr(char *str, int start, int size)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = gnl_strlen(str);
	if (!str)
		return (NULL);
	if (start > len)
		return (gnl_strdup(""));
	if (size > len)
		size = len;
	s = malloc(size + 1);
	if (!s)
		return (NULL);
	while (i < size)
	{
		s[i] = str[start];
		i++;
		start++;
	}
	s[i] = '\0';
	return (s);
}
