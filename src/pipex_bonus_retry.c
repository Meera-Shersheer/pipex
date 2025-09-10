/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_retry.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 02:11:06 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/11 02:52:07 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
	int i;
	t_dlist *cmd_list;
	
	i = 2;
	cmd_list = NULL;
	if (argc < 5)
		wrong_n_arguments(argc);
	if (access(argv[1], F_OK | R_OK) != 0)
		ft_printf("Error: %s: %s\n", argv[1], strerror(errno));
	while (i < (argc - 1))
	{
		if(cmd_list == NULL)
			cmd_list = create_dlist(check_cmd_path(argv[i], envp));
		else
			cmd_list = add_last_dlist(cmd_list, create_dlist(check_cmd_path(argv[i], envp)));
		i++;
	}
	pipex_bonus(cmd_list, argv[1], argv[argc - 1]);
	if (cmd_list != NULL)
		free_stack(&cmd_list);
	return 0;
}


void pipex_bonus(t_dlist *list, char *infile, char *outfile)
{
	int fd[2];
	pid_t id;
	int prev_fd;

	prev_fd = -1;
	while (list != NULL)
	{
		if (list->next != NULL)
		{
			if (pipe(fd) == -1)
				exit(1);
		}
		id = fork();
		if (id == -1)
			exit(1);
		else if (id == 0)
			child_process_2(list, fd, infile, outfile, prev_fd);
		else
		{
			if (list->next != NULL)
				close(fd[1]);
			if (prev_fd != -1)
				close(prev_fd);
			if (list->next != NULL)
				prev_fd = fd[0];
		} 
		list = list->next;
	}
	if ( id > 0)
	{
		while(wait(NULL) > 0)
			;
	}		
}

void child_process_2(t_dlist *list, int fd[2], char *infile, char *outfile,int prev_fd)
{
	int open_fd;
	
	if (list->pre != NULL)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	
	}
	else
	{
		open_fd =  open(infile, O_RDONLY);
		dup2(open_fd, STDIN_FILENO);
		close(open_fd);
	}
	if (list->next != NULL)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
	{
		if(list->add_trunc == 0)
			open_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (list->add_trunc == 'p')
			open_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(open_fd, STDOUT_FILENO);
		close(open_fd);
	}
	if (list->next != NULL)
	    close(fd[1]);
	if (list->next != NULL)
	     close(fd[0]);
	execve(list->cmd[0], list->cmd, NULL);
}

void wrong_n_arguments(int n_arg)
{
	if(n_arg > 5)
		ft_printf("Error, too many arguments\n");
	else
		ft_printf("Error, the number of arguments is less than expected\n");
	exit(1);
}