#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
#include "Binary_tree.h"
#include "AVL_TREES.h"

using namespace std;

random_device rd;
mt19937 gen(rd());
mt19937 gen_(chrono::system_clock::now().time_since_epoch().count());


int biggest_elem_avl(Avl_Node* a) {
	int val = a->val;
	//Avl_Node* temp = a.get_root();
	if (a->childs[1] != nullptr) {
		a = a->childs[1];
		val = biggest_elem_avl(a);
	}
	return val;
}



list<int> nearly_ordered(list<int> a, int swaps) {
	list<int> nearly_ordered_list;
	auto it = a.begin();
	uniform_int_distribution<int> dist(*it, a.size());
	for (int i = 0; i < a.size(); i++) {
		if (swaps > 0) {
			nearly_ordered_list.push_back(dist(gen));
			swaps--;
			continue;
		}
		nearly_ordered_list.push_back(i);
	}
	return nearly_ordered_list;
}



int ordered_bst_biggest_element(Binary_Tree a) {
	return a.find_max(a.get_root()) + 1;
}


template <typename T>
int  binary_search(T* root,int val) {
	if (root != nullptr && val == root->val) {
		return root->val;
	}
	else if (val > root->val && root->childs[1]!=nullptr) {
		return binary_search(root->childs[1], val);
	}
	else if (val < root->val && root->childs[0]!=nullptr ) {
		return binary_search(root->childs[0], val);
	}
	else{
		return -1;
	}

}

