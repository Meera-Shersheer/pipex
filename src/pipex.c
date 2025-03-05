/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:00:32 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/05 11:04:44 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(int argc, char **argv, char **envp)
{
	int alpha;
	int i;

	i = 0;
	alpha = -1;
	if (argc != 5)
		ft_printf("Error, the number of arguments is not correct\n");
	//check files	
	if (access(argv[1], F_OK | R_OK) != 0)
		perror("Error: ");

	//check commands

	//tokenizer();

// see relative path and absolute path
	if(ft_isalpha(argv[2][0]) == 0)
	{
			if(argv[2][0] == '/')
			{
				get_env_path(envp);
			}
			//absolute path
			if(argv[2][0] == '.')
			{}//relative path 1
			else
			{}//relative path 2
	}

// work through the envp and the split

	// if (access(argv[2], F_OK | X_OK) != 0 || access(argv[3], F_OK | X_OK) != 0 )
	// 	perror("Error: ");

	// create outfile if doesn't exist
	if (access(argv[4], F_OK) != 0)
		open(argv[4], O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 	
	return 0;
}


char	*get_env_path(char **envp)
{
	int i;
	int list;

	i = 0;
	list = ft_strlen_d(envp);
	while (i < list)
	{
		if(ft_strncmp( envp[i], "PATH" , 4) == 0 )
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	**get_directories(char *path_env)
{
	char **dir;
	char *path_var;

	path_var = ft_strtrim_start(path_env, "PATH=");
	
	dir = ft_split(path_var, ':');
	if (dir == NULL)
	{
		// exit
	}
	return (dir);
}
