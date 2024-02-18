/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:22:48 by oumimoun          #+#    #+#             */
/*   Updated: 2024/02/18 19:31:43 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void ft_execute(t_data *data, char **argv, char **envp)
{
    char *path;
    char **cmd;

    cmd = ft_split(argv[data->i], ' ');
    path = check_path(cmd[0], envp);
    execve(path, cmd, envp);
    ft_print_error("Error in execve()");
    // exit(EXIT_FAILURE);
}

void ft_parent_process(t_data *data)
{
    (void)data;
    // close(data->pd[0]);
    // close(data->pd[1]);
    // dup2(data->pd[0], 0);
    // close(data->save);

    // close(data->save);

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
        {
            data->infile = open(argv[1], O_RDONLY, 0777);
            if (data->infile == -1)
                ft_print_error("Error opening infile");
            dup2(data->infile, 0);
            dup2(data->pd[1], 1);
            close(data->pd[1]);
            close(data->infile);
            ft_execute(data, argv, envp);
        }
        dup2(data->save, 0);
        if (data->i == data->ac - 2)
        {
            data->outfile = open(argv[data->ac - 1], O_RDWR | O_TRUNC, 0777);
            dup2(data->outfile, 1);
            close(data->outfile);
            close(data->pd[1]);
            ft_execute(data, argv, envp);
        }
        // dup2()
        
        dup2(data->pd[1], 1);
        close(data->pd[1]);
        ft_execute(data, argv, envp);
    }

    // 
    data->save = dup(data->pd[0]);
    // dup2( data->save , data->pd[0]);
    printf("%d %d\n", data->save, data->pd[1]);
    close(data->pd[0]);
    close(data->pd[1]);
    // ft_parent_process(data);
    // close(data->save);
}

void pipex(t_data *data, char **argv, char **envp)
{
    data->i = 2;
    data->save = -1;
    while (data->i <= data->ac - 2)
    {
        middle_process(data, argv, envp);
        data->i++;
    }
    // par
    ft_parent_process(data);
    // close(data->save);

}

void f(void)
{
    system("lsof -c pipex");
}

int main(int argc, char **argv, char **envp)
{
    t_data data;
    atexit(f);
    if (!envp)
        ft_print_error("Error empty environment");
    if (argc >= 5)
    {
        data.ac = argc;
        pipex(&data, argv, envp);
    }
    else
        ft_print_error("Usage: ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2");
    return 0;
}
