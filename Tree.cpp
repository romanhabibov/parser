#include "Tree.h"
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* cur_ptr = NULL;
int error_counter = 0;

void set_error(const char* errorMessage)
{
	error_counter++;
	printf(errorMessage);
}

node_of_bin_tree* create_node(char operation, node_of_bin_tree* left_child, node_of_bin_tree* right_child)
{
	node_of_bin_tree* result = (node_of_bin_tree*)malloc(sizeof(node_of_bin_tree));
	result->operation_ = operation;
	result->left_child_ = left_child;
	result->right_child_ = right_child;
	return result;
}

node_of_bin_tree* create_leaf(int val)
{
	node_of_bin_tree* result = create_node('v', NULL, NULL);
	result->val_ = val;
	return result;
}

node_of_bin_tree* create_tree()
{
	node_of_bin_tree* result = getExpr();
	if (!error_counter)
		if (*cur_ptr == '\0')
			return result;
		else if (*cur_ptr == '(')
			set_error("Incorrect bracket sequence\n");
		else if (*cur_ptr == ')')
			set_error("Incorrect bracket sequence\n");
		else
			set_error("Incorrect symbol\n");
	error_counter = 0;
	destruct_tree(result);
	return NULL;
}

void destruct_node(node_of_bin_tree* tree)
{
	assert(tree != NULL);
	free(tree);
}

void destruct_tree(node_of_bin_tree* tree)
{
	if (!tree)
		return;
	destruct_tree(tree->left_child_);
	destruct_tree(tree->right_child_);
	free(tree);
}

void print_tree(FILE* file, node_of_bin_tree* tree)
{
	assert(tree != NULL);
	fprintf(file, "(");
	if (tree->left_child_)
	{
		fprintf(file, "%c", tree->operation_);
		print_tree(file, tree->left_child_);
		print_tree(file, tree->right_child_);
	}
	if (tree->operation_ == 'v')
	{
		fprintf(file, "%d", tree->val_);
		fprintf(file, "~");
	}
	fprintf(file, ")");
}

int calculate(node_of_bin_tree* tree, unsigned int level)
{
	if (!tree)
	{
		printf("Not initialized\n");
		return 0;
	}
	if (tree->operation_ == 'v')
		return tree->val_;
	calculate(tree->left_child_, level + 1);
	calculate(tree->right_child_, level + 1);
	switch (tree->operation_)
	{
	case '+':
		tree->val_ = tree->left_child_->val_ + tree->right_child_->val_;
		destruct_node(tree->left_child_);
		destruct_node(tree->right_child_);
		break;
	case '-':
		tree->val_ = tree->left_child_->val_ - tree->right_child_->val_;
		destruct_node(tree->left_child_);
		destruct_node(tree->right_child_);
		break;
	case '*':
		tree->val_ = tree->left_child_->val_ * tree->right_child_->val_;
		destruct_node(tree->left_child_);
		destruct_node(tree->right_child_);
		break;
	case '/':
		if (tree->right_child_->val_)
		{
			tree->val_ = tree->left_child_->val_ / tree->right_child_->val_;
		}
		else
		{
			set_error("Zero division\n");
			tree->val_ = tree->left_child_->val_ / 1;
		}
		destruct_node(tree->left_child_);
		destruct_node(tree->right_child_);
		break;
	}
	if (!error_counter)
		return tree->val_;
	else
	{
		if (level == 0)
		{
			destruct_node(tree);
			error_counter = 0;
		}
		return 0;
	}
}

node_of_bin_tree* recover_tree(FILE* file)
{
	if (file)
	{
		fgetc(file);
		char buf_char = fgetc(file);
		node_of_bin_tree* result;
		if ((buf_char == '+') || (buf_char == '-') || (buf_char == '*') || (buf_char == '/'))
		{
			result = (node_of_bin_tree*)malloc(sizeof(node_of_bin_tree));
			result->operation_ = buf_char;
			result->left_child_ = recover_tree(file);
			result->right_child_ = recover_tree(file);
			fgetc(file);
			return result;
		}
		else
		{
			int val = 0;
			int counter = 0;
			while (('0' <= buf_char) && (buf_char <= '9'))
			{
				counter++;
				val *= 10;
				val += buf_char - '0';
				buf_char = fgetc(file);
			}
			result = create_leaf(val);
			fgetc(file);
			return result;
		}
	}
	else
	{
		printf("Can't open file\n");
		return NULL;
	}
}

