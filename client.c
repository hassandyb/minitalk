/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:41:29 by hed-dyb           #+#    #+#             */
/*   Updated: 2023/01/27 10:57:10 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_msg(int pid, char *msg)
{
	int	i;
	int	shifter;
	int	n;

	i = 0;
	while (msg[i] != '\0')
	{
		shifter = 0;
		while (shifter < 8)
		{
			n = 128 >> shifter;
			if ((n & msg[i]) == 0)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			shifter++;
			usleep(100);
			usleep(100);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		exit (1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		exit (1);
	ft_send_msg(pid, argv[2]);
}
