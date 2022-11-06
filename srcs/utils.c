/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:00:35 by jinhokim          #+#    #+#             */
/*   Updated: 2022/11/01 21:11:47 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && !(line[i] >= 9 && line[i] <= 13))
			return (0);
	}
	return (1);
}

void ft_error(char *str)
{
	printf("%s\n", str);
}

void ft_print_node(t_node *head)
{
	t_node *node;
	
	node = head->next;
	while (node)
	{
		printf("token: %d, str: %s\n", node->token, node->str);
		node = node->next;
	}
}