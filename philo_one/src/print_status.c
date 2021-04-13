#include "../inc/philo_one.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int		print_status(t_phil *phil, char *action)
{
	char	buf[100];
	char	*time;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (phil->state->death)
		return (0);
	time = ft_itoa(time_since(phil->state->start_time));
	while (time[j])
		buf[i++] = time[j++];
	free(time);
	buf[i] = ' ';
	i++;
	j = 0;
	while (phil->id[j])
		buf[i++] = phil->id[j++];
	buf[i] = ' ';
	i++;
	j = 0;
	while (action[j])
		buf[i++] = action[j++];
	buf[i] = '\n';
	buf[i + 1] = '\0';
	if (phil->state->at_table > 0)
		write(1, buf, ft_strlen(buf));
	return (1);
}