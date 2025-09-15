/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:09 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/14 20:12:28 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_tokens *get_next_token_redir(t_tokens *temp, t_cmd *current_cmd)
{
    if (temp->type == TOKEN_REDIR_IN)
    {
        if (!temp->next || temp->next->type != TOKEN_WORD)
        {
            printf("Error: Missing filename after '<'\n");
            return (NULL);
        }
        (current_cmd)->redir_in_file = ft_strdup(temp->next->value);
        temp = temp->next;
    }
    else if (temp->type == TOKEN_REDIR_OUT)
    {
        if (!temp->next || temp->next->type != TOKEN_WORD)
        {
            printf("Error: Missing filename after '>'\n");
            return (NULL);
        }
        (current_cmd)->redir_out_file = ft_strdup(temp->next->value);
        temp = temp->next;
    }
    return (temp);
}

t_tokens *get_next_token_append_heredoc(t_tokens *temp, t_cmd *current_cmd)
{
    if (temp->type == TOKEN_APPEND)
    {
        if (!temp->next || temp->next->type != TOKEN_WORD)
        {
            printf("Error: Missing filename after '>>'\n");
            return (NULL);
        }
        (current_cmd)->append_file = ft_strdup(temp->next->value);
        temp = temp->next;
    }
    else if (temp->type == TOKEN_HEREDOC)
    {
        if (!temp->next || temp->next->type != TOKEN_WORD)
        {
            printf("Error: Missing delimiter after '<<'\n");
            return (NULL);
        }
        (current_cmd)->heredoc_limiter = ft_strdup(temp->next->value);
        temp = temp->next;
    }
    return (temp);
}

t_cmd *get_token_word_pipe(t_tokens *temp, t_cmd *current_cmd)
{
    t_list *new;
    
    if (temp->type == TOKEN_WORD)
    {
        new = ft_lstnew(ft_strdup(temp->value));
        if (!new)
            return (NULL);
        ft_lstadd_back(&((current_cmd)->args), new);
    }
    else if (temp->type == TOKEN_PIPE)
    {
        if (!temp->next)
        {
            printf("Error: Missing command and argument after '|'\n");
            return (NULL);
        }
        cmd_init(&(current_cmd->next));
        current_cmd = current_cmd->next;
    }
    return (current_cmd);
}

void	parse_tokens(t_tokens **tokens, t_cmd **cmd)
{
	t_tokens	*temp;
	t_cmd	*current_cmd;
	
    if (!tokens || !*tokens || !cmd)
        return;
    temp = *tokens;
    current_cmd = *cmd;
    while (temp)
    {
        if (temp->type == TOKEN_WORD)
            current_cmd = get_token_word_pipe(temp, current_cmd);
        else if (temp->type == TOKEN_REDIR_IN)
            temp = get_next_token_redir(temp, current_cmd);
        else if (temp->type == TOKEN_REDIR_OUT)
            temp = get_next_token_redir(temp, current_cmd);
        else if (temp->type == TOKEN_APPEND)
            temp = get_next_token_append_heredoc(temp, current_cmd);
        else if (temp->type == TOKEN_HEREDOC)
            temp = get_next_token_append_heredoc(temp, current_cmd);
        else if (temp->type == TOKEN_PIPE)
            current_cmd = get_token_word_pipe(temp, current_cmd);
        if(!temp || !current_cmd)
            return ;
        temp = temp->next;
    }
}


