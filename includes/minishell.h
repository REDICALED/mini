/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:53:27 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/02 15:53:36 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <./readline/readline.h>
# include <./readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "libft.h"

typedef enum
{
	string,
	dollar,
	s_quote,
	d_quote,
	read_in,
	read_in2,
	read_out,
	read_out2,
	e_pipe,
	e_error
}		t_token;

//typedef struct s_info
//{
//	int		quote;
//	int		pipe;
//}				t_info;

typedef	struct s_node
{
	t_token	token;
	char	*str;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef	struct s_global
{
	int		len;
	char	*line;
	int 	token_count;
	t_node	*head;
	t_node	*tail;
}				t_global;

//tokenize_util.c
int	count_1(t_global *global, int i);
int	count_2(t_global *global, int i);
int	count_3(t_global *global, int *i);
int	count_4(t_global *global, int *i);
int	count_5(t_global *global, int *i);

//tokenize_util2.c
int	count_6(t_global *global, int i);
int	count_7(t_global *global, int i);
int	count_8(t_global *global, int i);
int	count_9(t_global *global, int i);

//util.c
int	is_space(char *line);
void ft_error(char *str);
void ft_print_node(t_node *head);

//tokenize_util.c
void	add_node(t_global *global, t_token token, char *str);
void	init_global(t_global *global, char *line);
void    tokenize(char *line, t_global *global);

#endif
