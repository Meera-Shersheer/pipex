/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:00:34 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/11 02:08:58 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	set_fds(t_dlist *list, int fd[2], char *infile, char *outfile)
{
	int	j;

	j = get_index(get_head(list), list);
	if (list->pre == NULL && list->add_trunc == 0)
	{
		close(fd[0]);
		fd[0] = check_emptyfile(infile, list, fd, j);
	}
	// else if (list->pre == NULL && list->add_trunc == 'p')
	// 	fd[j][0] = check_emptyfile_hdoc(infile, list, fd, j); 
	if (list->next == NULL)
	{
		if(list->add_trunc == 0)
		{
			close(fd[1]);
			fd[1] = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);	
		}
		else if (list->add_trunc == 'p')
		{
			close(fd[1]);
			fd[1] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}	// if (fd[j + 1][1] == -1)
		// 	exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
				exit_pipes(&list,fd, dlistsize(list) - 1 , 1);
	close(fd[0]);
	fd[0] = -1;
	if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	close(fd[1]);
	fd[1] = -1;
}

int	check_emptyfile(char *infile, t_dlist *list, int fd[2], int j)
{
	char	buffer[1];

	(void)j;
	fd[0] = open(infile, O_RDONLY);
	// if (fd[j][0] == -1)
	//exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	if (read(fd[0], buffer, 1) == 0)
	{
		close(fd[0]);
		fd[0] = open("/dev/null", O_RDONLY); 
		if (fd[0] == -1)
			exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	}
	else
	{
		close(fd[0]);
		fd[0] = open(infile, O_RDONLY);
		// if (fd[j][0] == -1)
		// 	exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	}
	return (fd[0]);
}

// int	check_emptyfile_hdoc(char *infile, t_dlist *list, int (*fd)[2], int j)
// {
// 	char	buffer[1];
// 	int	temp_fd;
// 	(void)infile;
// 	(void)list;
// 	// if (fd[j][0] < 0)
// 	// 	fd[j][0] = open(infile, O_RDONLY);
// 	// if (fd[j][0] == -1)
// 	// 	exit_pipes(&list, fd, dlistsize(list) - 1, 1);
// 	temp_fd = dup(fd[j][0]);
// 	// if (temp_fd == -1)
// 	// 	exit_pipes(&list, fd, dlistsize(list) - 1, 1);
// 	if (read(temp_fd, buffer, 1) == 0)
// 	{
// 		close(temp_fd);
// 		close(fd[j][0]);
// 		fd[j][0] = open("/dev/null", O_RDONLY); 
// 		// if (fd[j][0] == -1)
// 		// 	exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
// 	}
// 	else
// 		close(temp_fd);
// 	return (fd[j][0]);
// }

void pipex_multi(t_dlist *list, char *infile, char *outfile)
{
	int	fd[2];
	int prev_fd;
	int	id;

	prev_fd = -1;
	while (list->next != NULL)
	{
		if(pipe(fd) == -1)
			exit_pipes(&list, fd, dlistsize(list) - 2 , 1);
		id = fork();
		if (id == -1)
			exit_pipes(&list, fd, dlistsize(list) - 1, 1);
		else if (id == 0)
			child_process(list, fd, infile, outfile);
		else
		{
			while (wait(NULL) > 0)
			;
			close (fd[1]);
			if (prev_fd != -1)
				close (prev_fd);
			prev_fd = fd[0];
			list = list->next;
		}
	}
	id = fork();
	if (id == -1)
		exit_pipes(&list, fd, dlistsize(list) - 1, 1);
	else if (id == 0)
		child_process(list, fd, infile, outfile);
	else
	{
		while (wait(NULL) > 0)
		;
		close(fd[0]);
		close (fd[1]);
	}
}

void pipex_multi_hdoc(t_dlist *list, char *infile, char *outfile, int fd[2])
{
	int id;
	int j;
	// int status;
	
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
				;
			close (fd[0]);
			if (j < dlistsize(list) - 1)
				close (fd[1]);
			list = list->next;
		}
	}
}

void set_pipes(t_dlist *list,  int fd[2])
{
	int i;
	
	i = 0;
	fprintf(stderr, "size_list: %d\n", dlistsize(list));
	while(i < dlistsize(list) - 1)
	{
		if(pipe(fd) == -1)
			exit_pipes(&list, fd, dlistsize(list) - 2 , 1);
		i++;
	}
}

void	child_process(t_dlist *list, int (fd)[2], char *infile, char *outfile)
{
	//int j;
	
	//j = get_index(get_head(list), list);
	//close_unused(fd, dlistsize(list) - 2, j); // check cancling it
	set_fds(list, fd, infile, outfile);
	execve(list->cmd[0], list->cmd, NULL);
	//exit_pipes(&list, fd, dlistsize(list) - 1, 1);
}

