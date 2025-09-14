/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:48:22 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/14 14:52:37 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    cmd_init(t_cmd **cmd)
{
    *cmd = malloc(sizeof(t_cmd));
    if (!*cmd)
        return;
    (*cmd)->args = NULL;
    (*cmd)->redir_in_file = NULL;
    (*cmd)->redir_out_file = NULL;
    (*cmd)->append_file = NULL;
    (*cmd)->heredoc_limiter = NULL;
    (*cmd)->next = NULL;
}

char **args_to_array(t_cmd **cmd)
{
    t_list *temp;
    int len;
    int i;
    
    i = 0;  
    len = ft_lstsize((*cmd)->args);
    (*cmd)->args_array = malloc((len + 1) * sizeof(char *));
    if (!(*cmd)->args_array)
        return (NULL);
    temp = (*cmd)->args;
    if (!temp)
        return (NULL);
    while (temp)
    {
        printf("Adding to args_array: %s\n", (char *)temp->content);
        (*cmd)->args_array[i++] = ft_strdup(temp->content);  
        temp = temp->next;
    }
    (*cmd)->args_array[i] = NULL;  
    return ((*cmd)->args_array);
}

char	*find_path(t_list *args, t_data *data)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (data->envp[i])
    {
        if (!ft_strncmp(data->envp[i], "PATH=", 5))
			break ;
        i++;
    }
	if (!data->envp[i] || args == NULL)
		return (NULL);
	data->paths = ft_split(data->envp[i] + 5, ':');
	if (!data->paths)
		return (NULL);
    if (!args->content)
    {
        return (free_array(data->paths), NULL);
    }
	i = 0;
	while (data->paths[i])
	{
		data->path = ft_strjoin(data->paths[i], "/");
		cmd_path = ft_strjoin(data->path, args->content);
		free(data->path);
		if (!access(cmd_path, X_OK))
        {
            printf("Command found: %s\n", cmd_path);
            return (free_array(data->paths), cmd_path);
        }
		free(cmd_path);
		i++;
	}
	return (free_array(data->paths), NULL);
}



























/*
void    cmd_init(t_cmd **cmd)
{
    *cmd = malloc(sizeof(t_cmd));
    if (!*cmd)
        return;
    (*cmd)->args = NULL;
    (*cmd)->redir_in_file = NULL;
    (*cmd)->redir_out_file = NULL;
    (*cmd)->append_file = NULL;
    (*cmd)->heredoc_limiter = NULL;
    (*cmd)->next = NULL;
}

char **args_array(t_list *args)
{
    int len;
    char **args_array;
    t_list *temp;
    int i;

    len = ft_lstsize(args);
    args_array = malloc((len + 1) * sizeof(char *));
    if (!args_array)
        return (NULL);
    temp = args;
    i = 0;
    if (!args)
        return NULL;
    while (temp)
    {
        args_array[i++] = ft_strdup(temp->content);
        temp = temp->next;
    }
    args_array[i] = NULL;
    return (args_array);
}


char	*find_path(t_list *args, t_data *data)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (data->envp[i])
    {
        if (!ft_strncmp(data->envp[i], "PATH=", 5))
			break ;
        i++;
    }
	if (!data->envp[i] || args == NULL)
		return (NULL);
	data->paths = ft_split(data->envp[i] + 5, ':');
	if (!data->paths)
		return (NULL);
    if (!args->content)
    {
        return (free_array(data->paths), NULL);
    }
	i = 0;
	while (data->paths[i])
	{
		data->path = ft_strjoin(data->paths[i], "/");
		cmd_path = ft_strjoin(data->path, args->content);
		free(data->path);
		if (!access(cmd_path, X_OK))
        {
            printf("Command found: %s\n", cmd_path);
            return (free_array(data->paths), cmd_path);
        }

		free(cmd_path);
		i++;
	}
	return (free_array(data->paths), NULL);
}
*/



