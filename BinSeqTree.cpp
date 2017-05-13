#include "BinSeqTree.h"
#include <iostream>
#include <math.h>
#include "Constant.h"
#include "Queue.h"
#include "Queue.cpp"

using namespace std;


BinSeqTree::BinSeqTree()
{
	root = NULL;
}

bool BinSeqTree::isEmpty()
{
	if (NULL == root)
	{
		return true;
	}
	return false;
}

void BinSeqTree::insertNode(int data)
{
	if (isEmpty())
	{
		root = new BiNode();
		root->data = data;
		root->lNode = NULL;
		root->rNode = NULL;
		return;
	}

	if (data < root->data)
	{
		//insertleft
		insertLeft(root, data);
	}
	else
	{
		//insertright
		insertRight(root, data);
	}
	return;
}

void BinSeqTree::deleteNode(int data)
{
	if (isEmpty())
		return;
	BiNode *node = root;
	BiNode *parent = NULL;
	while (node != NULL)
	{
		if (data == node->data)
		{
			break;
		}
		parent = node;
		if (data < node->data)
		{
			node = node->lNode;
		}
		else
		{
			node = node->rNode;
		}
	}

	if ((NULL != node) && (data == node->data))
	{
		//delete the node
		if (NULL == parent)
		{
			deleteRoot();
		}
		else if (parent->lNode == node)
		{
			deleteTheNode(parent, node, 0);
		}
		else
		{
			deleteTheNode(parent, node, 1);
		}
		
	}
	else if (NULL != root)
	{
		cout << "data:" << data << "is not in the tree" << endl;
	}
	else
	{
		cout << "The tree is empty" << endl;
	}
}

void BinSeqTree::deleteNodeViaCopy(int data)
{
	if (isEmpty())
		return;
	BiNode *node = root;
	BiNode *parent = NULL;
	while (node != NULL)
	{
		if (data == node->data)
		{
			break;
		}
		parent = node;
		if (data < node->data)
		{
			node = node->lNode;
		}
		else
		{
			node = node->rNode;
		}
	}

	if ((NULL != node) && (data == node->data))
	{
		//delete the node
		if (NULL == parent)
		{
			deleteRootViaCopy();
		}
		else if (parent->lNode == node)
		{
			deleteTheNodeViaCopy(parent, node, 0);
		}
		else
		{
			deleteTheNodeViaCopy(parent, node, 1);
		}
	}
	else if (NULL != root)
	{
		cout << "data:" << data << "is not in the tree" << endl;
	}
	else
	{
		cout << "The tree is empty" << endl;
	}
}

void BinSeqTree::deleteRoot()
{
	BiNode* temp = NULL;
	if (!root->rNode)
	{
		temp = root->lNode;
		delete root;
		root = temp;
	}
	else if (!root->lNode)
	{
		temp = root->rNode;
		delete root;
		root = temp;
	}
	else
	{
		temp = root->lNode;
		while (NULL != temp->rNode)
		{
			temp = temp->rNode;
		}
		temp->rNode = root->rNode;

		temp = root->lNode;
		delete root;
		root = temp;
	}
}

void BinSeqTree::deleteRootViaCopy()
{
	BiNode* temp = NULL;
	if (!root->rNode)
	{
		temp = root->lNode;
		delete root;
		root = temp;
	}
	else if (!root->lNode)
	{
		temp = root->rNode;
		delete root;
		root = temp;
	}
	else
	{
		BiNode* tempParent = root;
		temp = root->lNode;
		int moveDirectionFlag = 0;
		while (NULL != temp->rNode)
		{
			tempParent = temp;
			temp = temp->rNode;
			moveDirectionFlag = 1;
		}
		root->data = temp->data;           //copy the rightest node value in the left tree to the root node value

		if (NULL != temp->lNode)
		{
			if (0 == moveDirectionFlag)
			{
				tempParent->lNode = temp->lNode;
			}
			else
			{
				tempParent->rNode = temp->lNode;
			}
			
		}
		delete temp;
	}
}

