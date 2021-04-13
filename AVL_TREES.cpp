#include "AVL_TREES.h"

Avl_Tree::Avl_Tree():root(nullptr)
{
}

Avl_Node* Avl_Tree::get_root()
{
	return root;
}

int Avl_Tree::depth_of_tree(Avl_Node* root)
{
	if (root == nullptr)
		return 0;
	else {

		int left = depth_of_tree(root->childs[0]);

		int right = depth_of_tree(root->childs[1]);

		return std::max(left, right) + 1;
	}

	
}

void Avl_Tree::insert(int val)
{
	if (this->root == nullptr) {
		root = new Avl_Node(val);
		root->height = 1;
		return;
	}
	Avl_Node* leaf = leaf_node(root, val);
	if (val >= leaf->val && leaf->childs[1] == nullptr) {
		leaf->childs[1] = new Avl_Node(val);
	}
	else if (val < leaf->val && leaf->childs[0] == nullptr) {
		leaf->childs[0] = new Avl_Node(val);
	}

	if (balance(this->root) > 1 || balance(this->root) < 1) {
		this->root = balance_tee(this->root);
	}
}

Avl_Node* Avl_Tree::leaf_node(Avl_Node* root,int val)
{
	while (root->childs[0] != nullptr || root->childs[1] != nullptr) {
		
		while (val >= root->val && root->childs[1] != nullptr) {
			
			root = root->childs[1];
		}
		while (val < root->val && root->childs[0] != nullptr) {
			root = root->childs[0];
		}
		return root;

	}
return root;

}

void Avl_Tree::print_tree(Avl_Node* root, int space)
{

	if (root == NULL)
		return;
	space += 10;
	print_tree(root->childs[1], space);
	cout << endl;
	for (int i = 10; i < space; i++)
		cout << " ";
	cout <<"Value " <<root->val <<"  height  " <<root->height<<  "\n";
	print_tree(root->childs[0], space);
}

void Avl_Tree::print2D(Avl_Node*)
{
	Avl_Tree::print_tree(root, 0);
}

int Avl_Tree::balance(Avl_Node* root)
{

	if (root->childs[0] != nullptr || root->childs[1] != nullptr) {

		int  right = depth_of_tree(root->childs[1]);

		int left = depth_of_tree(root->childs[0]);
		
		return left - right;
	}
	return 0;
}

Avl_Node*  Avl_Tree::rotate_right(Avl_Node* node)
{

	Avl_Node* new_subtree_root = node->childs[0];

	node->childs[0] = new_subtree_root->childs[1];

	new_subtree_root->childs[1] = node;

	// fix( node) and fix(new subbtree)
	node->height = depth_of_tree(node);
	new_subtree_root->height = depth_of_tree(new_subtree_root);
	
	return new_subtree_root;
}

Avl_Node* Avl_Tree::rotate_left(Avl_Node* node)
{
	Avl_Node* new_subtree_root = node->childs[1];
	node->childs[1] = new_subtree_root->childs[0];
	new_subtree_root->childs[0] = node;

	// fix heights
	node->height = depth_of_tree(node);
	new_subtree_root->height = depth_of_tree(new_subtree_root);
	
	
	return new_subtree_root;

	
}

Avl_Node* Avl_Tree::balance_tee(Avl_Node* node)
{
	node->height = depth_of_tree(node);
	if (balance(node) > 1) {
		if (balance(node->childs[0]) < 0) {
			node->childs[0] = rotate_left(node->childs[0]);
		}
		return rotate_right(node);
	}
	if (balance(node) < -1) {
		if (balance(node->childs[1]) > 0) {
			node->childs[1] = rotate_right(node->childs[1]);
		}
		return rotate_left(node);
	}

	return node;
}
