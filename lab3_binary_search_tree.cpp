#include <iostream>
#include <algorithm> 
#include <stack>
#include <queue>
#include "lab3_binary_search_tree.hpp"

using namespace std;

BinarySearchTree::BinarySearchTree() {
	root = NULL;
	size = 0;
}

BinarySearchTree::~BinarySearchTree() {
	
	if (!root ) return;

	queue<TaskItem*> q;
	q.push(root);
	
	while (!q.empty()) {
		TaskItem* n = q.front();
		q.pop();

		if (n->left) q.push(n->left);
		if (n->right) q.push(n->right);

		delete n;
		n = NULL;
	}
	return;
}

unsigned int BinarySearchTree::get_size() const {
	return size;
}

BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if (size == 0) return BinarySearchTree::TaskItem(-1, "N/A");
	else if (!root->right) return *root;
	else {
		TaskItem* current = root;
		while (current->right)current = current->right;
		return BinarySearchTree::TaskItem(*current);
	}
	
}

BinarySearchTree::TaskItem BinarySearchTree::min() const {
	
	if (size == 0) 	return BinarySearchTree::TaskItem(-1, "N/A");
	else if (root->left == NULL) return *root;
	else {
		TaskItem* current = root;
		while (current->left != NULL) current = current->left;
		return BinarySearchTree::TaskItem(*current);
	}
	
}

unsigned int BinarySearchTree::height() const {
	return BinarySearchTree::get_node_depth(root);
}

void BinarySearchTree::print() const {
	if (size==0) return;
	
	stack<TaskItem*> s;
	s.push(root);
	while (!s.empty()) {
		TaskItem* curr = s.top(); s.pop();
		cout << curr->priority << ", "<<curr->description<<endl;
		if (curr->right)
			s.push(curr->right);
		if (curr->left)
			s.push(curr->left);
	}
}

bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	if (size == 0) return false;
	if (*root == val) return true;
	
	TaskItem* curr = root;
	
	while (curr) {
		if (*curr == val) return true;
		else if (curr->priority > val.priority) curr = curr->left;
		else curr = curr->right;
	}

	return false;
}

BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
	return root;
}

BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
	if (root) return &root;
	return NULL;
}

int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	if (!n) return -1;
	else return 1 + std::max(get_node_depth(n->left), get_node_depth(n->right));	
}

bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
	if (size == 0) {
		root = new TaskItem(val);
		size = size + 1;
		return true;
	} 
	if (exists(val)) return false;

	TaskItem* curr = root;
	
	while (curr) {
		if (curr->priority > val.priority)
		{
			if (curr->left) curr = curr->left;
			else {
				curr->left = new TaskItem(val);
				size = size + 1;
				return true;
			}
		}
		else {
			if (curr->right) curr = curr->right;
			else {
				curr->right = new TaskItem(val);
				size = size + 1;
				return true;
			}
		}
	}
	
}

bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
	if (size == 0) return false;
	if (!exists(val)) return false;
	if (size == 1 && *root == val) {
		delete root;
		root = NULL;
		size--;
		return true;
	}

	TaskItem* parent = NULL;
	TaskItem* curr = root;
	bool run = true;
	
	while (curr!=NULL && run==true) {
		if (*curr == val) run = false;
		else if (curr->priority > val.priority) {
			parent = curr;
			curr = curr->left;
		} else {
			parent = curr;
			curr = curr->right;
		}
	}

	if (curr->left == NULL && curr->right == NULL) { // Case 1: no children
		if (parent->left == curr) parent->left = NULL;
		else parent->right = NULL;

		delete curr;
		curr = NULL;
		size = size - 1;
		return true;

	} else if (curr->left && curr->right)  { // Case 2: both have children
		TaskItem* succe = curr->right;
		TaskItem* succeParent = curr;

		while (succe->left) {
			succeParent = succe;
			succe = succe->left;
		}

		if (curr != root) {
			if (curr == parent->left) {
				parent->left->priority = succe->priority;
				parent->left->description = succe->description;
				
				if (succeParent->right != succe) succeParent->left = succe->right;
				else succeParent->right = succe->right;
			} else {
				parent->right->priority = succe->priority;
				parent->right->description = succe->description;
				succeParent->left = succe->right;
			}
			
		} else {
			root->priority = succe->priority;
			root->description = succe->description;
			
			if (succeParent!=root) succeParent->left = succe->right;
			else succeParent->right = succe->right;			
		}

		succe->right = NULL;
		succe->left = NULL;
		delete succe;
		succe = NULL;
		size--;
		return true;
		
	} else { // Case 3: One child
		
		TaskItem* temp;

		if (curr->left && !curr->right) temp = curr->left;
		else temp = curr->right;
		
		if (curr != root) {
			if (curr == parent->left) parent->left = temp;
			else parent->right = temp;
		} else root = temp;
		
		curr->right = NULL;
		curr->left = NULL;
		delete curr;
		curr = NULL;
		size = size - 1;
		return true;
	}
	
	return false;
}
