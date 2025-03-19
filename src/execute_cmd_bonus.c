/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:00:34 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/19 10:55:17 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	set_fds(t_dlist *list, int (*fd)[2], char *infile, char *outfile)
{
	int	j;

	j = get_index(get_head(list), list);
	if (list->pre == NULL && list->add_trunc == 0)
		fd[j][0] = check_emptyfile(infile, list, fd, j);
	else if (list->pre == NULL && list->add_trunc == 'p')
		fd[j][0] = check_emptyfile_hdoc(infile, list, fd, j); 
	if (list->next == NULL)
	{
		if(list->add_trunc == 0)
			fd[j + 1][1] = open(outfile, O_WRONLY | O_TRUNC);
		else if (list->add_trunc == 'p')
			fd[j + 1][1] = open(outfile, O_WRONLY | O_APPEND);
		if (fd[j + 1][1] == -1)
			exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	}
	if (dup2(fd[j][0], STDIN_FILENO) == -1)
				exit_pipes(&list,fd, dlistsize(list) - 1 , 1);
	if (dup2(fd[j + 1][1], STDOUT_FILENO) == -1)
				exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
}

int	check_emptyfile(char *infile, t_dlist *list, int (*fd)[2], int j)
{
	char	buffer[1];

	fd[j][0] = open(infile, O_RDONLY);
	// if (fd[j][0] == -1)
	//exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	if (read(fd[j][0], buffer, 1) == 0)
	{
		close(fd[j][0]);
		fd[j][0] = open("/dev/null", O_RDONLY); 
		if (fd[j][0] == -1)
			exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	}
	else
	{
		close(fd[j][0]);
		fd[j][0] = open(infile, O_RDONLY);
		// if (fd[j][0] == -1)
		// 	exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	}
	return (fd[j][0]);
}

int	check_emptyfile_hdoc(char *infile, t_dlist *list, int (*fd)[2], int j)
{
	char	buffer[1];
	int	temp_fd;

	if (fd[j][0] < 0)
		fd[j][0] = open(infile, O_RDONLY);
	if (fd[j][0] == -1)
		exit_pipes(&list, fd, dlistsize(list) - 1, 1);
	temp_fd = dup(fd[j][0]);
	// if (temp_fd == -1)
	// 	exit_pipes(&list, fd, dlistsize(list) - 1, 1);
	if (read(temp_fd, buffer, 1) == 0)
	{
		close(temp_fd);
		close(fd[j][0]);
		fd[j][0] = open("/dev/null", O_RDONLY); 
		// if (fd[j][0] == -1)
		// 	exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	}
	else
		close(temp_fd);
	return (fd[j][0]);
}

void pipex_multi(t_dlist *list, char *infile, char *outfile)
{
	int	fd[dlistsize(list)][2];
	int	id;
	int	j;

	set_pipes(list, fd);
	while (list)
	{
		j = get_index(get_head(list), list);
		id = fork();
		if (id == -1)
			exit_pipes(&list, fd, dlistsize(list) - 1, 1);
		else if (id == 0)
			child_process(list, fd, infile, outfile);
		else
		{
			while (wait(NULL) > 0)
			{
			}
			close (fd[j][0]);
			if (j < dlistsize(list) - 1)
				close (fd[j + 1][1]);
			list = list->next;
		}
	}
}
void pipex_multi_hdoc(t_dlist *list, char *infile, char *outfile, int (*fd)[2])
{
	int id;
	int j;

	while (list)
	{
		j = get_index(get_head(list), list);
		id = fork();
		if (id == -1)
			exit_pipes(&list, fd, dlistsize(list) - 1, 1);
		else if (id == 0)
			child_process(list, fd, infile, outfile);
		else
		{
			while (wait(NULL) > 0)
			{
			}
			close (fd[j][0]);
			if (j < dlistsize(list) - 1)
				close (fd[j + 1][1]);
			list = list->next;
		}
	}
}
	
void set_pipes(t_dlist *list,  int (*fd)[2])
{
	int i;
	
	i = 0;
	while(i < dlistsize(list))
	{
		if(pipe(fd[i]) == -1)
			exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
		i++;
	}
}

void	child_process(t_dlist *list, int (*fd)[2], char *infile, char *outfile)
{
	//int j;
	
	//j = get_index(get_head(list), list);
	//close_unused(fd, dlistsize(list) - 1, j); // check cancling it
	set_fds(list, fd, infile, outfile);
	execve(list->cmd[0], list->cmd, NULL);
	exit_pipes(&list, fd, dlistsize(list) - 1, 1);
}

