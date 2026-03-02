#include <stdio.h>
#include <unistd.h>

//to get the length of the string
int ft_strlen(char *s)
{
	int i =0;
	while (s[i])
		i++;
	return i;
}

//to check if the number of parantheses are balanced in the string
int is_balanced(char *str)
{
	int balance = 0;
	int i = 0;
	int len = ft_strlen(str);

	while (i < len)
	{
		if (str[i] == '(')
			balance++;
		else if (str[i] == ')')
		{
			balance--;
			if (balance < 0)
				return 0;
		}
		i++;
	}
	return (balance == 0);
}

void ft_rip(char *s, int *min_rmv, int index, int current_rmv, int step)
{
	int i;
	char saved; 

	//if they have removed more than the original length of the string, return false
	if (current_rmv > *min_rmv)
		return ;

	//let's check if the string being passed is balance, if so we will try to set the minimum removable amount based on the step
	if (is_balanced(s))
	{
		if (step == 1 && current_rmv < *min_rmv)
			*min_rmv = current_rmv;
		else  if (step == 2 && current_rmv == *min_rmv)
		{
			write(1, s, ft_strlen(s));
			write(1, "\n", 1);
			return ;
		}
	}

//in this part, we are trying to do backtracking 'Core'
//if we find the  paranthesis we will try to replace that with a space first , basically an attempt to remove that 
	i = index; 
	while (s[i])
	{
		if (s[i] == '(' || s[i] == ')')
		{
			saved = s[i];
			s[i] = ' ';

			ft_rip(s, min_rmv, i + 1, current_rmv + 1, step);
			s[i] = saved;
		}
		i++;
	}

}

int main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return 1; 

	int i = 0;
	//we are trying to get the number of () and if it is not a paranthesis in the string, error
	while (av[1][i])
	{
		if (av[1][i] != '(' && av[1][i] != ')')
			return 1;
		i++;
	}

	//we will set the minimum number of removable to be the length of the string 
	int min_rmv = ft_strlen(av[1]);

	//step is set to 1 -> to find the possible sets first
	ft_rip(av[1], &min_rmv, 0, 0, 1);

	//2 to print out the sets
	ft_rip (av[1], &min_rmv, 0, 0, 2);

	return 0;
}
