/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:44:12 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/08 18:51:00 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	execute_first(t_data *data, t_list *args)
{
    char **aa;

    aa = args_array(args);
    printf("Executing command: %s\n", data->cmd_paths[0]);
	execve(data->cmd_paths[0], aa, data->envp);
    
}