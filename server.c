/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hed-dyb <hed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:42:07 by hed-dyb           #+#    #+#             */
/*   Updated: 2023/01/27 11:01:02 by hed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signals_handler(int signum, siginfo_t *info, void *extra)
{
	static int				pidcheck;
	static unsigned char	c;
	static int				i;
	int						signal;

	(void)extra;
	if (pidcheck != info->si_pid)
	{
		c = '\0';
		i = 0;
		pidcheck = info->si_pid;
	}
	signal = 0;
	if (signum == SIGUSR1)
		signal = 1;
	c = c << 1;
	c = c | signal;
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = '\0';
	}
}

int	main(void)
{
	struct sigaction	cs;

	ft_putnbr(getpid());
	write(1, "\n", 1);
	cs.sa_sigaction = &signals_handler;
	cs.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &cs, NULL);
	sigaction(SIGUSR2, &cs, NULL);
	while (1)
		pause();
}
