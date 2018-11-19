#ifndef BSTREE_H
#define BSTREE_H
#include <iostream>
#include <cstdlib>
#include <vector>
class BSTree{
	private:
		class Node{
			public:
				Node *left, *right, *parent;
				int data;
				Node(int n){data=n;left=NULL;right=NULL;parent=NULL;};
		};
		Node *root;
		bool insertNode(int,Node *);//
		bool findNode(int,Node *);//
		void deleteNode(Node *);
		void sortedArrayHelper(std::vector<int> &, Node *);
		Node *read(int );
		Node *readNode(int ,Node *);
		Node *getMinMax(Node *n);
		Node *makeTree(Node *,Node *);
	public:
		BSTree();//
		bool empty();//
		bool insert(int);//
		bool find(int);//
		~BSTree();
		BSTree(const BSTree &);
		void sortedArray(std::vector<int> &);
		
		bool remove(int num);
		void removeLeaf(Node *);
		void shortCircuit(Node *);
		void promotion(Node *);
		
		
};


#endif
