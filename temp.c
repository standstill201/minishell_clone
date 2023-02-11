// this function makes linked list to string. the string is seperated by pipe_n
// char	**make_linked_list_to_array(t_list *root)
// {
// 	char	**return_val;
// 	t_list	*temp;
// 	int		index;
// 	int		pipe_n;

// 	temp = root;
// 	pipe_n = ft_lstlast(root)->pipe_n;
// 	return_val = (char **)malloc(sizeof(char *) * (pipe_n + 2));
// 	index = 0;
// 	while (index <= pipe_n)
// 	{
// 		return_val[index] = (char *)malloc(sizeof(char) * 1);
// 		return_val[index][0] = '\0';
// 		index++;
// 	}
// 	return_val[index] = 0;
// 	temp = root->next;
// 	while (temp)
// 	{
// 		return_val[temp->pipe_n] = ft_strjoin(return_val[temp->pipe_n], temp->content);
// 		temp = temp->next;
// 	}
// 	return (return_val);
// }

	// index = 0;
	// return_val_char = make_linked_list_to_array(return_val);
	// while (return_val_char[index])
	// {
	// 	printf("return_val_char[%d]: $%s$\n", index, return_val_char[index]);
	// 	index++;
	// }

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// make test case of getenv function
int main()
{
	char *return_val;
	return_val = getenv("dfasdfa");
	printf("return_val: %s\n", return_val);
	return (0);
}
