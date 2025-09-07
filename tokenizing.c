/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:42:57 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/05 11:39:28 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


void get_token_type(t_tokens *token_node)
{
    if (!token_node)
        return ;
    if (ft_strncmp(token_node->value, "|", 1) == 0)
        token_node->type = TOKEN_PIPE;
    else if (ft_strncmp(token_node->value, ">>", 2) == 0)
        token_node->type = TOKEN_APPEND;
    else if (ft_strncmp(token_node->value, "<<", 2) == 0)
        token_node->type = TOKEN_HEREDOC;
    else if (ft_strncmp(token_node->value, "<", 1) == 0)
        token_node->type = TOKEN_REDIR_IN;
    else if (ft_strncmp(token_node->value, ">", 1) == 0)
        token_node->type = TOKEN_REDIR_OUT;
    else
        token_node->type = TOKEN_WORD;
}

void    get_token_value(t_list *lexemes, t_tokens **tokens)
{
    t_list *temp;
    t_tokens *last;

    temp = lexemes;
    last = NULL;
    while (temp)
    {
        t_tokens *token_node;
        char *lexeme;
        lexeme = (char *)temp->content;
        token_node = malloc(sizeof(t_tokens));
        if (!token_node)
            return ;
        token_node->value = ft_strdup(lexeme);
        token_node->next = NULL;
        get_token_type(token_node);
        if (!*tokens)
            *tokens = token_node;
        else
            last->next = token_node;
        last = token_node;
        temp = temp->next;
    }
    //print_tokens(*tokens);
}

int get_start(char *input, int i)
{
    int start;

    while (input[i] && input[i] == ' ')
        i++;
    start = i;
    return start;
}

void get_lexemes(t_list **lexemes, t_tokens **tokens, char *input)
{
    int i;
    int start;

    i = 0;
    while (input[i])
    {
        start = get_start(input, i);
        i = start;
        if (input[i] == '"' || input[i] == '\'')
        {
            char quote;
            
            quote = input[i++];
            start = i;
            while (input[i] && input[i] != quote)
                i++;
            if (i > start)
                ft_lstadd_back(lexemes, ft_lstnew(ft_substr(input, start, i - start)));
            if (input[i] == quote)
                i++; 
        }
        else 
        {
            while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != '\'')
                i++;
            if (i > start)
                ft_lstadd_back(lexemes, ft_lstnew(ft_substr(input, start, i - start)));
        }
    }
    get_token_value(*lexemes, tokens);
}

