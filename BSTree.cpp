#include "BSTree.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>
BSTree::BSTree(){
	this->root=NULL;
}
bool BSTree::empty(){
	if(root==NULL){
		return true;
	}
	return false;
}
bool BSTree::insert(int t){
	if(root==NULL){
		root= new Node(t);
		return true;
	}else{
		return insertNode(t,root);
	}
}
bool BSTree::insertNode(int t,Node *n){
	if(t<n->data){
		if(n->left==NULL){
			n->left=new Node(t);
			n->left->parent=n;
			return true;
		}else{
			return insertNode(t,n->left);
		}
	}else if(t>n->data){
		if(n->right==NULL){
			n->right=new Node(t);
			n->right->parent=n;
			return true;
		}else{
			return insertNode(t,n->right);
		}
	}
	return false;
}
bool BSTree::find(int t){
	if(root==NULL){
		return false;
	}else{
		return findNode(t,root);
	}
}
bool BSTree::findNode(int t,Node *n){
	if(t<n->data){
		if(n->left==NULL){
			return false;
		}else{
			return findNode(t,n->left);
		}
	}else if(t>n->data){
		if(n->right==NULL){
			return false;
		}else{
			return findNode(t,n->right);
		}
	}else{
		return true;
	}
}
BSTree::~BSTree(){
	if(root!=NULL){
		deleteNode(root);
	}
}
void BSTree::deleteNode(Node *n){
	if(n->left!=NULL){
		deleteNode(n->left);
	}
	if(n->right!=NULL){
		deleteNode(n->right);
	}
	delete n;
}
BSTree::BSTree(const BSTree &old_tree){
	Node *o= old_tree.root;
	if(o==NULL){
		this->root=NULL;
	}else{
		this->root=makeTree(this->root,o);	
	}
		
}
BSTree::Node *BSTree::makeTree(Node *n,Node *o){
	n=new Node(o->data);
	
	if(o->left!=NULL){
		Node *l=makeTree(n->left,o->left);
		n->left=l;
		n->left->parent=n;
	}
	if(o->right!=NULL){
		Node *r=makeTree(n->right,o->right);
		n->right=r;
		n->right->parent=n;
	}
	return n;
}
void BSTree::sortedArray(std::vector<int> &list){
	if(this->root!=NULL){
		sortedArrayHelper(list,this->root);
	}
}
void BSTree::sortedArrayHelper(std::vector<int> &list, Node *n){
	if(n != NULL){
		sortedArrayHelper(list,n->left);
		list.push_back(n->data);
		sortedArrayHelper(list,n->right);
	}
	return;
}
bool BSTree::remove(int num){
	//std::cout<<"8"<<std::endl;
	Node *del=read(num);
	//std::cout<<"9"<<std::endl;
	if(del==NULL){
		return false;
	}
	//std::cout<<"10"<<std::endl;
	if(del->left==NULL && del->right==NULL){
		if(del==this->root){
			delete del;
			this->root=NULL;
		}else{
			removeLeaf(del);
		}
		return true;
	}else if(del->left==NULL || del->right==NULL){
		if(del==this->root && del->left==NULL){
			this->root=del->right;
			delete del;
		}else if(del==this->root && del->right==NULL){
			this->root=del->left;
			delete del;
		}else{
			shortCircuit(del);
		}
		return true;
	}else{
		promotion(del);
		return true;
	}
	return false;
}
void BSTree::removeLeaf(Node *del){
	if(del->parent->left==del){
		del->parent->left=NULL;
	}else{
		del->parent->right=NULL;
	}
	delete del;
}
void BSTree::shortCircuit(Node *del){
	if(del->parent->left==del){
		if(del->left!=NULL){
			del->parent->left=del->left;
			del->left->parent=del->parent;
		}else{
			del->parent->left=del->right;
			del->right->parent=del->parent;
		}
	}else{
		if(del->left!=NULL){
			del->parent->right=del->left;
			del->left->parent=del->parent;
		}else{
			del->parent->right=del->right;
			del->right->parent=del->parent;
		}
	}
	delete del;
}
void BSTree::promotion(Node *del){
	Node *promote = getMinMax(del->right);
	del->data=promote->data;
	if(promote->left==NULL && promote->right==NULL){
		removeLeaf(promote);
	}else{
		shortCircuit(promote);
	}
}
BSTree::Node *BSTree::getMinMax(Node *n){
	if(n->left==NULL){
		return n;
	}else{
		return getMinMax(n->left);
	}
}
BSTree::Node *BSTree::read(int t){
	if(root==NULL){
		return NULL;
	}else{
		return readNode(t,root);
	}
}
BSTree::Node *BSTree::readNode(int t,Node *n){
	if(t<n->data){
		if(n->left==NULL){
			return NULL;
		}else{
			return readNode(t,n->left);
		}
	}else if(t>n->data){
		if(n->right==NULL){
			return NULL;
		}else{
			return readNode(t,n->right);
		}
	}else{
		return n;
	}
}