int main() {
	int tests_count, array_size,benchmark_stop;
	cout << "Please input tests count,begining size of the tree and the size where you want to stop benchmark " << endl;
	cin >> tests_count >> array_size>> benchmark_stop;

//	int array_size;
	string result_file_insert,result_file_search;
	int itterations;
	cout << "Please input results insert file name with the extension csv" << endl;
	cin >> result_file_insert;
	cout << "Please input file name for search results with the extension csv " << endl;
	cin >> result_file_search;
	cout << "Please input the itteration count" << endl;
	cin >> itterations;

	ofstream  for_result_insert;
	for_result_insert.open(result_file_insert);
	string desc_insert = "size , BST_random_insert , Bst_ordered_insert , Bst_nearlyordered_insert , Avl_random_insert , Avl_ordered_insert, Avl_nearlyordered_insert ";
	for_result_insert << desc_insert << endl;

	ofstream for_result_search;
	for_result_search.open(result_file_search);
	string desc_search = "size , BST_random_search_included, BST_ordered_search_included ,BST_nearlyordered_included, Avl_random_search_included, Avl_ordered_search_included ,Avl_nearlyordered_included, BST_random_search_excluded, BST_ordered_search_excluded ,BST_nearlyordered_excluded,  Avl_random_search_excluded, Avl_ordered_search_excluded ,Avl_nearlyordered_excluded ";
	for_result_search << desc_search << endl;


	for (int i = 0; i < tests_count; i++) {
		chrono::nanoseconds Bst_random_insert(0);
		chrono::nanoseconds Bst_ordered_insert(0);
		chrono::nanoseconds Bst_nearlyordered_insert(0);
		chrono::nanoseconds Avl_random_insert(0);
		chrono::nanoseconds Avl_ordered_insert(0);
		chrono::nanoseconds Avl_nearly_ordered_insert(0);
	
		chrono::nanoseconds Bst_random_search_included(0);
		chrono::nanoseconds Bst_ordered_search_included(0);
		chrono::nanoseconds Bst_nearlyordered_search_included(0);
		chrono::nanoseconds Avl_random_search_included(0);
		chrono::nanoseconds Avl_ordered_search_included(0);
		chrono::nanoseconds Avl_nearly_search_included(0);

		chrono::nanoseconds Bst_random_search_excluded(0);
		chrono::nanoseconds Bst_ordered_search_excluded(0);
		chrono::nanoseconds Bst_nearlyordered_search_excluded(0);
		chrono::nanoseconds Avl_random_search_excluded(0);
		chrono::nanoseconds Avl_ordered_search_excluded(0);
		chrono::nanoseconds Avl_nearly_search_excluded(0);
		cout << "begining_size  " << array_size << endl;
		if (array_size > benchmark_stop) return 0;
		for_result_insert << array_size << ",  ";
		for_result_search << array_size << ",   ";


		for (int k = 0; k < itterations; k++) {
			list<int> bst_ordered;
			for(int i =0; i<array_size;i++){
				bst_ordered.push_back(i);
			}
			Binary_Tree b(bst_ordered);
			int elem = ordered_bst_biggest_element(b);
			auto start_bst_ordered = chrono::steady_clock::now();
			b.insert_elem(elem);
			auto end_bst_ordered = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_bst_ordered(end_bst_ordered - start_bst_ordered);
			Bst_ordered_insert += time_taken_bst_ordered;
			
			list<int> random_list;
			uniform_int_distribution<int> dist(0, array_size);
			for (int i = 0; i < array_size; i++) {
				random_list.push_back(dist(gen));
			}
			Binary_Tree random_bst (random_list);
			auto start_bst_random = chrono::steady_clock::now();
			random_bst.insert_elem(elem);
			auto end_bst_random = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_bst_random(end_bst_random - start_bst_random);
			Bst_random_insert+=time_taken_bst_random;

			list<int> nearly_ordered_list = nearly_ordered(bst_ordered,array_size*0.30);
			Binary_Tree nearly_ordered_bst(nearly_ordered_list);
			auto start_bst_nearlyordered = chrono::steady_clock::now();
			nearly_ordered_bst.insert_elem(elem);
			auto end_bst_nearlyordered = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_bst_nearlyordered(end_bst_nearlyordered - start_bst_nearlyordered);
			Bst_nearlyordered_insert += time_taken_bst_nearlyordered;
			
			Avl_Tree ordered_avl;
			for (int i = 0; i < array_size; i++) {
				ordered_avl.insert(i);
			}
			auto start_avl_ordered = chrono::steady_clock::now();
			ordered_avl.insert(array_size);
			auto end_avl_ordered = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_avl_ordered(end_avl_ordered - start_avl_ordered);
			Avl_ordered_insert += time_taken_avl_ordered;

			Avl_Tree random_avl;
			for (int i = 0; i < array_size; i++) {
				random_avl.insert(dist(gen));
			}
			auto start_avl_random = chrono::steady_clock::now();
			random_avl.insert(array_size + 1);
			auto end_avl_random = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_avl_random(end_avl_random - start_avl_random);
			Avl_random_insert += time_taken_avl_random;

			Avl_Tree nearly_ordered;
			int swaps = array_size * 0.2;
			for (int i = 0; i < array_size; i++) {
				if (swaps > 0) {
					nearly_ordered.insert(dist(gen));
					swaps--;
					continue;
				}
				nearly_ordered.insert(i);
			}
			auto start_avl_nearly_ordered = chrono::steady_clock::now();
			nearly_ordered.insert(array_size + 2);
			auto end_avl_nearly_ordered = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_avl_nearlyordered(end_avl_nearly_ordered - start_avl_nearly_ordered);
			Avl_nearly_ordered_insert += time_taken_avl_nearlyordered;

			//search

			auto start_binary_search_ordered = chrono::steady_clock::now();
			binary_search(b.get_root(), array_size);
			auto end_binary_search_ordered = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_binary_search_ordered_included(end_binary_search_ordered - start_binary_search_ordered);
			Bst_ordered_search_included +=time_taken_binary_search_ordered_included;

			auto start_binary_search_random = chrono::steady_clock::now();
			binary_search(random_bst.get_root(), array_size);
			auto end_binary_search_random = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_binary_search_random_included(end_binary_search_random - start_binary_search_random);
			Bst_random_search_included +=time_taken_binary_search_random_included;

			auto start_binary_search_nearlyordered = chrono::system_clock::now();
			binary_search(nearly_ordered_bst.get_root(), array_size);
			auto end_binary_search_nearlyordered = chrono::system_clock::now();
			chrono::nanoseconds time_taken_binary_search_nearlyordered_included(end_binary_search_nearlyordered - start_binary_search_nearlyordered);
			Bst_nearlyordered_search_included += time_taken_binary_search_nearlyordered_included;
		
			auto start_binary_search_ordered_avl = chrono::steady_clock::now();
			binary_search(ordered_avl.get_root(), array_size);
			auto end_binary_search_ordered_avl = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_binary_search_ordered_avl_included(end_binary_search_ordered_avl - start_binary_search_ordered_avl);
			Avl_ordered_search_included += time_taken_binary_search_ordered_avl_included;

			
			int elem_avl = biggest_elem_avl(random_avl.get_root());
			auto start_binary_search_random_avl = chrono::steady_clock::now();
			binary_search(random_avl.get_root(), elem_avl);
			auto end_binary_search_random_avl = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_binary_search_random_avl_included(end_binary_search_random_avl - start_binary_search_random_avl);
			Avl_random_search_included += time_taken_binary_search_random_avl_included;

			auto start_binary_search_nearlyordered_avl = chrono::steady_clock::now();
			binary_search(nearly_ordered.get_root(), array_size);
			auto end_binary_search_nearlyordered_avl = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_binary_search_nearlyordered_avl_included(end_binary_search_nearlyordered_avl - start_binary_search_nearlyordered_avl);
			Avl_nearly_search_included += time_taken_binary_search_nearlyordered_avl_included;


			auto start_binary_search_ordered_excluded = chrono::steady_clock::now();
			binary_search(b.get_root(), INT_MAX);
			auto end_binary_search_ordered_excluded = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_binary_search_ordered_excluded(end_binary_search_ordered_excluded - start_binary_search_ordered_excluded);
			Bst_ordered_search_excluded += time_taken_binary_search_ordered_excluded;

			auto start_binary_search_random_excluded = chrono::steady_clock::now();
			binary_search(random_bst.get_root(), INT_MAX);
			auto end_binary_search_random_excluded = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_binary_search_random_excluded(end_binary_search_random_excluded - start_binary_search_random_excluded);
			Bst_random_search_excluded += time_taken_binary_search_random_excluded;

			auto start_binary_search_nearly_ordered_excluded = chrono::steady_clock::now();
			binary_search(nearly_ordered_bst.get_root(), INT_MAX);
			auto end_binary_search_nearly_ordered_excluded = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_binary_search_nearly_ordered_excluded(end_binary_search_nearly_ordered_excluded - start_binary_search_nearly_ordered_excluded);
			Bst_nearlyordered_search_excluded += time_taken_binary_search_nearly_ordered_excluded;


			auto start_avl_search_ordered_excluded = chrono::steady_clock::now();
			binary_search(ordered_avl.get_root(), INT_MAX);
			auto end_avl_search_ordered_excluded = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_avl_search_ordered_excluded(end_avl_search_ordered_excluded-start_avl_search_ordered_excluded);
			Avl_ordered_search_excluded += time_taken_avl_search_ordered_excluded;

			auto start_avl_search_random_excluded = chrono::steady_clock::now();
			binary_search(random_avl.get_root(), INT_MAX);
			auto end_avl_search_random_excluded = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_avl_search_random_excluded(end_avl_search_random_excluded - start_avl_search_random_excluded);
			Avl_random_search_excluded += time_taken_avl_search_random_excluded;

			auto start_avl_search_nearly_ordered_excluded = chrono::steady_clock::now();
			binary_search(nearly_ordered.get_root(), INT_MAX);
			auto end_avl_search_nearly_ordered_excluded = chrono::steady_clock::now();
			chrono::nanoseconds time_taken_avl_search_nearlyodered_excluded(end_avl_search_nearly_ordered_excluded - start_avl_search_nearly_ordered_excluded);
			Avl_nearly_search_excluded += time_taken_avl_search_nearlyodered_excluded;



		}
		for_result_insert << Bst_random_insert.count() / itterations << ",    ";
		for_result_insert << Bst_ordered_insert.count() / itterations << ",     ";
		for_result_insert << Bst_nearlyordered_insert.count() / itterations << ",   ";
		for_result_insert << Avl_random_insert.count() / itterations << ",    ";
		for_result_insert << Avl_ordered_insert.count() / itterations << ",    ";
		for_result_insert << Avl_nearly_ordered_insert.count() / itterations << ",   ";
		for_result_insert << endl;
	

		for_result_search << Bst_random_search_included.count() / itterations << ",   ";
		for_result_search << Bst_ordered_search_included.count() / itterations << ",   ";
		for_result_search << Bst_nearlyordered_search_included.count() / itterations << ",  ";
		for_result_search << Avl_random_search_included.count() / itterations << ",  ";
		for_result_search << Avl_ordered_search_included.count() / itterations << ",  ";
		for_result_search << Avl_nearly_search_included.count() / itterations << ",  ";

		for_result_search << Bst_random_search_excluded.count() / itterations << ",   ";
		for_result_search << Bst_ordered_search_excluded.count() / itterations << ",   ";
		for_result_search << Bst_nearlyordered_search_excluded.count() / itterations << ", ";
		for_result_search << Avl_random_search_excluded.count() / itterations << ",  ";
		for_result_search << Avl_ordered_search_excluded.count() / itterations << ",  ";
		for_result_search << Avl_nearly_search_excluded.count() / itterations << ",  ";
		for_result_search << endl;

		
		cout << "Time taken for  ordered insert is " << Bst_ordered_insert.count()/itterations << endl;
		cout << "Time taken for random list is  " << Bst_random_insert.count() / itterations << endl;
		cout << "Time taken for nearly ordered " << Bst_nearlyordered_insert.count() / itterations << endl;
		
		if (array_size < 100) array_size += 10;
		else array_size += 400;
	}
	
	
}