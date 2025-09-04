/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:44:46 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/04 19:01:15 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main ()
{
	char *input;
    t_token token;

	while (1)
	{
        input = readline("bbshell> ");
        if (*input)
        {
            add_history(input);  // saves it so ↑ arrow recalls it
            token_init(&token, input);
        }
        free(input);  // readline mallocs, so you must free it
    }
    return 0;
}
