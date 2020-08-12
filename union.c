/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <qcraghas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:03:47 by qcraghas          #+#    #+#             */
/*   Updated: 2020/08/11 17:15:26 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void    ft_union(char *s1, char *s2, int c)
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
        if (c == 1)
            while (s2[j] != '\0')
                if (s2[j++] == s1[i])
                {
                    dup = 0;
                    break ;
                }
		if (dup == 1)
            write (1, (s1 + i), 1);
		i++;
	}
}

int     main(int argc, char *argv[])
{
    if (argc != 3 || (!argv[1] || !argv[2]))
        write(1, "\n", 1);
    else
        ft_union(argv[1], argv[2], 0);
        ft_union(argv[2], argv[1], 1);
    return (0);
}