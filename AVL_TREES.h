#pragma once
#ifndef AVL_TREE
#define AVL_TREE
#include <vector>
#include <algorithm>
#include <iostream>
//#include "Binary_tree.h"
using namespace std;

struct Avl_Node {
	int val;
	vector<Avl_Node*> childs;
	int height;
	//int left_height;
	///int right_height;
	Avl_Node(int v) : val(v), childs(2, nullptr) ,height(0){};


};


class Avl_Tree {
private:
	Avl_Node* root;
	int height;
public:
	Avl_Tree();
	Avl_Node* get_root();
	int depth_of_tree(Avl_Node* root);
	void insert(int);
	Avl_Node* leaf_node(Avl_Node*,int);
	void print_tree(Avl_Node* root, int);
	void print2D(Avl_Node*);
	int  balance(Avl_Node* root);
	Avl_Node* rotate_right(Avl_Node* node);
	Avl_Node*  rotate_left(Avl_Node* node);
	Avl_Node* balance_tee(Avl_Node* node);

};

#endif // !AVL_TREE
