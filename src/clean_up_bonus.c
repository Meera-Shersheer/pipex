/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:58:46 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/15 01:27:39 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	exit_pipes(t_dlist **list, int (*fd)[2], int i, int j)
{
	int k;
	
	k = j;
	if (list != NULL)
		free_stack(list);
	while(i >= 0)
	{
		j = k;
		while(j >= 0)
		{
			close(fd[i][j]);
			j--;
		}
			i--;
	}
	perror("Error");
	exit(errno);
}
void close_unused(int (*fd)[2],int i, int j)
{
	while(i >= 0)
	{
		if (i != j)
			close(fd[i][0]);
		if (i != j + 1)
			close(fd[i][1]);
		i--;
	}
}
void	exit_pipex(t_dlist **list, char **ptr)
{
	if (list != NULL)
		free_stack(list);
	if (ptr != NULL)
		ft_free(ptr);
	perror("Error");
	exit(1);
}