#pragma once
#include <stdio.h>

extern char* cur_ptr;
extern int error_counter;

struct node_of_bin_tree
{
	char operation_ = 'v';
	int val_ = 0;
	node_of_bin_tree* left_child_ = NULL;
	node_of_bin_tree* right_child_ = NULL;
};

//creation and destruction
node_of_bin_tree* create_leaf(int val); //Returns pointer to ending node of tree with value. Left and right childrens are NULL. Function allocates memory. Function is used in parser-functions.
node_of_bin_tree* create_node(char operation, node_of_bin_tree* left_child, node_of_bin_tree* right_child); //Returns pointer to node of tree with operation. Left and right childrens aren't NULL. Its can be other nodes or leafs. Function allocates memory. Function is used in parser-functions.
node_of_bin_tree* create_tree(); //Make tree with exeption in cur_ptr. Function uses parser-functions.
node_of_bin_tree* recover_tree(FILE* file); //Creates tree from file.
void destruct_node(node_of_bin_tree* tree); //Frees memory of one node.
void destruct_tree(node_of_bin_tree* tree); //Frees memory of all tree.

//print
void print_tree(FILE* file, node_of_bin_tree* node); //Saves tree to file.
int calculate(node_of_bin_tree* tree, unsigned int level = 0); //Returns the value of the expression given by the tree. It use "destruct_node".

//parser
node_of_bin_tree* getN();
node_of_bin_tree* getExpr();
node_of_bin_tree* getProd();
node_of_bin_tree* getTerm();

//tests
void test_parser(const char* string, int result);
void test_parser_exception(const char string[], const char error[]);
void test_print_recover(FILE* file, const char string[], int result);

void set_error(const char* error_message);
