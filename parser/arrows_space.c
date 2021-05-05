#include "../headers/overall.h"

int	put_endline(t_lst **last_arg)
{
	(*last_arg)->str = char_join(&((*last_arg)->str), '\0', 0);
	if (!(*last_arg)->str)
		return (BAD_MALLOC);
	return (ALL_OK);
}

int	handle_space(char **data, t_lst **last_arg)
{
	t_lst	*tmp;
	char	*tmp_str;

	tmp_str = *data;
	if ((*last_arg)->str == NULL)
		if (put_endline(last_arg))
			return (BAD_MALLOC);
	while (*tmp_str == ' ')
		tmp_str++;
	if (*tmp_str)
	{
		tmp = lstnew_char(NULL);
		if (!tmp)
			return (BAD_MALLOC);
		lst_add_back(last_arg, tmp);
		*last_arg = (*last_arg)->next;
	}
	while (*(*data + 1) == ' ')
		(*data)++;
	return (ALL_OK);
}

int	handle_arrows(char **data, t_lst **last_arg)
{
	t_lst	*tmp;
	int		arg_size;

	if ((*last_arg)->str)
	{
		tmp = lstnew_char(NULL);
		if (!tmp)
			return (BAD_MALLOC);
		lst_add_back(last_arg, tmp);
		*last_arg = (*last_arg)->next;
	}
	arg_size = 0;
	while (**data == '<' || **data == '>')
	{
		(*last_arg)->str = char_join(&((*last_arg)->str), **data, arg_size);
		if (!(*last_arg)->str)
			return (BAD_MALLOC);
		++*data;
		arg_size++;
	}
	if (**data != ' ' && **data)
	{
		tmp = lstnew_char(NULL);
		if (!tmp)
			return (BAD_MALLOC);
		lst_add_back(last_arg, tmp);
		*last_arg = (*last_arg)->next;
	}
	(*data)--;
	return (ALL_OK);
}
