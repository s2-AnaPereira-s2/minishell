/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:48:22 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/05 17:18:18 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    cmd_init(t_cmd **cmd)
{
    if (!cmd)
        return;
    (*cmd)->args = NULL;
    (*cmd)->redir_in = NULL;
    (*cmd)->redir_out = NULL;
    (*cmd)->append = NULL;
    (*cmd)->heredoc = NULL;
    (*cmd)->next = NULL;
}