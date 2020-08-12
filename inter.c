/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <qcraghas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:24:28 by qcraghas          #+#    #+#             */
/*   Updated: 2020/08/11 16:02:13 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_inter(char *s1, char *s2)
{
	int i;
	int j;
	int dup;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		dup = 1;
		while (j < i)
			if (s1[j++] == s1[i])
			{
				dup = 0;
				break ;
			}
		j = 0;
		if (dup == 1)
			while (s2[j] != '\0')
				if (s1[i] == s2[j++])
				{
					write(1, (s1 + i), 1);
					break ;
				}
		i++;
	}
}

int		main(int argc, char *argv[])
{
	if (argc != 3 || (!argv[1] || !argv[2]))
		write(1, "\n", 1);
	else
		ft_inter(argv[1], argv[2]);
	return (0);
}
