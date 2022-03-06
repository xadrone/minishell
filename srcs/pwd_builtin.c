/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:05:47 by jgyles            #+#    #+#             */
/*   Updated: 2022/03/04 18:04:55 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd_buildin(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf)
	{
		printf("%s\n", buf);
		free (buf);
	}
	else
	{
		printf("minishell: pwd: %s\n", strerror(errno));
		return (errno);
	}
	return (0);
}
