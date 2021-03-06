#include "./headers/overall.h"

void	print_promt(void)
{
	int		x;
	char	*str;

	str = "shell";
	x = 6;
	if (x == 2)
		ft_putstr_fd("\033[35m", 2);
	else if (x == 3)
		ft_putstr_fd("\033[34m", 2);
	else if (x == 4)
		ft_putstr_fd("\033[32m", 2);
	else if (x == 5)
		ft_putstr_fd("\033[33m", 2);
	else if (x > 5)
		ft_putstr_fd("\033[36m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[31m~\033[0m ", 2);
}

static void	set_all(t_all *all, char **envp)
{
	g_errno = 0;
	all->pipein = 0;
	all->redirect = 0;
	all->current_cmd = NULL;
	all->stroller = NULL;
	all->cursor_pos = 0;
	all->writen_symblos = 0;
	all->cmd_in_history = 0;
	all->env = NULL;
	all->stdout_tmp = dup(STDOUT_FILENO);
	all->stdin_tmp = dup(STDIN_FILENO);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ioctl(1, TIOCGWINSZ, &all->win);
	set_history(all);
	environment_to_struct(&(all->env), envp);
	copy_envp(all, envp);
	set_path(all->env, &(all->path));
	all->term_name = "xterm-256color";
	if (tcgetattr(0, &(all->term)))
		errors("Error: can't get terminal attrebuts.\n", TERM_ERROR);
	tgetent(0, all->term_name);
	all->cursor_pos = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_all	all;

	if (ac && av)
		;
	set_all(&all, envp);
	while (1)
	{
		all.term.c_lflag &= ~(ECHO);
		all.term.c_lflag &= ~(ICANON);
		all.term.c_lflag &= ~(ISIG);
		print_promt();
		tcsetattr(0, TCSANOW, &all.term);
		tputs(save_cursor, 1, ft_putint);
		handle_input(&all);
	}
	return (0);
}
