/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:44:12 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/12 19:06:36 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	execute_one_cmd(t_cmd **cmd, t_data *data)
{
	execve(data->cmd_paths[0], (*cmd)->args_array, data->envp);
}

void    execute_basic_cmds(t_cmd **cmd, t_data *data, int cmd_index)
{
    int i;
    t_cmd *current_cmd;

    current_cmd = *cmd;
    i = 0;
    while (i < cmd_index && current_cmd)
    {
        current_cmd = current_cmd->next;
        i++;
    }
    if (cmd_index == 0)
    {
        dup2(data->pipefds[1], 1);
    }
    else if (cmd_index == data->cmds - 1)
    {
        dup2(data->pipefds[2 * (cmd_index - 1)], 0);
    }
    else
    {
        dup2(data->pipefds[2 * (cmd_index - 1)], 0);
        dup2(data->pipefds[2 * (cmd_index + 1)], 1);
    }
    i = 0;
    while (i < cmd_index * 2)
    {
        close(data->pipefds[i]);
        i++;
    }
    execve(data->cmd_paths[cmd_index], current_cmd->args_array, data->envp);
    perror("execve failed");
    exit(EXIT_FAILURE);
}































/*
void	execute_one_cmd(t_data *data, t_list *args)
{
    char **aa;

    aa = args_array(args);
    printf("Executing command: %s\n", aa[0]);
    printf("Command path: %s\n", data->cmd_paths[0]);
	execve(data->cmd_paths[0], aa, data->envp);
    free_array(aa);
}

void    execute_basic_cmds(t_data *data, t_list *args, int cmd_index)
{
    char **aa;
    int i;

    aa = args_array(args);
    if (cmd_index == 0)
    {
        dup2(data->pipefds[1], 1);
    }
    else if (cmd_index == data->cmds - 1)
    {
        dup2(data->pipefds[2 * (cmd_index - 1)], 0);
    }
    else
    {
        dup2(data->pipefds[2 * (cmd_index - 1)], 0);
        dup2(data->pipefds[2 * cmd_index + 1], 1);
    }
    i = 0;
    while (i < (data->cmds - 1) * 2)
    {
        close(data->pipefds[i]);
        i++;
    }
    i = 0;
    while (aa[i])
    {
        printf("Args[%d]: %s\n", i, aa[i]);
        i++;
    }
    execve(data->cmd_paths[cmd_index], aa, data->envp);
    perror("execve failed");
    free_array(aa);
    exit(EXIT_FAILURE);
}
*/