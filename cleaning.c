/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:47:28 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/05 17:14:52 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

static void free_cmd_list(t_cmd **cmd)
{
    t_cmd *temp;
    t_cmd *next;

    temp = *cmd;
    while (temp)
    {
        next = temp->next;
        if (temp->args)
            ft_lstclear(&(temp->args), free);
        free(temp->redir_in);
        free(temp->redir_out);
        free(temp->append);
        free(temp->heredoc);
        free(temp);
        temp = next;
    }
    *cmd = NULL;
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