/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pdos <ana-pdos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:44:46 by ana-pdos          #+#    #+#             */
/*   Updated: 2025/09/12 19:25:57 by ana-pdos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main (int argc, char **argv, char **envp)
{
	char *input;
    t_tokens *tokens;
    t_list *lexemes;
    t_data data;
    t_cmd *cmd;
    t_cmd *temp;
    t_list *args_temp;
    int len;
    int i;

    (void)argv;
    (void)argc;
    tokens = NULL;
    lexemes = NULL;
    data.envp = envp;
    cmd_init(&cmd);
    i = 0;
	while (1)  
	{
        cmd->index_args_array = 0;
        input = readline("bbshell> ");
        if (!input)
            break;
        if (*input)
        {
            add_history(input);
            get_lexemes(&lexemes, &tokens, input);
            parse_tokens(&tokens, &cmd);
            len = ft_lstsize(cmd->args);
            (*cmd).args_array = malloc((len + 1) * sizeof(char *));
            if (!(*cmd).args_array)
                return (1);
            get_cmds_count(&cmd, &data);
            data.cmd_paths = malloc((data.cmds + 1) * sizeof(char *));
            if (!data.cmd_paths)
                return (1);
            temp = cmd;
            while (temp)
            {
                args_temp = temp->args;
                while (args_temp)
                {
                    printf("Finding path for command: %s\n", (char *)args_temp->content);
                    args_to_array(&cmd, args_temp);
                    data.cmd_paths[i] = find_path(args_temp, &data);
                    printf("I'm here inside loop\n");
                    break ;
                }
                i++;
                temp = temp->next;
            }
            (*cmd).args_array[(*cmd).index_args_array] = NULL;
            data.cmd_paths[i] = NULL;
            get_pipefds(&cmd, &data);
            process_pids(&data, &cmd);
        }
        free(input);
        cleaning_func(&tokens, &lexemes, &cmd);
        cmd_init(&cmd);
    }
    return 0;
}
