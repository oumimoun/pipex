/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_pipes_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:51:33 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/01 18:34:44 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_execute(t_data *data, char **argv, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(argv[data->i], ' ');
	path = check_path(cmd[0], envp);
	execve(path, cmd, envp);
	ft_print_error("Error in execve()");
}

void	ft_first_cmd(t_data *data, char **argv)
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		ft_print_error("Error opening infile");
	if (dup2(data->infile, 0) == -1)
		ft_print_error("Error in dup2()");
	close(data->infile);
}

void	ft_last_cmd(t_data *data, char **argv, char **envp)
{
	if (data->flag == 1)
		data->outfile = open(argv[data->ac - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		data->outfile = open(argv[data->ac - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->outfile == -1)
		ft_print_error("Error opening outfile");
	if (dup2(data->outfile, 1) == -1)
		ft_print_error("Error in dup2()");
	close(data->outfile);
	ft_execute(data, argv, envp);
}
