#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

int main()
{
	char command[6];
	printf("help - information about instructions\n");
	printf("run - interactive interpreter mode\n");
	printf("test - run the tests\n");
	printf("exit - stop the program\n\n");
	while(1)
	{
		printf("Type instruction\n");
		gets(command);
		if ((command[0] == 'h') && (command[1] == 'e') && (command[2] == 'l') && (command[3] == 'p') && (command[4] == '\0'))
		{
			printf("run - interactive interpreter mode\n");
			printf("test - run the tests\n");
			printf("exit - stop the program\n\n");
			continue;
		}
		else if ((command[0] == 'r') && (command[1] == 'u') && (command[2] == 'n') && (command[3] == '\0'))
		{
			int size = 100;
			cur_ptr = (char*)malloc(size);
			char buf_char = getchar();
			int i = 0;
			while (buf_char != '\n')
			{
				if (((i + 1) / size) > 0)
				{
					size = i + 1;
					cur_ptr = (char*)realloc(cur_ptr, size);
				}
				cur_ptr[i] = buf_char;
				i++;
				buf_char = getchar();
			}
			cur_ptr[i] = '\0';
			node_of_bin_tree* tree = create_tree();
			printf("%d\n\n", calculate(tree));
			free(cur_ptr - i);
			continue;
		}
		else if ((command[0] == 't') && (command[1] == 'e') && (command[2] == 's') && (command[3] == 't') && (command[4] == '\0'))
		{
			printf("***Parsing***\n\n");
			test_parser("100\0", 100);
			test_parser("1+1\0", 2);
			test_parser("(12+34)*(56-78)\0", -1012);
			test_parser("4/2/2", 1);
			test_parser("(((123+45/5)+(67*8))*9)\0", 6012);

			printf("***Exceptions***\n\n");
			test_parser_exception("()\0", "Incorrect symbol\0");
			test_parser_exception("(1+)\0", "Incorrect symbol\0");
			test_parser_exception("1+a\0", "Incorrect symbol\0");
			test_parser_exception("((1+2)+", "Incorrect bracket sequence\0");
			test_parser_exception("(1+2)+1)", "Incorrect bracket sequence\0");
			test_parser_exception("1/0", "Zero division\0");

			printf("***Recover from file***\n\n");
			FILE* test_file = fopen("test.txt", "w");
			test_print_recover(test_file, "100\0", 100);
			test_file = fopen("test.txt", "w");
			test_print_recover(test_file, "1+1\0", 2);
			test_file = fopen("test.txt", "w");
			test_print_recover(test_file, "(12+34)*(56-78)\0", -1012);
			test_file = fopen("test.txt", "w");
			test_print_recover(test_file, "4/2/2", 1);
			test_file = fopen("test.txt", "w");
			test_print_recover(test_file, "(((123+45/5)+(67*8))*9)\0", 6012);
			continue;
		}
		else if ((command[0] == 'e') && (command[1] == 'x') && (command[2] == 'i') && (command[3] == 't') && (command[4] == '\0'))
			break;
		else
		{
			printf("unknown instruction\n");
			continue;
		}
	}
	getch();
	return 0;
}
