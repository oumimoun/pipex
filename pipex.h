/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:52:57 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/01 19:43:23 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_data
{
	char	*limiter;
	char	*file_path;
	int		infile;
	int		outfile;
	int		pd[2];
	int		ac;
	int		i;
	int		save;
	int		flag;

}	t_data;

char	**ft_split(char const *s, char c);
char	**ft_get_paths(char **envp);
char	*ft_strjoin(char *s1, char *s2);
char	*check_path(char *cmd, char **envp);
char	*ft_itoa(int n);
void	ft_free(char **result);
void	ft_print_error(char *str);
void	ft_handle_here_doc(t_data *data, char **argv, char **envp);
void	ft_here_doc(t_data *data);
void	ft_execute(t_data *data, char **argv, char **envp);
void	ft_first_cmd(t_data *data, char **argv);
void	ft_last_cmd(t_data *data, char **argv, char **envp);
void	pipex(t_data *data, char **argv, char **envp);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strlen(char *str);

#endif
