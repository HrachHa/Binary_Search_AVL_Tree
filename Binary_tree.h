#pragma once
#ifndef BINARY_TREE
#define BINARY_TREE
#include <list>
#include <vector>
#include <iostream>
using namespace std;


struct Node {
	int val;
	vector<Node*> childs;
	//Node* parent;
	Node(int val_) : val(val_),childs(2,nullptr) {};

};

class Binary_Tree{
private:
	Node* root;
	Node* left;
	Node* right;
	Node* leaf;
	int height;
	
public:
	Binary_Tree();
	Binary_Tree(list<int> a) ;
	

	void insert_elem(int);
	Node* get_root();
	Node* leaf_node(Node *, int );
	int find_max(Node * root);
	void list_to_binarytree(list<int>,Node*);

	void print_tree(Node* root,int);
	void print2D(Node*);
};


#endif // !BINARY_TREE