node_of_bin_tree* getN()
{
	int val = 0;
	node_of_bin_tree* result;
	int counter = 0;
	while (('0' <= *cur_ptr) && (*cur_ptr <= '9'))
	{
		counter++;
		val *= 10;
		val += *cur_ptr - '0';
		cur_ptr++;
	}
	if (!counter)
		set_error("Incorret symbol\n");
	result = create_leaf(val);
	return result;
};

node_of_bin_tree* getExpr()
{
	node_of_bin_tree* lhs = getProd();
	while ((*cur_ptr == '+') || (*cur_ptr == '-'))
	{
		char bin_op = *cur_ptr++;
		node_of_bin_tree* rhs = getProd();
		node_of_bin_tree* temporary_lhs;
		if (bin_op == '+')
			temporary_lhs = create_node('+', lhs, rhs);
		else
			temporary_lhs = create_node('-', lhs, rhs);
		lhs = temporary_lhs;
	}
	return lhs;
}

node_of_bin_tree* getProd()
{
	node_of_bin_tree* lhs = getTerm();
	while ((*cur_ptr == '*') || (*cur_ptr == '/'))
	{
		char bin_op = *cur_ptr++;
		node_of_bin_tree* rhs = getTerm();
		node_of_bin_tree* temporary_lhs;
		if (bin_op == '*')
			temporary_lhs = create_node('*', lhs, rhs);
		else
			temporary_lhs = create_node('/', lhs, rhs);
		lhs = temporary_lhs;
	}
	return lhs;
}

node_of_bin_tree* getTerm()
{
	node_of_bin_tree* result;
	if (*cur_ptr == '(')
	{
		cur_ptr++;
		result = getExpr();
		if (*cur_ptr == ')')
			cur_ptr++;
		else
			set_error("Incorrect bracket sequence\n");
		return result;
	}
	else
		result = getN();
	return result;
}

void test_parser(const char* string, int result)
{
	size_t length = strlen(string);
	cur_ptr = (char*)malloc(sizeof(char) * length + 1);
	for (size_t i = 0; i < length; i++)
	{
		cur_ptr[i] = string[i];
	}
	cur_ptr[length] = '\0';
	node_of_bin_tree* tree = create_tree();
	if (calculate(tree) == result)
	{
		printf("%s == %d\n", string, result);
		printf("ok\n\n");
	}
	else
	{
		printf("%s != %d\n", string, result);
		printf("not ok\n\n");
	}
	cur_ptr -= length;
	free(cur_ptr);
}

void test_parser_exception(const char string[], const char error[])
{
	size_t length = strlen(string);
	cur_ptr = (char*)malloc(sizeof(char) * length + 1);
	for (unsigned int i = 0; i < length; i++)
	{
		cur_ptr[i] = string[i];
	}
	cur_ptr[length] = '\0';
	node_of_bin_tree* tree = create_tree();
	int buf = calculate(tree);
	printf("if there was an error message - ok\n\n");
	cur_ptr -= length - strlen(cur_ptr);
	free(cur_ptr);
}

void test_print_recover(FILE* file, const char string[], int result)
{
	size_t length = strlen(string);
	cur_ptr = (char*)malloc(sizeof(char) * length + 1);
	for (size_t i = 0; i < length; i++)
	{
		cur_ptr[i] = string[i];
	}
	cur_ptr[length] = '\0';
	node_of_bin_tree* tree = create_tree();
	cur_ptr -= length;
	free(cur_ptr);
	print_tree(file, tree);
	destruct_tree(tree);
	fclose(file);
	file = fopen("test.txt", "r");
	tree = recover_tree(file);
	if (calculate(tree) == result)
	{
		printf("%s == %d\n", string, result);
		printf("ok\n\n");
	}
	else
	{
		printf("%s != %d", string, result);
		printf("not ok\n\n");
	}
}
