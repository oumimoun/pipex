/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:46:04 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/01 18:17:09 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../get_next_line/get_next_line_bonus.h"

static char	*get_file_name(void)
{
	char	*path;
	int		i;

	i = 0;
	while (i < OPEN_MAX)
	{
		path = ft_strjoin("/tmp/", ft_itoa(i));
		if (access(path, F_OK) == -1)
			return (path);
		i++;
	}
	return (NULL);
}

void	ft_here_doc(t_data *data)
{
	int	temp_fd;

	temp_fd = open(data->file_path, O_RDONLY);
	if (temp_fd == -1)
		ft_print_error("Error");
	if (dup2(temp_fd, 0) == -1)
		ft_print_error("Error in dup2()");
	close(temp_fd);
}

static void	ft_read_lines(t_data *data, char *line, int temp_fd)
{
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if ((ft_strncmp(line, data->limiter, ft_strlen(data->limiter)) == 0)
			&& (ft_strlen(line) - 1 == ft_strlen(data->limiter)))
		{
			free(line);
			break ;
		}
		if (write(temp_fd, line, ft_strlen(line)) == -1)
		{
			free(line);
			close(temp_fd);
			unlink(data->file_path);
			ft_print_error("Error");
		}
		free(line);
	}
}

void	ft_handle_here_doc(t_data *data, char **argv, char **envp)
{
	char	*line;
	int		temp_fd;

	line = NULL;
	data->file_path = get_file_name();
	data->limiter = argv[2];
	data->flag = 1;
	temp_fd = open(data->file_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp_fd == -1)
		ft_print_error("Error");
	ft_read_lines(data, line, temp_fd);
	close(temp_fd);
	pipex(data, argv, envp);
	unlink(data->file_path);
	free(data->file_path);
	data->file_path = NULL;
}
