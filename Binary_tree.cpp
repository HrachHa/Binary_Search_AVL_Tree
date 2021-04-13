#include "Binary_tree.h"


Binary_Tree::Binary_Tree(list<int> a) : root(new Node(a.front())), left(nullptr), right(nullptr), height(0) {

	a.pop_front();
	
	list_to_binarytree(a, root);

};


void Binary_Tree::insert_elem(int val) {

	Node* leaf = leaf_node(root, val);
	if (val >= leaf->val && leaf->childs[1] == nullptr) {
		leaf->childs[1] = new Node(val);
	}
	else if (val < leaf->val && leaf->childs[0] == nullptr) {
		leaf->childs[0] = new Node(val);
	}

}



Node* Binary_Tree::leaf_node(Node *root, int val) {
	while (root->childs[0] != nullptr || root->childs[1] != nullptr) {

		while(val >= root->val && root->childs[1]!=nullptr){

			root = root->childs[1];
		}
		while(val< root->val && root->childs[0]!=nullptr) {
			root = root->childs[0];
		}
		
			return root;
		
		}
	return root;
};

Node* Binary_Tree::get_root() {
	return root;
}

void Binary_Tree::list_to_binarytree(list<int> a, Node* root)
{
	for (auto i : a) {
		Binary_Tree::insert_elem(i);
	}
}

void Binary_Tree::print2D(Node* root)
{
	Binary_Tree::print_tree(root, 0);
}

void Binary_Tree::print_tree(Node* root,int space)
{

	if (root == NULL)
		return;
	space += 10;
	print_tree(root->childs[1], space);
	cout << endl;
	for (int i = 10; i < space; i++)
		cout << " ";
	cout << root->val << "\n";
	print_tree(root->childs[0], space);
}

int Binary_Tree::find_max(Node * root) {
	int val = root->val;
	if (root->childs[1] != nullptr) {
		root = root->childs[1];
		val = find_max(root);
	}
	return val;
}
