/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyoo <seokjyoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:01:19 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/01/30 17:28:07 by seokjyoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// node example

// int main() {
// 	struct node *root = newNode(1);
// 	root->left = newNode(2);
// 	root->right = newNode(3);
// 	root->left->left = newNode(4);
// return 0;
// }
// node example

// 1. count pipe's number
// 2. allocates trees as many as the number of pipes counted
// 3. count each tree's tokens
// 4. allocates trees as many as the number of tokens counted
// 5. execute each tokens according to the hierarchy

t_node	*new_node(char *data, int is_root)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	node->is_root_end = is_root;
	node->data = data;
	node->next_class = NULL;
	return(node);
}

int	count_pipe(char *line)
{
	int	return_val;
	int	index;

	index = 0;
	return_val = 0;
	while (line[index])
	{
		if (line[index] == '|')
			return_val++;
		index++;
	}
	return (return_val);
}

t_node	*set_root(int count_num)
{
	t_node	*temp;
	t_node	*root;
	int		index;

	index = 0;
	root = new_node(NULL, 1);
	count_num++;
	root->next_class = (t_node *)malloc(sizeof(t_node) * (count_num + 1));
	(root->next_class)[count_num].is_root_end = -1;
	while (count_num)
	{
		(root->next_class)[count_num - 1].next_class = NULL;
		(root->next_class)[count_num - 1].is_root_end = 0;
		count_num--;
	}
	return (root);
}

void	alloc_cmd_before_pipe(char *line, int before_index, int next_index, char **data)
{
	int	index;

	index = 0;
	if (!line[next_index + 1] && line[next_index] != '|')
		next_index++;
	*data = (char *)malloc(sizeof(char) * (next_index - before_index + 1));
	while (before_index < next_index)
	{
		(*data)[index] = line[before_index];
		before_index++;
		index++;
	}
}

void	alloc_cmd(t_node *root, char *line)
{
	int		index;
	int		root_index;
	int		before_index;

	index = 0;
	before_index = 0;
	root_index = 0;
	while (line[index])
	{
		if (line[index] == '|' || !line[index + 1])
		{
			alloc_cmd_before_pipe(line, before_index, index, &(root->next_class)[root_index].data);
			before_index = index + 1;
			root_index++;
		}
		index++;
	}
}

void	printf_root(t_node *root)
{
	int		index;

	index = 0;
	while ((root->next_class)[index].is_root_end != -1)
	{
		printf("%s\n", (root->next_class)[index].data);
		index++;
	}
}

t_node	*parse_data(char *line)
{
	int		count_num;
	char	last_word;
	t_node	*root;

	last_word = line[ft_strlen(line) - 1];
	if (last_word == '|' || last_word == '&')
		sj_error(LINE_SPILL);
	count_num = count_pipe(line);
	root = set_root(count_num);
	alloc_cmd(root, line);
	printf_root(root);
	return (root);
}
