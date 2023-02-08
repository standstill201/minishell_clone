/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sj_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyoo <seokjyoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:25:06 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/01/30 17:29:41 by seokjyoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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