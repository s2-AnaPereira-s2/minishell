/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:13:52 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/11 17:31:02 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void    get_pipefds(t_cmd **cmd, t_data *data)
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
    if (data->cmds == 1)
    {
        data->pids[0] = fork();
        if (data->pids[0] < 0)
        {
            perror("Fork failed");
            return ;
        }
        if (data->pids[0] == 0)
        {
            execute_one_cmd(data, args);
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        waitpid(data->pids[0], NULL, 0);
        return ;
    }
    else
    {
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
                execute_basic_cmds(data, args, i);
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
            i++;
        }
        i = 0;
        while (i < data->cmds)
        {
            waitpid(data->pids[i], NULL, 0);
            i++;
        }
            
    }
}
