#include "minitalk.h"

static	void	received_signal(int sig)
{
	if (sig == SIGUSR1)
		write(1, "Signal Received\n", 16);
}

void	ft_sendbit(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit != -1)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit--;
		signal(SIGUSR1, received_signal);
	}
}

int	main(int argc, char *argv[])
{
	int				pid;

	if (argc != 3)
	{
		write(1, "INVALID ARGUMENTS", 17);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	while (*argv[2])
		ft_sendbit(pid, *(argv[2]++));
	ft_sendbit(pid, '\n');
	ft_sendbit(pid, '\0');
	return (0);
}
