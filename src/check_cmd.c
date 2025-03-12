/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:44:59 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/12 13:32:48 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char **check_cmd_path(char *cmd_arg, char **envp)
{
	char *path_env;
	char *temp;
	char **cmd;
	
	path_env = NULL;
	cmd = ft_split(cmd_arg, ' ');
	if(cmd == NULL)
		exit_program(NULL, NULL, -1, -1);
	if(ft_isalpha(cmd[0][0]) == 0) //given an absoulute path or a relative path
	{
		if (access(cmd[0], F_OK | X_OK) != 0)
			exit_program(cmd, NULL, -1, -1);
	}
	else // giving only the command name -> try different dirs to see if exists
	{
		path_env = get_env_path(envp);
		temp = check_cmd_exist(cmd, path_env);
		free(cmd[0]);
		cmd[0] = temp;
	}
	return (cmd);
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

	path_var = ft_strtrim_start(path_env, "PATH=");//leaks
	if(path_var == NULL)
		exit_program(NULL, NULL, -1, -1);
	dir = ft_split(path_var, ':');//leaks
	if(path_var)
		free(path_var);
	if (dir == NULL)
		exit_program(NULL, NULL, -1, -1);
	return (dir);
}

char	*check_cmd_exist(char **cmd, char *path_env)
{
	char **dir;
	char *path;
	char *temp;
	size_t i;

	dir = get_directories(path_env);//leaks
	i = 0;
	while (i < ft_strlen_d(dir))
	{
		temp = ft_strjoin(dir[i], "/");//leaks
		if(temp == NULL)
			exit_program(dir, NULL, -1, -1);
		path = ft_strjoin(temp, cmd[0]);//leaks
		if(temp)
			free(temp);
		if(path == NULL)
			exit_program(dir, NULL, -1, -1);
		if (access(path, F_OK | X_OK) == 0)
			return(ft_free(dir), path);
		free(path);
		i++;
	}
	ft_printf("Error: command not found\n");
	ft_free(dir);
	return (NULL);
}
