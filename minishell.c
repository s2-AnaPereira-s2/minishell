/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:44:46 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/03 19:04:42 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main ()
{
	char *input;

	while (1)
	{
        input = readline("minishell> ");
        if (*input)
        {
            add_history(input);  // saves it so ↑ arrow recalls it
            get_tokens(input);
            printf("You typed: %s\n", input);
        }
        free(input);  // readline mallocs, so you must free it
    }
    return 0;
}
