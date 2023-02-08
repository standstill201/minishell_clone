/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 07:38:45 by codespace         #+#    #+#             */
/*   Updated: 2023/02/08 09:49:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <string.h>

// 1. seperate string by white space and special metacharacter |. each seperated string is named 'token'
// 2. if each token seperated by white space, intermidiate token is saved as a white space
// 3. if token is wrapped by double quotation or single quotation, it is saved as a single token
// 4. token is saved in a linked list
// example: echo hello world -> "echo", " ", "hello world"
// exmaple2: cat infile'|' | grep hello -> "cat", " ", "infile'|'", " ", "|", " ", "grep", " ", "hello"

// make a function seperate string by white space and special metacharacter |. each seperated string is named 'token'

void	read_string_before_quote(char str)
{
	int		index;
	char	*return_val;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\'' || str[index] == '\"')
			break ;
		index++;
	}
	return_val = (char *)malloc(sizeof(char) * (index + 1));
	index = 0;
	while (str[index])
	{
		if (str[index] == '\'' || str[index] == '\"')
			break ;
		return_val[index] = str[index];
		index++;
	}
	return_val[index] = '\0';
	return (return_val);
}


char	**seperate_string(char *str)
{
	int		index;
	char	**return_val;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\'' || str[index] == '\"')
			read_string_before_quote(&str[index + 1]);
		index++;
	}
}

// make a test case main function
int main()
{
	char	**return_val;
	int		index;

	index = 0;
	return_val = seperate_string("echo'|' hello world");
	while (return_val[index])
	{
		printf("%s\n", return_val[index]);
		index++;
	}
	return (0);
}
