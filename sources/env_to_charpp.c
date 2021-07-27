#include "../headers/overall.h"

int	ft_env_list_size(t_env_list *lst)
{
	int		size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

static char	*env_item_to_str(t_env_item *item)
{
	char 	*string;
	size_t	i;
	size_t	count;

	i = 0;
	count = (ft_strlen(item->key) + ft_strlen(item->value) + 1) * sizeof (char);
	string = (char *)malloc(count);
	count = 0;
	if (!string)
		return (NULL);
	while (i < ft_strlen(item->key))
	{
		string[i] = item->key[i];
		i++;
	}
	string[i++] = '=';
	while (count++ < ft_strlen(item->value))
	{
		string[i++] = *item->value;
		item->value++;
	}
	string[i] = '\0';
	return (string);
}

char	**env_to_charpp(t_all *all)
{
	char	**tmp;
	int		len_of_list;
	int 	i;

	i = 0;
	len_of_list = ft_env_list_size(all->env);
	tmp = (char **)malloc((sizeof (char *) * len_of_list + 1));
	if (!tmp)
		return (NULL);
	while (all->env)
	{
		tmp[i] = env_item_to_str(all->env->item);
		if (!tmp[i])
		{
			while (i >= 0)
				free(tmp[i--]);
			return (NULL);
		}
		i++;
		all->env = all->env->next;
	}
	tmp[len_of_list] = "\0";
	return (tmp);
}