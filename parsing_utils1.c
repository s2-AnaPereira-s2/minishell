/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:48:22 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/08 19:05:46 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    cmd_init(t_cmd **cmd)
{
    *cmd = malloc(sizeof(t_cmd));
    if (!*cmd)
        return;
    (*cmd)->args = NULL;
    (*cmd)->redir_in = NULL;
    (*cmd)->redir_out = NULL;
    (*cmd)->append = NULL;
    (*cmd)->heredoc = NULL;
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

void get_cmds_count(t_cmd **cmd, t_data *data)
{
   t_cmd *temp;

   temp = *cmd;
   data->cmds = 0;
   while (temp)
   {
       data->cmds += 1;
       temp = temp->next;
   }
}

void    get_pipes_pids(t_cmd **cmd, t_data *data)
{
    t_cmd *temp;
    
    temp = *cmd;
    data->pipefds = malloc(sizeof(int) * (2 * (data->cmds - 1)));
    if (!data->pipefds)
        return ;   
    process_pids(data, temp->args);
}

void    process_pids(t_data *data, t_list *args)
{
    int i;
    
    data->pids = malloc(sizeof(pid_t) * data->cmds);
    if (!data->pids)
        return ;
    i = 0;
    while(i < data->cmds)
    {
        data->pids[i] = fork();
        if (data->pids[i] < 0)
        {
            perror("Fork failed");
            return ;
        }
        if (data->pids[i] == 0)
        {
            execute_first(data, args);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    while(i-- > 0)
        waitpid(data->pids[i], NULL, 0);
}

