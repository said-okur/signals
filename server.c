/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokur <sokur@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:12:26 by sokur             #+#    #+#             */
/*   Updated: 2023/08/15 20:36:20 by sokur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>


void	ft_handle(int sig, siginfo_t *info, void *context)
{
	static int	bit = 7;
	static int	c = 0;

	(void)context;
	if (sig == SIGUSR1)
	{
		c |= 1 << bit;
	}
	bit--;
	if (bit == -1)
	{
		write(1, &c, 1);
		if (c == '\0')
			kill(info->si_pid, SIGUSR1);
		bit = 7;
		c = 0;
	}
}


int	main(void)
{
	struct sigaction	act;
	int	pid;

	pid = getpid();
	write(1, "Server PID: ", 12);
	ft_putnbr(pid);
	write(1, "\n", 1);
	act.sa_sigaction = ft_handle;
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
