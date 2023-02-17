/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sj_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:25:06 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/17 10:56:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	case_line_spill()
{
	write(2, "minishell: line did not ended. exit\n", 36);
	exit(1);
}

void	sj_error(int errno)
{
	if (errno == LINE_SPILL)
		case_line_spill();
}

