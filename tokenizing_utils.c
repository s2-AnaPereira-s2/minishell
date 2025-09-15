/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 19:01:45 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/14 19:17:38 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

int get_start(char *input, int i)
{
    int start;

    while (input[i] && input[i] == ' ')
        i++;
    start = i;
    return start;
}

int dollar_sign_check(char *input)
{
    int i;

    i = 0;
    while(input[i])
    {
        if (input[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

int get_quote_word(t_list **lexemes, char *input, int i, int expand)
{
    int start;
    char quote;
    
    quote = input[i++];
    if (expand == 1)
    {
        start = i - 1;
        while (input[i] && input[i] != quote)
            i++;
        if (i > start)
            ft_lstadd_back(lexemes, ft_lstnew(ft_substr(input, start, (i - start) + 1)));
        if (input[i] == quote)
            i++; 
    }
    else
    {
        start = i;
        while (input[i] && input[i] != quote)
            i++;
        if (i > start)
            ft_lstadd_back(lexemes, ft_lstnew(ft_substr(input, start, i - start)));
        if (input[i] == quote)
            i++;
    }
    return (i);
}

void    get_normal_lexemes(t_list **lexemes, char *input)
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
            i = get_quote_word(lexemes, input, i, 0);
        }
        else 
        {
            while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != '\'')
                i++;
            if (i > start)
                ft_lstadd_back(lexemes, ft_lstnew(ft_substr(input, start, i - start)));
        }
    }
}

void    get_expand_lexemes(t_list **lexemes, char *input)
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
            i = get_quote_word(lexemes, input, i, 1);
        }
        else 
        {
            while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != '\'')
                i++;
            if (i > start)
                ft_lstadd_back(lexemes, ft_lstnew(ft_substr(input, start, i - start)));
        }
    }
}