void BinSeqTree::deleteTheNode(BiNode*& parent, BiNode*& node, int lOrR)
{
	BiNode* temp = node;
	if (!node->rNode)
	{
		if (0 == lOrR)  //parent left child
		{
			parent->lNode = node->lNode;
		}
		else
		{
			parent->rNode = node->lNode;
		}
	}
	else if (!node->lNode)
	{
		if (0 == lOrR)  //parent left child
		{
			parent->lNode = node->rNode;
		}
		else
		{
			parent->rNode = node->rNode;
		}
	}
	else
	{
		temp = temp->lNode;                //Move left
		while (NULL != temp->rNode)        //go to the rightest node in the left tree
		{
			temp = temp->rNode;
		}
		temp->rNode = node->rNode;        //delete node right tree linked to the rightest node in the left tree
		temp = node;
		if (0 == lOrR)
		{
			parent->lNode = node->lNode;
		}
		else
		{
			parent->rNode = node->lNode;
		}
	}
	delete temp;                          //free the memory
	return;
}

void BinSeqTree::deleteTheNodeViaCopy(BiNode*& parent, BiNode*& node, int lOrR)
{
	BiNode* temp = node;
	if (!node->rNode)
	{
		if (0 == lOrR)  //parent left child
		{
			parent->lNode = node->lNode;
		}
		else
		{
			parent->rNode = node->lNode;
		}
	}
	else if (!node->lNode)
	{
		if (0 == lOrR)  //parent left child
		{
			parent->lNode = node->rNode;
		}
		else
		{
			parent->rNode = node->rNode;
		}
	}
	else
	{
		BiNode* tempsParent = temp;
		temp = temp->lNode;                //Move left
		int moveDirectionFlag = 0;
		while (NULL != temp->rNode)        //go to the rightest node in the left tree
		{
			tempsParent = temp;
			temp = temp->rNode;
			moveDirectionFlag = 1;
		}
		node->data = temp->data;           //copy the rightest node value into original deleted node
		if (0 == moveDirectionFlag)
			tempsParent->lNode = temp->lNode;
		else
			tempsParent->rNode = temp->lNode;
		//if (temp->lNode != NULL)
		//{
		//	tempsParent->rNode = temp->lNode;
		//}
	}
	delete temp;                          //free the memory
	return;
}

void BinSeqTree::insertLeft(BiNode* node, int data)
{
	if (NULL == node->lNode)
	{
		BiNode* leftNode = new BiNode();
		leftNode->data = data;
		leftNode->lNode = NULL;
		leftNode->rNode = NULL;
		node->lNode = leftNode;
		return;
	}
	else
	{
		if (data < node->lNode->data)
			insertLeft(node->lNode, data);
		else
			insertRight(node->lNode, data);
	}
}

void BinSeqTree::insertRight(BiNode* node, int data)
{
	if (NULL == node->rNode)
	{
		BiNode* rightNode = new BiNode();
		rightNode->data = data;
		rightNode->lNode = NULL;
		rightNode->rNode = NULL;
		node->rNode = rightNode;
		return;
	}
	else
	{
		if (data < node->rNode->data)
			insertLeft(node->rNode, data);
		else
			insertRight(node->rNode, data);
	}
}

void BinSeqTree::destoryTree()
{
	if (NULL == root)
		return;
	destroyNode(root);
}

void BinSeqTree::destroyNode(BiNode* node)
{
	if (NULL == node)
		return;
	destroyNode(node->lNode);
	destroyNode(node->rNode);
	deleteNode(node->data);
	//cout << "Last Order:" << node->data << endl;
}

void BinSeqTree::preOrder()
{
	if (NULL == root)
		return;
	preOrder(root);
}

void BinSeqTree::preOrder(BiNode* node)
{
	if (NULL == node)
		return;
	cout << "Pre Order:" << node->data << endl;
	preOrder(node->lNode);
	preOrder(node->rNode);
}

void BinSeqTree::midOrder()
{
	if (NULL == root)
		return;
	midOrder(root);
}

void BinSeqTree::midOrder(int*& pArray)
{
	if (NULL == root)
		return;
	midOrder(root, pArray);
}

void BinSeqTree::midOrder(BiNode* node)
{
	if (NULL == node)
		return;
	midOrder(node->lNode);
	cout << "Mid Order:" << node->data << endl;
	midOrder(node->rNode);
}

void BinSeqTree::midOrder(BiNode* node, int*& pArray)
{
	if (NULL == node)
		return;
	midOrder(node->lNode, pArray);
	*pArray = node->data;
	pArray++;
	midOrder(node->rNode, pArray);
}

