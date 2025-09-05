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

void cleaning_func(t_tokens **tokens, t_list **lexemes, t_cmd **cmd) 
{
    ft_lstclear(lexemes, NULL);
    ft_lstclear(tokens, NULL);
    ft_lstclear(cmd, NULL);
}