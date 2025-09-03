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

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main ()
{
    char *input;

    while (1)
    {
        input = readline("minishell> ");  // prints prompt and waits
        if (!input)  // NULL means user pressed Ctrl+D (EOF)
        {
            printf("exit\n");
            break;
        }
        if (*input)  // non-empty string
            add_history(input);  // saves it so ↑ arrow recalls it
        printf("You typed: %s\n", input);
        free(input);  // readline mallocs, so you must free it
    }
    return 0;
    
}