void BinSeqTree::lastOrder()
{
	if (NULL == root)
		return;
	lastOrder(root);
}

void BinSeqTree::lastOrder(BiNode* node)
{
	if (NULL == node)
		return;
	lastOrder(node->lNode);
	lastOrder(node->rNode);
	cout << "Last Order:" << node->data << endl;
}

void BinSeqTree::breadthFirstOrder()
{
	if (isEmpty())
		return;

	ArrayQueue<BiNode*, QUEUE_SIZE> *queue = new ArrayQueue<BiNode*, QUEUE_SIZE>();
	queue->enQueue(root);
	while (!(queue->isEmpty()))
	{
		BiNode* p_BiNode;
		queue->deQueue(p_BiNode);
		cout << "BreadthFristOrder:" << p_BiNode->data << endl;
		if (p_BiNode->lNode != NULL)
		{
			queue->enQueue(p_BiNode->lNode);
		}
		if (p_BiNode->rNode != NULL)
		{
			queue->enQueue(p_BiNode->rNode);
		}
	}
	delete queue;
	queue = NULL;
}


//pay attention, should be optimization, old tree first deleted, then recreate the balance tree
void BinSeqTree::balanceTree(int* pArray, int first, int last)
{
	if (first <= last)
	{
		int middle = (first + last) / 2;
		insertNode(*(pArray + middle));
		balanceTree(pArray, first, middle - 1);
		balanceTree(pArray, middle + 1, last);
	}
}

void BinSeqTree::dswBalance(int nodeNum)
{
	if (nodeNum < 3)
	{
		return;
	}
	createBackbone();  //Step 1, createBackbone, retate right
	createPerfectTree(nodeNum);
}

void BinSeqTree::createBackbone()
{
	BiNode* grandParent = NULL;
	BiNode* temp = root;
	while (NULL != temp)
	{
		if (NULL != temp->lNode)
		{
			BiNode* child = temp->lNode;
			rotateRight(grandParent, temp, child);
			temp = child;
		}
		else
		{
			grandParent = temp;
			temp = temp->rNode;
		}
	}
}

void BinSeqTree::createPerfectTree(int nodeNum)
{
	BiNode* grandParent = NULL;
	BiNode* parent = root;
	BiNode* child = root->rNode;
	int logValue = log(nodeNum + 1) / log(2);
	int m = pow(2, logValue) - 1;
	for (int i = 0; i < nodeNum - m; i++)
	{
		rotateLeft(grandParent, parent, child);
		if (NULL == grandParent)
		{
			root = child;
		}
		grandParent = child;
		parent = child->rNode;
		child = child->rNode->rNode;
	}
	while (m > 1)
	{
		m = m / 2;
		BiNode* grandParent2 = NULL;
		BiNode* parent2 = root;
		BiNode* child2 = root->rNode;
		for (int i = 0; i < m; i++)
		{
			rotateLeft(grandParent2, parent2, child2);
			if (NULL == grandParent2)
			{
				root = child2;
			}
			grandParent2 = child2;
			parent2 = child2->rNode;
			child2 = child2->rNode->rNode;
		}
	}
}


void BinSeqTree::rotateRight(BiNode*& grandParent, BiNode*& parent, BiNode*& child)
{
	int lOrR = 0;
	if (NULL != grandParent)
	{
		if (parent == grandParent->lNode)
		{
			lOrR = 0;
		}
		else
		{
			lOrR = 1;
		}
		if (0 == lOrR)
		{
			grandParent->lNode = child;
		}
		else
		{
			grandParent->rNode = child;
		}
	}
	parent->lNode = child->rNode;
	child->rNode = parent;
	if (NULL == grandParent)
	{
		root = child;
	}
}


void BinSeqTree::rotateLeft(BiNode*& grandParent, BiNode*& parent, BiNode*& child)
{
	if (NULL == grandParent)         //parent should be root
	{
		if (child != NULL)
		{
			parent->rNode = child->lNode;
			child->lNode = parent;			
		}
		else
		{
			return;
		}
	}
	else
	{
		grandParent->rNode = parent->rNode;
		parent->rNode = child->lNode;
		child->lNode = parent;
	}
	if (NULL == grandParent)
	{
		root = child;
	}
}