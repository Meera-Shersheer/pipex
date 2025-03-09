/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:44:59 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/08 18:05:47 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char **check_cmd_path(char *cmd_arg, char **envp)
{
	char *path_env;
	char **cmd;
	
	cmd = split_command(cmd_arg);
	if(ft_isalpha(cmd[0][0]) == 0) //given an absoulute path or a relative path
	{
		if (access(cmd[0], F_OK | X_OK) != 0)
			perror("Error: ");
	}
	else // giving only the command name -> try different dirs to see if exists
	{
		path_env = get_env_path(envp);
		check_cmd_exist(cmd, path_env);
	}
	return (cmd);
}
char	**split_command(char *cmd_arg)
{
	char **cmd;

	handle_quotes(&cmd_arg);
	printf("string : %s\n", cmd_arg);
	cmd = ft_split(cmd_arg, ' ');
	return(cmd);
}

void	handle_quotes(char **cmd_arg)
{
	size_t i;
	int counter;

	i = 0;
	counter = 0;
	if(ft_strchr(*cmd_arg, '\'') == NULL)
		return ;
	else
	{
		while (i < ft_strlen(*cmd_arg))
		{
			if ((*cmd_arg)[i] == '\'')
				counter++;
			i++;
		}
		if (counter%2 != 0)
			return ;
		while (i < ft_strlen(*cmd_arg))
		{
			if ((*cmd_arg)[i] == '\'')
				(*cmd_arg)[i] = '\n';
			i++;
		}
	}
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

char *check_cmd_exist(char **cmd, char *path_env)
{
	char **dir;
	char *path;
	size_t i;

	dir = get_directories(path_env);
	//handle arguments without spaces 
	i = 0;
	while (i < ft_strlen_d(dir) )
	{
		path = ft_strjoin(dir[i], cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free(dir);
			return(path);
		}
			free(path);
		i++;
	}
	perror("Error: command not found ");
	ft_free(dir);
	return (NULL);
}
