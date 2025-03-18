/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:19:51 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/18 15:03:54 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void here_doc(char *limiter, t_dlist *list, char *temp_infile)
{
	int hdoc_fd[dlistsize(list)][2];
	int pid;
	int status;
	int fd;
	
	(void)limiter;
	(void)temp_infile;
	 set_pipes(list, hdoc_fd);
	pid = fork();
	if(pid == -1)
		exit_pipes(&list, hdoc_fd, dlistsize(list) -1 , 1);
	else if (pid == 0)
	{
		fd = open(temp_infile, O_RDWR | O_EXCL, 0644);
		read_stdin(hdoc_fd[0], limiter,fd);
		close (fd);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) != 0 && WEXITSTATUS(status) != 1)
			exit_pipes(&list, hdoc_fd, dlistsize(list) - 1 , 1);	
	}
}



// void check_rest(t_dlist **list, int argc, char **argv, char **envp)
// {
// 	int i;

// 	i = 3;
// 	if(list == NULL)
// 		exit_pipex(NULL, NULL);
// 	while (i < (argc - 1))
// 	{
// 		if(*list == NULL)
// 			*list = create_dlist(check_cmd_path(argv[i], envp));
// 		else
// 			*list = add_last_dlist(*list, create_dlist(check_cmd_path(argv[i], envp)));
// 		i++;
// 	}
// 	if (access(argv[argc - 1], F_OK) != 0)
// 		open(argv[argc - 1], O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// 	if (access(argv[argc - 1], W_OK) != 0)
// 		exit_pipex(list, NULL);
// }
void read_stdin(int *fd, char *limiter, int fd_infile)
{
	char *line;
	char *delimiter;
	char *lim;
	int len;
	// if(pipe(fd) == -1)
	// 	exit_pipex(NULL, NULL);
	// fd[1] = open("infile",  O_CREAT | O_TRUNC | O_WRONLY, 0644);
	close(fd[0]);
	// if(dup2(fd[1], infile) == -1)
	// 	exit_pipex(NULL, NULL);
	delimiter = ft_strdup(limiter);
	lim = ft_strjoin(delimiter, "\n");//leak
	if(lim == NULL)
		exit_program_leak(NULL, NULL, fd[0], fd[1]);	
	while(1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			free(delimiter);
			free(lim);
			close(fd[1]);
			return ;
		}
		if( ft_strlen(line) > ft_strlen(lim))
			len = ft_strlen(line);
		else
			len = ft_strlen(lim);
		if (ft_strncmp(line, lim, len) == 0)
		{
			free(lim);
			free(delimiter);
			free(line);
			close(fd[1]);
			return;
		}
		write(fd_infile ,line, ft_strlen(line) + 1);
		free(line);
	}
	free(delimiter);
	free(lim);
	close(fd[1]);
}
