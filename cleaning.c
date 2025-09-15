/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:47:28 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/15 16:54:32 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void free_token_list(t_tokens **tokens)
{
    t_tokens *temp;
    t_tokens *next;

    temp = *tokens;
    while (temp)
    {
        next = temp->next;
        free(temp->value);
        free(temp);
        temp = next;
    }
    *tokens = NULL;
}

void free_cmd_list(t_cmd **cmd)
{
    t_cmd *temp;
    t_cmd *next;

    temp = *cmd;
    while (temp)
    {
        next = temp->next;
        if (temp->args)
            ft_lstclear(&(temp->args), free);
        if (temp->args_array)
            free_array(temp->args_array);
        free(temp->redir_in_file);
        free(temp->redir_out_file);
        free(temp->append_file);
        free(temp->heredoc_limiter);
        free(temp);
        temp = next;
    }
    *cmd = NULL;
}

void free_data(t_data *data)
{
    if (!data)
        return;
    free_array(data->cmd_paths);
    free(data->path);
    free(data->pipefds);
    free(data->pids);
}

void cleaning_func(t_tokens **tokens, t_list **lexemes, t_cmd **cmd)
{
    if (tokens && *tokens)
        free_token_list(tokens);
    if (lexemes && *lexemes)
        ft_lstclear(lexemes, free);
    if (cmd && *cmd)
        free_cmd_list(cmd);
}
