#pragma once

struct node_of_bin_tree;

//creation and destruction
node_of_bin_tree* create_leaf(int val); //Returns pointer to ending node of tree with value. Left and right childrens are NULL. Function allocates memory. Function is used in parser-functions.
node_of_bin_tree* create_node(char operation, node_of_bin_tree* left_child, node_of_bin_tree* right_child);//Returns pointer to node of tree with operation. Left and right childrens aren't NULL. Its can be other nodes or leafs. Function allocates memory. Function is used in parser-functions.
node_of_bin_tree* create_tree(); //Make tree with exeption in cur_ptr. Function uses parser-functions.
node_of_bin_tree* recover_tree(FILE* file);//Creates tree from file.
void destruct_node(node_of_bin_tree* tree);//Frees memory of one node.
void destruct_tree(node_of_bin_tree* tree);//Frees memory of all tree. Assigns NULL to the tree.

//print
void print_tree(FILE* file, node_of_bin_tree* node);//Saves tree to file.
int calculate(node_of_bin_tree* tree, unsigned int level);//Returns the value of the expression given by the tree. It use "destruct_node". Assigns NULL to the tree.

//parser
node_of_bin_tree* getN();
node_of_bin_tree* getExpr();
node_of_bin_tree* getProd();
node_of_bin_tree* getTerm();

//tests
void test_parser(const char* string, int result);
void test_parser_exception(const char string[], const char error[]);
void test_print(FILE* file, const char string[], int result);

void set_error(const char* error_message);
