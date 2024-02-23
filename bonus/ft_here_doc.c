/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:04 by oumimoun          #+#    #+#             */
/*   Updated: 2024/02/21 18:54:51 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../get_next_line/get_next_line.h"

void ft_here_doc(void)
{
    int temp_fd = open("/tmp/temp_file", O_RDONLY);
    if (temp_fd == -1)
        ft_print_error("Error");
    if (dup2(temp_fd, 0) == -1)
        ft_print_error("Error in dup2()");
    close(temp_fd);
}

void ft_handle_here_doc(t_data *data, char **argv, char **envp)
{
    char *line = NULL;
    int temp_fd;

    data->LIMITER = argv[2];
    data->flag = 1;
    temp_fd = open("/tmp/temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (temp_fd == -1)
        ft_print_error("Error");
    write(1, ">", 1);
    while ((line = get_next_line(0)) != NULL)
    {
        if (ft_strncmp(line, data->LIMITER, ft_strlen(data->LIMITER)) == 0)
        {
            free(line);
            break;
        }
        write(1, ">", 1);
        if (write(temp_fd, line, ft_strlen(line)) == -1)
        {
            free(line);
            close(temp_fd);
            unlink("/tmp/temp_file");
            ft_print_error("Error");
        }
        free(line);
    }
    close(temp_fd);
    pipex(data, argv, envp);
    unlink("/tmp/temp_file");
}

