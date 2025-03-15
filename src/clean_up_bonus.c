/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:58:46 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/15 03:15:08 by mshershe         ###   ########.fr       */
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
void	exit_program_leak(char **ptr1, char **ptr2, int fd1, int fd2)
{
	if (ptr1 != NULL)
		ft_free(ptr1);
	if (ptr2 != NULL)
		ft_free(ptr2);
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd2 == -2)
		ft_printf("Error: command not found\n");
	else
		ft_printf("Error: program couldn't proceed\n");
	exit(1);
}