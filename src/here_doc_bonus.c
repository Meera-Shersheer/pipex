/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:19:51 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/19 04:27:33 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void here_doc(char *limiter, t_dlist *list, char *outfile)
{
	int hdoc_fd[dlistsize(list)][2];

	set_pipes(list, hdoc_fd);
	read_stdin(hdoc_fd[0], limiter);
	list->add_trunc = 'p';
	pipex_multi_hdoc(list, NULL, outfile, hdoc_fd);
}



void check_rest(t_dlist **list, int argc, char **argv, char **envp)
{
	int i;

	i = 3;
	if(list == NULL)
		exit_pipex(NULL, NULL);
	while (i < (argc - 1))
	{
		if(*list == NULL)
			*list = create_dlist(check_cmd_path(argv[i], envp));
		else
			*list = add_last_dlist(*list, create_dlist(check_cmd_path(argv[i], envp)));
		i++;
	}
	if (access(argv[argc - 1], F_OK) != 0)
		open(argv[argc - 1], O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (access(argv[argc - 1], W_OK) != 0)
		ft_printf("Error: %s: %s\n", argv[argc - 1], strerror(errno));
}
void read_stdin(int *fd, char *limiter)
{
	char *line;
	char *delimiter;
	char *lim;
	int len;

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
			close(fd[1]);
			return (free(delimiter), free(lim));
		}
		if( ft_strlen(line) > ft_strlen(lim))
			len = ft_strlen(line);
		else
			len = ft_strlen(lim);
		if (ft_strncmp(line, lim, len) == 0)
		{
			close(fd[1]);
			return (free(delimiter), free(lim), free(line));
		}
		write(fd[1] ,line, ft_strlen(line));
		free(line);
	}
	return (free(delimiter), free(lim));
}
