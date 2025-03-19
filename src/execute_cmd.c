/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:00:34 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/19 21:44:56 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exceute_cmd_in(char **argv, char **envp, int *pipe_fd)
{
	int		fd;
	pid_t	id;
	char	**args;
	char	**cmd;

	args = NULL;
	id = fork();
	if (id == -1)
		exit_program(NULL, pipe_fd[0], pipe_fd[1]);
	else if (id == 0)
	{
		close(pipe_fd[0]);
		dupfd(pipe_fd[1], STDOUT_FILENO);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			error_norm(argv[1]);
		dupfd(fd, STDIN_FILENO);
		cmd = command_matrix(argv[2]);
		args = check_cmd_path(cmd, envp);
		if (!args)
			exit_program_wo_e(cmd, -1, -1);
		execve(args[0], cmd, NULL);
		exit_program(args, -1, -1);
	}
}

void	dupfd(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		exit_program(NULL, -1, oldfd);
	close(oldfd);
}

void	exceute_cmd_out(char **argv, char **envp, int *pipe_fd)
{
	int		fd;
	pid_t	id;
	char	**args;
	char	**cmd;

	args = NULL;
	id = fork();
	if (id == -1)
		exit_program(NULL, pipe_fd[0], pipe_fd[1]);
	else if (id == 0)
	{
		close(pipe_fd[1]);
		dupfd(pipe_fd[0], STDIN_FILENO);
		fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			error_norm(argv[4]);
		dupfd(fd, STDOUT_FILENO);
		cmd = command_matrix(argv[3]);
		args = check_cmd_path(cmd, envp);
		if (!args)
			exit(EXIT_FAILURE);
		execve(args[0], cmd, NULL);
		exit_program(args, -1, -1);
	}
}

void	pipex(char **argv, char **envp)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	exceute_cmd_in(argv, envp, pipefd);
	exceute_cmd_out(argv, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	while (wait(NULL) > 0)
		;
}
