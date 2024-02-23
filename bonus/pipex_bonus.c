/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:22:48 by oumimoun          #+#    #+#             */
/*   Updated: 2024/02/21 18:53:59 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../get_next_line/get_next_line.h"



void ft_parent_process(t_data *data)
{
    close(data->save);
    while (waitpid(-1, NULL, 0) != -1)
        ;
}


void middle_process(t_data *data, char **argv, char **envp)
{
    pid_t pid;

    if (pipe(data->pd) == -1)
        ft_print_error("Error in pipe()");
    pid = fork();
    if (pid == -1)
        ft_print_error("Error in fork()");
    if (pid == 0)
    { // child
        close(data->pd[0]);
        if (data->i == 2)
            ft_first_cmd(data, argv);
        if ((data->flag == 1) && data->i == 3)
            ft_here_doc();
        dup2(data->save, 0);
        if (data->i == data->ac - 2)
            ft_last_cmd(data, argv, envp);
        dup2(data->pd[1], 1);
        close(data->pd[1]);
        ft_execute(data, argv, envp);
    }
    close(data->save);
    data->save = dup(data->pd[0]);
    close(data->pd[0]);
    close(data->pd[1]);
}

void pipex(t_data *data, char **argv, char **envp)
{
    data->i = 2;
    data->save = -1;
    if (data->flag == 1)
        data->i = 3;
    while (data->i <= data->ac - 2)
    {
        middle_process(data, argv, envp);
        data->i++;
    }
    ft_parent_process(data);
}

void f(void)
{
    system("lsof -c pipex");
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    // atexit(f);

    if (argc == 1)
        ft_print_error("Usage: ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2");
    if (!envp)
        ft_print_error("Error empty environment");
    if (!ft_strncmp(argv[1], "here_doc", 9) && argc == 6)
    {
        data.ac = argc;
        ft_handle_here_doc(&data, argv, envp);
    }
    else if (argc >= 5)
    {
        data.ac = argc;
        data.flag = 0;
        pipex(&data, argv, envp);
    }
    else
        ft_print_error("Usage: ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2");
    return 0;
}
