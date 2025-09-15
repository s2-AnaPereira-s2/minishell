/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:06:39 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/15 19:10:11 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *get_cmd_path(t_list *args, t_data *data)
{
    int i;
    char *cmd_path;

    i = 0;
	while (data->paths[i])
	{
		data->path = ft_strjoin(data->paths[i], "/");
		cmd_path = ft_strjoin(data->path, args->content);
		free(data->path);
		if (!access(cmd_path, X_OK))
        {
            return (cmd_path);
        }
		free(cmd_path);
		i++;
	}
    return (NULL);
}

char *checking_given_cmd_path(t_list *args)
{
    char *cmd_path;

    if (!access(args->content, X_OK))
    {
        cmd_path = ft_strdup(args->content);
        return (cmd_path);
    }
    else
        return (NULL);
}

int get_envp_index(t_data *data)
{
    int		i;
    
    i = 0;
	while (data->envp[i])
    {
        if (!ft_strncmp(data->envp[i], "PATH=", 5))
			break ;
        i++;
    }
    return (i);
}

char	*find_path(t_list *args, t_data *data)
{
	int		i;
	char	*cmd_path;

	i = get_envp_index(data);
	if (!data->envp[i] || args == NULL || !args->content)
		return (NULL);
	data->paths = ft_split(data->envp[i] + 5, ':');
	if (!data->paths)
		return (NULL);
    if (((char *)args->content)[0] == '/' || ((char *)args->content)[0] == '.')
    {
        cmd_path = checking_given_cmd_path(args);
        if (cmd_path)
        {
            return (free_array(data->paths), data->paths = NULL, cmd_path);
        }
	    return (free_array(data->paths), data->paths = NULL, NULL);
    }
    cmd_path = get_cmd_path(args, data);
    if (cmd_path)
    {
        return (free_array(data->paths), data->paths = NULL, cmd_path);
    }
	return (free_array(data->paths), data->paths = NULL, NULL);
}
