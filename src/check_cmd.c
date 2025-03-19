/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:44:59 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/19 21:44:21 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**check_cmd_path(char **cmd, char **envp)
{
	char		*path_env;
	char		*temp;

	path_env = NULL;
	if (cmd == NULL || *cmd == NULL)
		return (cmd);
	if (ft_strncmp(cmd[0], ".", 1) == 0 || ft_strncmp(cmd[0], "/", 1) == 0)
	{
		if (access(cmd[0], F_OK | X_OK) != 0)
			ft_printf("Error: %s: %s\n", cmd[0], strerror(errno));
	}
	else
	{
		path_env = get_env_path(envp);
		temp = check_cmd_exist(cmd, path_env);
		if (temp == NULL)
			return (NULL);
		free(cmd[0]);
		cmd[0] = temp;
	}
	return (cmd);
}

char	*get_env_path(char **envp)
{
	int	i;
	int	list;

	i = 0;
	list = ft_strlen_d(envp);
	while (i < list)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	**get_directories(char **cmd, char *path_env)
{
	char		**dir;
	char		*path_var;

	path_var = ft_strtrim_start(path_env, "PATH=");
	if (path_var == NULL)
		exit_program_leak(cmd, -1, -1);
	dir = ft_split(path_var, ':');
	if (path_var)
		free(path_var);
	if (dir == NULL)
		exit_program_leak(cmd, -1, -1);
	return (dir);
}

char	*check_cmd_exist(char **cmd, char *path_env)
{
	char		**dir;
	char		*path;
	char		*temp;
	size_t		i;

	dir = get_directories(cmd, path_env);
	if (dir == NULL)
		return (NULL);
	i = 0;
	while (dir[i])
	{
		temp = ft_strjoin(dir[i++], "/");
		if (temp == NULL)
			return(free_norm (dir, NULL));
		path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (path == NULL)
			return(free_norm (dir, NULL));
		if (access(path, F_OK | X_OK) == 0)
			return(free_norm (dir, path));
		free(path);
	}
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	return (NULL);
}

char	*free_norm(char **ptr, char *ret)
{
	if (ptr != NULL)
		ft_free(ptr);
	return (ret);
}
