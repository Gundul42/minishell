#include "../header/minishell.h"

void	clear_previous_tokens(t_split *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 40)
	{
		j = 0;
		while (j < 200)
		{
			data->tokens[i][j] = '\0';
			j++;
		}
		i++;
	}
}

//parses input inside data->token 2d array,
//tokens that were inside '' are start with '' so we can recognize them, "lol"->""lol
void	ms_input_parser(char *input, t_split *data)
{
	int space_found;
	int	d;
	int	t;
	int	ends_with_quotes;
	
	d = 0;
	ends_with_quotes = 0;
	clear_previous_tokens(data);
	while (input[data->i] != '\0')
	{
		space_found = 0;
		while (input[data->i] == ' ')
		{
			// in case there are space before 1st token
			if (d == 0 && data->i == 0)
			{
				// its + 1 because there is another i++ before while closing
				while (input[data->i + 1] == ' ')
					data->i++;
			}
			else if (space_found == 0 && ends_with_quotes == 0)
			{
				space_found = 1;
				d++;
				t = 0;
			}
			data->i++;
		}

		ends_with_quotes = 0;
		if (input[data->i] == '\'')
		{
			if (data->i > 0 && input[data->i - 1] != ' ')
			{
				d++;
				t = 0;
			}
			if (ft_strchr(input + data->i + 1, '\'') == 0)
			{
				data->tokens[d][t] = input[data->i];
				data->i++;
				t++;
			}
			else
			{
				data->tokens[d][t] = '\'';
				data->tokens[d][t + 1] = '\'';
				t += 2;
				data->i++;
				while (input[data->i] != '\'')
				{
					data->tokens[d][t] = input[data->i];
					t++;
					data->i++;
				}
				data->i++;
				d++;
				t = 0;
				ends_with_quotes = 1;
			}
		}
		else if (input[data->i] == '"')
		{
			data->i++;
			if (data->i > 0 && input[data->i - 1] != ' ')
			{
				d++;
				t = 0;
			}
			if (ft_strchr(input + data->i + 1, '"') == 0)
			{
				data->tokens[d][t] = input[data->i];
				data->i++;
				t++;
			}
			else
			{
				while (input[data->i] != '"')
				{
					data->tokens[d][t] = input[data->i];
					t++;
					data->i++;
				}
				data->i++;
				d++;
				t = 0;
				ends_with_quotes = 1;
			}
		}
		else
		{
			data->tokens[d][t] = input[data->i];
			t++;
			data->i++;
		}
	}
}
