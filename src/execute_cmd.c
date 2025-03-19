/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:00:34 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/19 05:22:43 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exceute_cmd_in(char **args1, char **args2, char *infile, int *pipe_fd)
{
	int		fd;
	pid_t	id;

	close(pipe_fd[0]);
	fd = open(infile, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		return ;
	if ((dup2(pipe_fd[1], STDOUT_FILENO)) == -1)
		exit_program(args1, args2, fd, pipe_fd[1]);
	id = fork();
	if (id == -1)
		exit_program(args1, args2, fd, pipe_fd[1]);
	else if (id == 0)
		execve(args1[0], args1, NULL);
	close(pipe_fd[1]);
	close(fd);
}

void	exceute_cmd_out(char **args1, char **args2, char *outfile, int *pipe_fd)
{
	int		fd;
	pid_t	id;

	close(pipe_fd[1]);
	fd = open(outfile, O_WRONLY | O_TRUNC);
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_program_wo_e(args1, args2, fd, pipe_fd[0]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		exit_program(args1, args2, fd, pipe_fd[0]);
	id = fork();
	if (id == -1)
		exit_program(args1, args2, fd, pipe_fd[0]);
	else if (id == 0)
		execve(args1[0], args1, NULL);
	else
	{
		while (wait(NULL) > 0)
		{
		}
	}
	close(pipe_fd[0]);
	close(fd);
}

void	pipex(char **args1, char **args2, char *infile, char *outfile)
{
	int		pipefd[2];
	pid_t	id;

	if (pipe(pipefd) == -1)
		exit_program(args1, args2, -1, -1);
	id = fork();
	if (id == -1)
		exit_program(args1, args2, pipefd[0], pipefd[1]);
	else if (id == 0)
		exceute_cmd_in(args1, args2, infile, pipefd);
	else
	{
		while (wait(NULL) > 0)
		{
		}
		exceute_cmd_out(args2, args1, outfile, pipefd);
	}
}
