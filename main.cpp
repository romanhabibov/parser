#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"

int main()
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
	//test_parser_exception("1+(12+34)/(56-56)\0", "Zero division\0");
	test_parser_exception("((1+2)+", "Incorrect bracket sequence\0");
	test_parser_exception("(1+2)+1)", "Incorrect bracket sequence\0");
	test_parser_exception("1/0", "Zero division\0");

	printf("***Recover from file***\n\n");
	FILE* test_file = fopen("test.txt", "w");
	test_print(test_file, "100\0", 100);
	test_file = fopen("test.txt", "w");
	test_print(test_file, "1+1\0", 2);
	test_file = fopen("test.txt", "w");
	test_print(test_file, "(12+34)*(56-78)\0", -1012);
	test_file = fopen("test.txt", "w");
	test_print(test_file, "4/2/2", 1);
	test_file = fopen("test.txt", "w");
	test_print(test_file, "(((123+45/5)+(67*8))*9)\0", 6012);

	getch();
	return 0;
}
