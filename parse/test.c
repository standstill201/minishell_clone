typedef struct s_node {
	int				is_root_end;
	char			*data;
	struct s_node	*next_class;
}	t_list;
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

t_list	*new_node(char *data, int is_root)
{
	t_list *node;

	node = (t_list *)malloc(sizeof(t_list));
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

t_list	*set_root(int count_num)
{
	t_list	*temp;
	t_list	*root;
	int		index;

	index = 0;
	root = new_node(NULL, 1);
	count_num++;
	root->next_class = (t_list *)malloc(sizeof(t_list) * (count_num + 1));
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
	if (!line[next_index + 1])
		next_index++;
	*data = (char *)malloc(sizeof(char) * (next_index - before_index + 1));
	while (before_index < next_index)
	{
		(*data)[index] = line[before_index];
		before_index++;
		index++;
	}
}

void	alloc_cmd(t_list *root, char *line)
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
			// printf("%s\n",(root->next_class)[root_index].data);
			before_index = index + 1;
			root_index++;
		}
		index++;
	}
}

void	print_root(t_list *root)
{
	int		index;

	index = 0;
	while ((root->next_class)[index].is_root_end != -1)
	{
		printf("len:%d    ", strlen((root->next_class)[index].data));
		printf("%s\n", (root->next_class)[index].data);
		index++;
	}
}

t_list	*parse_data(char *line)
{
	int		count_num;
	t_list	*root;

	count_num = count_pipe(line);
	root = set_root(count_num);
	alloc_cmd(root, line);
	print_root(root);
	return (root);
}


int main()
{
		t_list	*line_root;
		char	*line;

		line = strdup("asdf|asdf");

		line_root = parse_data(line);

}