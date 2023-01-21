#include<stdio.h>
#include<stdlib.h>
#include "Stack.h"

int get_number_of_strings(void);
Boolean get_is_balanced(void);
Boolean get_match(char open, char close);
void clear_keyboard_buffer(void);
Boolean is_valid(char c);

int main(int argc, char* argv[])
{
	int number_of_strings = get_number_of_strings();
	clear_keyboard_buffer();
	Boolean is_balanced;
	for (number_of_strings; number_of_strings > 0; number_of_strings--)
	{
		is_balanced = get_is_balanced();
		
		if (is_balanced == TRUE)
		{
			printf("Yes\n");
		}
		else
		{
			printf("No\n");
		}	
	}
}


int get_number_of_strings(void)
{
	int number_of_strings;
	int noc = scanf("%d", &number_of_strings);
	return number_of_strings;
}

Boolean get_is_balanced(void)
{
	STACK hStack = init_stack();
	Boolean instance_match;
	char char_entered;

	scanf("%c", &char_entered);

	while (char_entered != '\n' && is_valid(char_entered))
	{
		if (char_entered == '(' || char_entered == '[' || char_entered == '{')
		{
			stack_insert(hStack, char_entered);
		}
		
		else if (char_entered == ')' || char_entered == ']' || char_entered == '}')
		{
			if (stack_empty(hStack))
			{
				clear_keyboard_buffer();
				destroy_stack(&hStack);
				return FALSE;
			}

			else if (!(get_match(get_top(hStack), char_entered)))
			{				
				destroy_stack(&hStack);
				return FALSE;
			}
			stack_pop(hStack);
		}
		scanf("%c", &char_entered);
	}
	if (stack_empty(hStack) && char_entered == '\n')
	{
		destroy_stack(&hStack);
		return TRUE;
	}
	else
	{
		destroy_stack(&hStack);
		return FALSE;
	}
}

Boolean get_match(char open, char close)
{
	switch (open)
	{
		case '(':
			if (close == ')')
			{
				return TRUE;
			}
			break;

		case '[':
			if (close == ']')
			{
				return TRUE;
			}
			break;

		case '{':
			if (close == '}')
			{
				return TRUE;
			}
			break;
		default: 
			return FALSE;
	}
	return FALSE;
}

void clear_keyboard_buffer(void)
{
	char ch;
	scanf("%c", &ch);
	while (ch != '\n' && ch != '\0')
	{
		scanf("%c", &ch);
	}

}

Boolean is_valid(char c)
{
	if (c != '(' && c != '[' && c != '{' && c != ')' && c != ']' && c != '}')
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}



