#include "../headers/overall.h"

int	cmp_data_to_env(char *data, char *key)
{
	if (*key == '_' && !*(key + 1))
		return (1);
	while (*data && *key)
	{
		if (*data != *key)
			return (1);
		data++;
		key++;
	}
	if (!*key && *data != '_' && ((*data >= ' ' && *data <= '/')
			|| (*data >= ':' && *data <= 64)
			|| (*data >= 91 && *data <= 96)
			|| (*data >= 123 && *data <= 126) || !*data))
		return (0);
	return (1);
}

int	add_matched_argument(char **arg, char *env_arg, int *arg_size)
{
	while (*env_arg)
	{
		*arg = char_join(arg, *env_arg, *arg_size);
		if (!*arg)
			return (BAD_MALLOC);
		(*arg_size)++;
		env_arg++;
	}
	return (ALL_OK);
}

void	skip_unnecessary_symbols(char **data, t_env_list *tmp)
{
	int		i;

	if (tmp)
	{
		i = -1;
		while ((tmp->item->key)[++i] == **data && *data && (tmp->item->key)[i])
			(*data)++;
	}
	else
	{
		while ((**data >= '0' && **data <= '9')
			|| ('A' <= **data && **data <= 'Z')
			|| ('a' <= **data && **data <= 'z')
			|| **data == '_')
			(*data)++;
	}
}

int	get_env_ergument(char **arg, char **data, int *arg_size, t_env_list **env)
{
	t_env_list	*tmp;

	(*data)++;
	tmp = *env;
	while (tmp)
	{
		if (cmp_data_to_env(*data, tmp->item->key) == 0)
		{
			if (add_matched_argument(arg, tmp->item->value, arg_size))
				return (BAD_MALLOC);
			break ;
		}
		tmp = tmp->next;
	}
	skip_unnecessary_symbols(data, tmp);
	return (ALL_OK);
}
