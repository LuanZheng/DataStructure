#ifndef _BIN_SEARCH_TREE_H_
#define _BIN_SEARCH_TREE_H_
#include "Constant.h"
#include "Stack.h"
#include "Queue.h"

template <class T>
class BinNode
{
public:
	BinNode();
	BinNode(const T& data, BinNode<T> *l = NULL, BinNode<T> *r = NULL);
	bool isLeafNode();
	bool isOnlyoneChildNode(bool &leftOrRight);
	T data;
	virtual BinNode<T>* getLeft();
	virtual BinNode<T>* getRight();
	virtual void setLeft(BinNode<T>* pLeft);
	virtual void setRight(BinNode<T>* pRight);
private:
	BinNode<T>* left;
	BinNode<T>* right;
};


template <class T>
class AVLNode : public BinNode<T>
{
public:
	AVLNode();
	AVLNode(const T& data, AVLNode<T> *l = NULL, AVLNode<T> *r = NULL, AVLNode<T> *p = NULL);
	AVLNode<T>* pa;
	int balanceValue;
	virtual BinNode<T>* getLeft();
	virtual BinNode<T>* getRight();
	virtual void setLeft(BinNode<T>* pLeft);
	virtual void setRight(BinNode<T>* pRight);
private:
	AVLNode<T>* left;
	AVLNode<T>* right;
};

template <class T, unsigned int capacity>
class BinSearchTree
{
public:
	BinSearchTree();
	bool isEmpty();
	bool isFull();
	virtual bool insert(T data);
	bool search(T data);
	bool delViaMerge(T data);
	bool delViaCopy(T data);
	bool preOrder();  //VLR
	bool preOrderWithoutRecursion();
	bool midOrder();   //LVR
	bool midOrderWithoutRecursion();
	bool afterOrder();   //LRV
	bool afterOrderWithoutRecursion();
	bool scopeOrder();
	bool dswBalance();
	unsigned int getNodeNum();
	virtual void setRoot(BinNode<T> *node);
	virtual BinNode<T>* getRoot();
protected:
	void createBackBone();
	void createPerfectTree();
	void preOrder(BinNode<T> *node);
	void midOrder(BinNode<T> *node);
	void afterOrder(BinNode<T> *node);
	unsigned int treeNodeNum;
	Stack<BinNode<T>*, capacity> *stackHelper;
	LinkQueue<BinNode<T>*, capacity> *queueHelper;
	void rotationRight(BinNode<T>* gr, BinNode<T>* pa, BinNode<T>* ch);
	void rotationLeft(BinNode<T>* gr, BinNode<T>* pa, BinNode<T>* ch);	
private:
	virtual void updateBalanceFactors(AVLNode<T>* avlNode, bool insertOrDelete = true, bool leftOrRight = true);
	BinNode<T> *root;
};

template <class T, unsigned int capacity>
class BinSearchTreeAVL : public BinSearchTree<T, capacity>
{
public:
	virtual bool insert(T data);
	//virtual bool delViaCopy(T data);
	bool scopeOrder();
	virtual void setRoot(BinNode<T> *node);
	virtual BinNode<T>* getRoot();
private:
	//void rotationRight(AVLNode<T>* gr, AVLNode<T>* pa, AVLNode<T>* ch);
	//void rotationLeft(AVLNode<T>* gr, AVLNode<T>* pa, AVLNode<T>* ch);
	void updateBalanceFactors(AVLNode<T>* avlNode, bool insertOrDelete = true, bool leftOrRight = true);
	void updateBalanceFactors4Insert(AVLNode<T>* avlNode);
	void updateBalanceFactors4Delete(AVLNode<T>* avlNode, bool leftOrRight);
	LinkQueue<AVLNode<T>*, capacity> *queueHelper;
	AVLNode<T> *root;
};

#endif
