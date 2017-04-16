#include "BinSearchTree.h"
#include <math.h>

template <class T>
BinNode<T>::BinNode()
{
	left = NULL;
	right = NULL;
}

template<class T>
BinNode<T>::BinNode(const T& data, BinNode<T> *l = NULL, BinNode<T> *r = NULL)
{
	this->data = data;
	left = l;
	right = r;
}

template<class T>
bool BinNode<T>::isLeafNode()
{
	bool rs = false;
	//if ((NULL == left) && (NULL == right))
	if (NULL == getLeft() && (NULL == getRight()))
		rs = true;
	return rs;
}

template<class T>
BinNode<T>* BinNode<T>::getLeft()
{
	return left;
}

template<class T>
BinNode<T>* BinNode<T>::getRight()
{
	return right;
}

template<class T>
void BinNode<T>::setLeft(BinNode<T>* pLeft)
{
	left = pLeft;
}

template<class T>
void BinNode<T>::setRight(BinNode<T>* pRight)
{
	right = pRight;
}


template<class T>
bool BinNode<T>::isOnlyoneChildNode(bool &leftOrRight)
{
	bool rs = false;
	if ((NULL == getLeft()) && (NULL != getRight()))
	{
		leftOrRight = true;
		rs = true;
	}
	else if ((NULL != getLeft()) && (NULL == getRight()))
	{
		leftOrRight = false;
		rs = true;
	}
	else
	{
		rs = false;
	}
	return rs;
}


template<class T, unsigned int capacity>
BinSearchTree<T, capacity>::BinSearchTree()
{
	root = NULL;
	stackHelper = NULL;
	queueHelper = NULL;
	treeNodeNum = 0;
}

template<class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::isEmpty()
{
	bool rs = false;
	if ((0 == treeNodeNum) && (NULL == root))
	{
		rs = true;
	}
	return rs;
}

template<class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::isFull()
{
	bool rs = false;
	if (capacity == treeNodeNum)
	{
		rs = true;
	}
	return rs;
}

template<class T, unsigned int capacity>
void BinSearchTree<T, capacity>::setRoot(BinNode<T> *node)
{
	root = node;
	return;
}

template<class T, unsigned int capacity>
BinNode<T>* BinSearchTree<T, capacity>::getRoot()
{
	return root;
}

template<class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::insert(T data)
{
	bool rs = false;
	if (isFull())
	{
		rs = false;
	}
	else if (isEmpty())
	{
		root = new BinNode<T>();
		root->data = data;
		//root->getLeft() = NULL;
		//root->getRight() = NULL;
		treeNodeNum++;
		rs = true;
	}
	else
	{
		BinNode<T>* parent = NULL;
		BinNode<T>* node = root;
		bool leftOrRight = false; //false means left, true means right
		while (NULL != node)
		{
			parent = node;
			if (data < node->data)
			{
				leftOrRight = false;
				//node = node->left;
				node = node->getLeft();
			}
			else
			{
				leftOrRight = true;
				//node = node->right;
				node = node->getRight();
			}
		}
		BinNode<T>* newNode = new BinNode<T>();
		newNode->data = data;
		if (leftOrRight)
		{
			//parent->right = newNode;
			parent->setRight(newNode);
		}
		else
		{
			//parent->left = newNode;
			parent->setLeft(newNode);
		}
		treeNodeNum++;
	}
	return rs;
}

template<class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::search(T data)
{
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		BinNode<T>* iter = root;
		while (NULL != iter)
		{
			if (data < iter->data)
			{
				iter = iter->left;
			}
			else if (data > iter->data)
			{
				iter = iter->right;
			}
			else
			{
				cout << "Find the data, the data is" << iter->data << endl;
				result = true;
				break;
			}
		}
		if (NULL == iter)
		{
			cout << "Not find the data" << endl;
		}
	}
	return false;
}

template<class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::delViaMerge(T data)
{
	bool rs = false;
	if (isEmpty())
	{
		rs = false;
	}
	else
	{
		bool findOrNot = false;
		BinNode<T> *preIter = NULL;
		BinNode<T> *iter = root;
		while (NULL != iter)
		{
			if (data < iter->data)
			{
				preIter = iter;
				iter = iter->left;
			}
			else if(data > iter->data)
			{
				preIter = iter;
				iter = iter->right;
			}
			else //find the node to del
			{
				findOrNot = true;
				bool hasLeftOrRight = false;
				if (iter->isLeafNode())
				{
					if (NULL != preIter)
					{
						if (preIter->left == iter)
						{
							delete iter;
							iter = NULL;
							preIter->left = NULL;
						}
						else
						{
							delete iter;
							iter = NULL;
							preIter->right = NULL;
						}
					}
					else
					{
						delete iter;
						iter = NULL;
						root = NULL;
					}

				}
				else if (iter->isOnlyoneChildNode(hasLeftOrRight))
				{
					BinNode<T> *needDeleteBuffer = iter;
					if (hasLeftOrRight)  //true means only right
					{
						iter = iter->right;
					}
					else     //false means only left
					{
						iter = iter->left;
					}
					if (NULL == preIter)
					{
						root = iter;
					}
					else
					{
						if (preIter->left == needDeleteBuffer)
						{
							preIter->left = iter;
						}
						else
						{
							preIter->right = iter;
						}
					}
					delete needDeleteBuffer;
					needDeleteBuffer = NULL;
				}
				else  //has both left and right child
				{
					BinNode<T> *needDeleteBuffer = iter;
					iter = iter->left;        //turn left
					if (NULL == preIter)
					{
						root = iter;
					}
					else
					{
						if (preIter->left == needDeleteBuffer)
						{
							preIter->left = iter;
						}
						else
						{
							preIter->right = iter;
						}
					}
					BinNode<T> *rightestNodeInLeftTree = NULL;
					while (NULL != iter)
					{
						rightestNodeInLeftTree = iter;
						iter = iter->right;
					}
					rightestNodeInLeftTree->right = needDeleteBuffer->right;
					delete needDeleteBuffer;
					needDeleteBuffer = NULL;
				}
				treeNodeNum--;
				rs = true;
				break;
			}
		}
		if (false == findOrNot)
		{
			rs = false;
		}
	}
	return rs;
}

template<class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::delViaCopy(T data)
{
	//cout << "The data to be deleted is :" << data << endl;
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		bool findOrNot = false;
		BinNode<T> *preIter = NULL;
		BinNode<T> *iter = getRoot();
		while (NULL != iter)
		{
			if (data < iter->data)
			{
				preIter = iter;
				//iter = iter->left;
				iter = iter->getLeft();
			}
			else if (data > iter->data)
			{
				preIter = iter;
				//iter = iter->right;
				iter = iter->getRight();
			}
			else  //Find the node
			{	
				findOrNot = true;
				bool hasLeftOrRight = false;
				if (iter->isLeafNode())
				{
					if (NULL != preIter)
					{
						if (/*preIter->left*/ preIter->getLeft() == iter)
						{
							delete iter;
							iter = NULL;
							//preIter->left = NULL;
							preIter->setLeft(NULL);
							updateBalanceFactors(dynamic_cast<AVLNode<T>*>(preIter), false, true);
						}
						else
						{
							delete iter;
							iter = NULL;
							//preIter->right = NULL;
							preIter->setRight(NULL);
							updateBalanceFactors(dynamic_cast<AVLNode<T>*>(preIter), false, false);
						}
					}
					else
					{
						delete iter;
						iter = NULL;
						setRoot(NULL);
					}
				}
				else if (iter->isOnlyoneChildNode(hasLeftOrRight))
				{
					bool leftOrRight = true;
					BinNode<T> *needDeleteBuffer = iter;
					if (hasLeftOrRight)  //true means only right, it is the out parameter
					{
						//iter = iter->right;
						iter = iter->getRight();
					}
					else     //false means only left
					{
						//iter = iter->left;
						iter = iter->getLeft();
					}
					if (NULL == preIter)
					{
						setRoot(iter);
					}
					else
					{
						if (/*preIter->left*/ preIter->getLeft() == needDeleteBuffer)
						{
							//preIter->left = iter;
							preIter->setLeft(iter);
							leftOrRight = true;
						}
						else
						{
							//preIter->right = iter;
							preIter->setRight(iter);
							leftOrRight = false;
						}
					}
					if (NULL != dynamic_cast<AVLNode<T>*>(iter))
					{
						dynamic_cast<AVLNode<T>*>(iter)->pa = dynamic_cast<AVLNode<T>*>(preIter);
					}
					delete needDeleteBuffer;
					needDeleteBuffer = NULL;
					updateBalanceFactors(dynamic_cast<AVLNode<T>*>(preIter), false, leftOrRight);					
				}
				else  //Copy delete, node has 2 child
				{
					bool leftOrRight = true;
					BinNode<T> *needConverNode = iter;
					preIter = iter;
					//iter = iter->left;          //turn left
					if (NULL != iter->getLeft())
					{
						iter = iter->getLeft();
					}				
					while (NULL != iter->getRight()/*iter->right*/)
					{
						preIter = iter;
						//iter = iter->right;
						leftOrRight = false;
						iter = iter->getRight();
					}
					needConverNode->data = iter->data;
					if (needConverNode == preIter)
					{
						//preIter->left = iter->left;
						preIter->setLeft(iter->getLeft());
					}
					else
					{
						//preIter->right = iter->left;
						preIter->setRight(iter->getLeft());
					}
					delete iter;
					iter = NULL;
					updateBalanceFactors(dynamic_cast<AVLNode<T>*>(preIter), false, leftOrRight);
				}
				treeNodeNum--;
				result = true;
				break;
			}
		}
		if (false == findOrNot)
		{
			result = false;
		}
	}
	return result;
}

template <class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::preOrder()
{
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		cout << "PreOrder: The Data is: " << root->data << endl;
		preOrder(root->left);
		preOrder(root->right);
		result = true;
	}
	return result;
}

template <class T, unsigned int capacity>
void BinSearchTree<T, capacity>::preOrder(BinNode<T> *node)
{
	if (NULL == node)
	{

	}
	else
	{
		cout << "PreOrder: The Data is: " << node->data << endl;
		preOrder(node->left);
		preOrder(node->right);
	}
	return;
}

template <class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::preOrderWithoutRecursion()
{
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		stackHelper = new Stack<BinNode<T>*, capacity>();
		BinNode<T> *iter = root;
		while ((NULL != iter) || !(stackHelper->isEmpty()))
		{
			while (NULL != iter)
			{
				cout << "preOrderWithoutRecursion: The data is: " << iter->data << endl;
				stackHelper->push(iter);
				iter = iter->left;
			}
			if (!(stackHelper->isEmpty()))
			{
				stackHelper->pop(iter);
				iter = iter->right;
			}
		}
		if (NULL != stackHelper)
		{
			delete stackHelper;
			stackHelper = NULL;
		}
		result = true;
	}
	return result;
}

template <class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::midOrder()
{
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		midOrder(root->left);
		cout << "MidOrder: The data is: " << root->data << endl;
		midOrder(root->right);
	}
	return result;
}

template <class T, unsigned int capacity>
void BinSearchTree<T, capacity>::midOrder(BinNode<T> *node)
{
	if (NULL == node)
	{

	}
	else
	{
		midOrder(node->left);
		cout << "MinOrder: The data is: " << node->data << endl;
		midOrder(node->right);
	}
	return;
}

template <class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::midOrderWithoutRecursion()
{
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		BinNode<T> *iter = root;
		stackHelper = new Stack<BinNode<T>*, capacity>();
		while ((NULL != iter) || !(stackHelper->isEmpty()))
		{
			while (NULL != iter)
			{
				stackHelper->push(iter);
				iter = iter->left;
			}
			if (!(stackHelper->isEmpty()))
			{
				stackHelper->pop(iter);
				cout << "midOrderWithoutRecursion: The data is: " << iter->data << endl;
				iter = iter->right;
			}
		}
		if (NULL != stackHelper)
		{
			delete stackHelper;
			stackHelper = NULL;
		}
		result = true;
	}
	return result;
}

template <class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::afterOrder()
{
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		afterOrder(root->left);
		afterOrder(root->right);
		cout << "AfterOrder: The data is: " << root->data <<endl;
		result = true;
	}
	return result;
}


template <class T, unsigned int capacity>
void BinSearchTree<T, capacity>::afterOrder(BinNode<T>* node)
{
	if (NULL == node)
	{

	}
	else
	{
		afterOrder(node->left);
		afterOrder(node->right);
		cout << "AfterOrder: The data is: " << node->data << endl;
	}
	return;
}

template <class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::afterOrderWithoutRecursion()
{
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		BinNode<T> *preVisited = NULL;
		BinNode<T> *iter = root;
		stackHelper = new Stack<BinNode<T>*, capacity>(); 
		while ((NULL != iter) || !(stackHelper->isEmpty()))
		{
			while (NULL != iter)
			{
				stackHelper->push(iter);
				iter = iter->left;
			}
			if (!(stackHelper->isEmpty()))
			{
				stackHelper->topElem(iter);
				if ((NULL == iter->right) || (preVisited == iter->right))
				{
					stackHelper->pop(iter);
					cout << "afterOrderWithoutRecursion: The data is: " << iter->data << endl;
					preVisited = iter;
					iter = NULL;
				}
				else
				{
					iter = iter->right;
				}
			}
		}
		if (NULL != stackHelper)
		{
			delete stackHelper;
			stackHelper = NULL;
		}
	}
	return result;
}

template <class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::scopeOrder()
{
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		queueHelper = new LinkQueue<BinNode<T>*, capacity>();
		queueHelper->enQueue(root);
		while (!(queueHelper->isEmpty()))
		{
			BinNode<T>* temp = NULL;
			queueHelper->deQueue(temp);
			cout << "ScopeOrder: The value is :" << temp->data << endl;
			if (NULL != temp->getLeft()/*temp->left*/)
			{
				queueHelper->enQueue(temp->getLeft()/*temp->left*/);
			}
			if (NULL != temp->getRight()/*temp->right*/)
			{
				queueHelper->enQueue(temp->getRight()/*temp->right*/);
			}
		}
		if (NULL != queueHelper)
		{
			delete queueHelper;
			queueHelper = NULL;
		}
		result = true;
	}
	return result;
}

template <class T, unsigned int capacity>
void BinSearchTree<T, capacity>::rotationRight(BinNode<T>* gr, BinNode<T>* pa, BinNode<T>* ch)
{
	if (NULL == gr)                   //the current pa must be root, no gr case
	{
		//pa->left = ch->right;
		pa->setLeft(ch->getRight());
		//ch->right = pa;
		ch->setRight(pa);
		//root = ch;                    //In this case, ch should be the new root after rotate
		setRoot(ch);
	}
	else
	{
		if (/*gr->right*/ gr->getRight() == pa)
		{
			//gr->right = ch;
			gr->setRight(ch);
		}
		else
		{
			//gr->left = ch;
			gr->setLeft(ch);
		}
		//pa->left = ch->right;
		pa->setLeft(ch->getRight());
		//ch->right = pa;
		ch->setRight(pa);
	}
	return;
}

template <class T, unsigned int capacity>
void BinSearchTree<T, capacity>::rotationLeft(BinNode<T>* gr, BinNode<T>* pa, BinNode<T>* ch)
{
	BinNode<T>* tmp = ch->getLeft()/*ch->left*/;
	//ch->left = pa;
	ch->setLeft(pa);
	//pa->right = tmp;
	pa->setRight(tmp);
	if (NULL == gr)
	{
		//root = ch;
		setRoot(ch);
	}
	else
	{
		if (/*gr->right*/gr->getRight() == pa)
		{
			//gr->right = ch;
			gr->setRight(ch);
		}
		else
		{
			//gr->left = ch;
			gr->setLeft(ch);
		}
	}
	return;
}

template <class T, unsigned int capacity>
void BinSearchTree<T, capacity>::createBackBone()
{
	BinNode<T>* gr = NULL;
	BinNode<T>* pa = root;
	BinNode<T>* ch = NULL;
	while (NULL != pa)
	{		
		if (NULL != pa->getLeft()/*pa->left*/)                 //if has left child, rotate right
		{
			//ch = pa->left;	
			ch = pa->getLeft();
			rotationRight(gr, pa, ch);
			pa = ch;                   //After rotate, he ch should be the pa in the next time loop
		}
		else          //gr, pa, tmp move downto next right
		{
			if (root == pa)       //pa is root case, when move downto next right, gr should be set to root
			{
				gr = root;	
			}
			else
			{
				//gr = gr->right;
				gr = gr->getRight();
			}
			//pa = pa->right;
			pa = pa->getRight();
		}
	}
}

template <class T, unsigned int capacity>
void BinSearchTree<T, capacity>::createPerfectTree()
{
	unsigned int n = treeNodeNum;
	if (n <= 3)
	{
		return;
	}
	unsigned int m = pow(2, floor(log(n + 1)/log(2))) - 1;
	BinNode<T>* gr = NULL;
	BinNode<T>* pa = root;
	BinNode<T>* ch = /*root->right*/root->getRight();
	for (unsigned int i = 0; i < n - m; i++)
	{
		rotationLeft(gr, pa, ch);
		gr = ch;
		//pa = gr->right;
		pa = gr->getRight();
		if (NULL != pa)
		{
			//ch = pa->right;
			ch = pa->getRight();
		}
		else
		{
			break;
		}
		//if ((NULL != pa->right) && (NULL != ch->right))
		//{
		//	pa = pa->right->right;         //The pa right should be changed in rorationLeft, can not use as
		//	ch = ch->right->right;
		//	if ((NULL == pa) || (NULL == ch))
		//	{
		//		break;
		//	}
		//}
		//else
		//{
		//	break;
		//}
	}
	while (m > 1)
	{
		m = m >> 1;
		BinNode<T>* gr = NULL;
		BinNode<T>* pa = root;
		BinNode<T>* ch = root->getRight();/*root->right;*/
		for (unsigned int i = 0; i < m; i++)
		{
			rotationLeft(gr, pa, ch);
			gr = ch;
			//pa = gr->right;
			pa = gr->getRight();
			if (NULL != pa)
			{
				//ch = pa->right;
				ch = pa->getRight();
			}
			else
			{
				break;
			}
		}
	}
	return;
}

template <class T, unsigned int capacity>
bool BinSearchTree<T, capacity>::dswBalance()
{
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		createBackBone();
		createPerfectTree();
		result = true;
	}
	return result;
}


template <class T, unsigned int capacity>
unsigned int BinSearchTree<T, capacity>::getNodeNum()
{
	return treeNodeNum;
}


template <class T, unsigned int capacity>
void BinSearchTree<T, capacity>::updateBalanceFactors(AVLNode<T>* avlNode, bool insertOrDelete = true, bool leftOrRight = true)
{
	//do nothing for basic class itself
	return;
}


template <class T>
AVLNode<T>::AVLNode()
{
	this->left =  NULL;
	this->right = NULL;
	this->pa = NULL;
	this->balanceValue = 0;
}

template <class T>
AVLNode<T>::AVLNode(const T& data, AVLNode<T> *l = NULL, AVLNode<T> *r = NULL, AVLNode<T> *p = NULL)
{
	this->data = data;
	this->left = l;
	this->right = r;
	this->pa = p;
	this->balanceValue = 0;
}

template<class T>
BinNode<T>* AVLNode<T>::getLeft()
{
	return left;
}

template<class T>
BinNode<T>* AVLNode<T>::getRight()
{
	return right;
}


template<class T>
void AVLNode<T>::setLeft(BinNode<T>* pLeft)
{
	left = (AVLNode<T>*)pLeft;
}

template<class T>
void AVLNode<T>::setRight(BinNode<T>* pRight)
{
	right = (AVLNode<T>*)pRight;
}

template <class T, unsigned int capacity>
bool BinSearchTreeAVL<T, capacity>::insert(T data)
{
	bool rs = false;
	if (isFull())
	{
		rs = false;
	}
	else if (isEmpty())
	{
		this->root = new AVLNode<T>();
		this->root->data = data;
		treeNodeNum++;
		rs = true;
	}
	else
	{
		AVLNode<T>* parent = NULL;
		AVLNode<T>* node = root;
		bool leftOrRight = false; //false means left, true means right
		while (NULL != node)
		{
			parent = node;
			if (data < node->data)
			{
				leftOrRight = false;
				node = /*static_cast<AVLNode<T>*>*/(/*node->left*/(AVLNode<T>*)(node->getLeft()));
			}
			else
			{
				leftOrRight = true;
				node = /*static_cast<AVLNode<T>*>*/(/*node->right*/(AVLNode<T>*)(node->getRight()));
			}
		}
		AVLNode<T>* newNode = new AVLNode<T>();
		newNode->data = data;
		newNode->pa = parent;
		if (leftOrRight)
		{
			//parent->right = newNode;
			parent->setRight(newNode);
		}
		else
		{
			//parent->left = newNode;
			parent->setLeft(newNode);
		}
		treeNodeNum++;
		updateBalanceFactors(newNode);
	}
	return rs;
}


template<class T, unsigned int capacity>
void BinSearchTreeAVL<T, capacity>::setRoot(BinNode<T> *node)
{
	root = static_cast<AVLNode<T>*>(node);
	return;
}

template<class T, unsigned int capacity>
BinNode<T>* BinSearchTreeAVL<T, capacity>::getRoot()
{
	return root;
}

template <class T, unsigned int capacity>
void BinSearchTreeAVL<T, capacity>::updateBalanceFactors4Insert(AVLNode<T>* avlNode)
{
	if (root == avlNode)
	{
		root->balanceValue = 0;
	}
	else
	{
		AVLNode<T> *pa = avlNode->pa;
		if (/*pa->left*/pa->getLeft() == avlNode)
		{
			pa->balanceValue--;
		}
		else
		{
			pa->balanceValue++;
		}
		while ((root != pa) && (pa->balanceValue != 2) && (pa->balanceValue != -2))
		{
			AVLNode<T> *curr = pa;
			pa = pa->pa;
			if (curr->balanceValue == 0)
			{
				return;       //no need to balance
			}
			else if (curr == pa->getLeft()/*pa->left*/)
			{
				pa->balanceValue--;
			}
			else
			{
				pa->balanceValue++;
			}
		}
		if ((pa->balanceValue == 2) || (pa->balanceValue == -2))
		{
			//rotation to AVL balance
			//the new insert node in right tree right
			if ((pa->balanceValue == 2) && (NULL != pa->getRight()/*pa->right*/) && (static_cast<AVLNode<T>*>(/*pa->right*/pa->getRight())->balanceValue == 1))
			{
				//update balance value of pa and ch, then rotation left, last update fa pointer
				pa->balanceValue = 0;
				static_cast<AVLNode<T>*>(/*pa->right*/pa->getRight())->balanceValue = 0;
				AVLNode<T>* grNode = pa->pa;
				AVLNode<T>* paNode = pa;
				AVLNode<T>* chNode = static_cast<AVLNode<T>*>(/*pa->right*/pa->getRight());
				AVLNode<T>* chLNode = static_cast<AVLNode<T>*>(chNode->getLeft())/*chNode->left*/;
				rotationLeft(grNode, paNode, chNode);
				paNode->pa = chNode;
				chNode->pa = grNode;
				if (NULL != chLNode)
				{
					chLNode->pa = paNode;
				}
			}
			//the new insert node in right tree left
			else if ((pa->balanceValue == 2) && (NULL != pa->getRight()/*pa->right*/) && (static_cast<AVLNode<T>*>(pa->getRight()/*pa->right*/)->balanceValue == -1))
			{
				AVLNode<T>* rotationRGrNode = pa;
				AVLNode<T>* rotationRPaNode = static_cast<AVLNode<T>*>(pa->getRight()/*pa->right*/);
				AVLNode<T>* rotationRChNode = static_cast<AVLNode<T>*>(pa->getRight()->getLeft()/*pa->right->left*/);
				int rotationRChNodeBalanceValue = rotationRChNode->balanceValue;
				AVLNode<T>* rotationRChRChNode = static_cast<AVLNode<T>*>(pa->getRight()->getLeft()->getRight()/*pa->right->left->right*/);
				rotationRight(rotationRGrNode, rotationRPaNode, rotationRChNode);
				rotationRChNode->pa = rotationRGrNode;
				rotationRPaNode->pa = rotationRChNode;
				if (NULL != rotationRChRChNode)
				{
					rotationRChRChNode->pa = rotationRPaNode;
				}
				AVLNode<T>* rotationLGrNode = rotationRGrNode->pa;
				AVLNode<T>* rotationLPaNode = rotationRGrNode;
				AVLNode<T>* rotationLChNode = rotationRChNode;
				AVLNode<T>* rotationLChLChNode = static_cast<AVLNode<T>*>(/*rotationLChNode->left*/rotationLChNode->getLeft());
				rotationLeft(rotationLGrNode, rotationLPaNode, rotationLChNode);
				rotationLChNode->pa = rotationLGrNode;
				rotationLPaNode->pa = rotationLChNode;
				if (NULL != rotationLChLChNode)
				{
					rotationLChLChNode->pa = rotationLPaNode;
				}
				if (1 == rotationRChNodeBalanceValue)
				{
					rotationRGrNode->balanceValue = -1;
					rotationRPaNode->balanceValue = 0;
					rotationRChNode->balanceValue = 0;
				}
				else if (-1 == rotationRChNodeBalanceValue)
				{
					rotationRGrNode->balanceValue = 0;
					rotationRPaNode->balanceValue = 1;
					rotationRChNode->balanceValue = 0;
				}
				else
				{
					rotationRGrNode->balanceValue = 0;
					rotationRPaNode->balanceValue = 0;
					rotationRChNode->balanceValue = 0;
				}

			}
			//the new insert node in left tree left
			else if ((pa->balanceValue == -2) && (NULL != pa->getLeft()/*pa->left*/) && (static_cast<AVLNode<T>*>(pa->getLeft()/*pa->left*/)->balanceValue == -1))
			{
				//update balance value of pa and ch, then rotation right, last update fa pointer
				static_cast<AVLNode<T>*>(pa->getLeft()/*pa->left*/)->balanceValue = 0;
				pa->balanceValue = 0;
				AVLNode<T>* grNode = pa->pa;
				AVLNode<T>* paNode = pa;
				AVLNode<T>* chNode = static_cast<AVLNode<T>*>(pa->getLeft()/*pa->left*/);
				AVLNode<T>* chRNode = static_cast<AVLNode<T>*>(chNode->getRight())/*chNode->right*/;
				rotationRight(grNode, paNode, chNode);
				paNode->pa = chNode;
				chNode->pa = grNode;
				if (NULL != chRNode)
				{
					chRNode->pa = paNode;
				}

			}
			//the new insert node in left tree right
			else if ((pa->balanceValue == -2) && (NULL != pa->getLeft()/*pa->left*/) && (/*pa->left*/static_cast<AVLNode<T>*>(pa->getLeft())->balanceValue == 1))
			{
				AVLNode<T>* rotationLGrNode = pa;
				AVLNode<T>* rotationLPaNode = static_cast<AVLNode<T>*>(pa->getLeft()/*pa->left*/);
				AVLNode<T>* rotationLChNode = static_cast<AVLNode<T>*>(pa->getLeft()->getRight()/*pa->left->right*/);
				int rotationLChNodeBalanceValue = rotationLChNode->balanceValue;
				AVLNode<T>* rotationLChLChNode = static_cast<AVLNode<T>*>(pa->getLeft()->getRight()->getLeft()/*pa->left->right->left*/);
				rotationLeft(rotationLGrNode, rotationLPaNode, rotationLChNode);
				rotationLChNode->pa = rotationLGrNode;
				rotationLPaNode->pa = rotationLChNode;
				if (NULL != rotationLChLChNode)
				{
					rotationLChLChNode->pa = rotationLPaNode;
				}
				AVLNode<T>* rotationRGrNode = rotationLGrNode->pa;
				AVLNode<T>* rotationRPaNode = rotationLGrNode;
				AVLNode<T>* rotationRChNode = rotationLChNode;
				AVLNode<T>* rotationRChRChNode = static_cast<AVLNode<T>*>(rotationRChNode->getRight()/*rotationRChNode->right*/);
				rotationRight(rotationRGrNode, rotationRPaNode, rotationRChNode);
				rotationRChNode->pa = rotationRGrNode;
				rotationRPaNode->pa = rotationRChNode;
				if (NULL != rotationRChRChNode)
				{
					rotationRChRChNode->pa = rotationRPaNode;
				}
				if (1 == rotationLChNodeBalanceValue)
				{
					rotationLGrNode->balanceValue = 0;
					rotationLPaNode->balanceValue = -1;
					rotationLChNode->balanceValue = 0;
				}
				else if (-1 == rotationLChNodeBalanceValue)
				{
					rotationLGrNode->balanceValue = 1;
					rotationLPaNode->balanceValue = 0;
					rotationLChNode->balanceValue = 0;
				}
				else
				{
					rotationLGrNode->balanceValue = 0;
					rotationLPaNode->balanceValue = 0;
					rotationLChNode->balanceValue = 0;
				}
			}
			else
			{
				//should be error case
			}
		}
	}
	return;
}

template <class T, unsigned int capacity>
void BinSearchTreeAVL<T, capacity>::updateBalanceFactors4Delete(AVLNode<T>* avlNode, bool leftOrRight)
{
	//For delete, the avlNode should be the pa Node, leftOrRight means the del node is 
	//pa's left or right
	if (NULL == avlNode)
	{

	}
	else
	{
		if (leftOrRight)     //Left
		{
			if (0 == avlNode->balanceValue)
			{
				avlNode->balanceValue = 1;
			}
			else if (-1 == avlNode->balanceValue)
			{
				avlNode->balanceValue = 0;
				//Go up
				AVLNode<T>* pa = avlNode->pa;
				if (NULL != pa)
				{
					if (avlNode == pa->getLeft())
					{
						updateBalanceFactors4Delete(pa, true);
					}
					else
					{
						updateBalanceFactors4Delete(pa, false);
					}
				}
			}
			else
			{
				//if (null == dynamic_cast<AVLNode<T>*>(avlNode->getRight()))
				//{
				//	avlNode->balanceValue = 0;
				//}
				//rotation
				//First case, single rotation left
				if (dynamic_cast<AVLNode<T>*>(avlNode->getRight())->balanceValue == 0)
				{
					AVLNode<T>* gr = avlNode->pa;
					AVLNode<T>* ch = dynamic_cast<AVLNode<T>*>(avlNode->getRight());
					AVLNode<T>* chLeft = dynamic_cast<AVLNode<T>*>(ch->getLeft());
					rotationLeft(gr, avlNode, ch);
					avlNode->balanceValue = 1;
					ch->balanceValue = -1;
					//Set pa pointer
					avlNode->pa = ch;
					ch->pa = gr;
					if (NULL != chLeft)
						chLeft->pa = avlNode;
					//do not need Go up, because the subtree height not changed
				}
				//Second case, still single rotation left
				else if (dynamic_cast<AVLNode<T>*>(avlNode->getRight())->balanceValue == 1)
				{
					AVLNode<T>* gr = avlNode->pa;
					AVLNode<T>* ch = dynamic_cast<AVLNode<T>*>(avlNode->getRight());
					AVLNode<T>* chLeft = dynamic_cast<AVLNode<T>*>(ch->getLeft());
					rotationLeft(gr, avlNode, ch);
					avlNode->balanceValue = 0;
					ch->balanceValue = 0;
					//Set pa pointer
					if (NULL != chLeft)
						chLeft->pa = avlNode;
					avlNode->pa = ch;
					ch->pa = gr;
					//Need Go up, becuase the subtree height changed (-1)
					if (NULL != gr)
					{
						if (ch == gr->getLeft())
						{
							updateBalanceFactors4Delete(gr, true);
						}
						else
						{
							updateBalanceFactors4Delete(gr, false);
						}
					}
				}
				//Need double rotation
				else
				{
					AVLNode<T>* grPa = avlNode->pa;
					//bool leftOrRightFlag = false;
					//if (grPa != NULL)
					//{
					//	if (grPa->getLeft() == avlNode)
					//	{
					//		leftOrRightFlag = false;
					//	}
					//	else
					//	{
					//		leftOrRightFlag = true;
					//	}
					//}
					//else
					//{
					//	setRoot(ch);
					//}
					AVLNode<T>* gr = avlNode;
					AVLNode<T>* pa = dynamic_cast<AVLNode<T>*>(gr->getRight());
					AVLNode<T>* ch = dynamic_cast<AVLNode<T>*>(pa->getLeft());
					int oldChBalanceValue = ch->balanceValue;
					AVLNode<T>* oldChLeft = dynamic_cast<AVLNode<T>*>(ch->getLeft());
					AVLNode<T>* oldChRight = dynamic_cast<AVLNode<T>*>(ch->getRight());
					rotationRight(gr, pa, ch);
					rotationLeft(grPa, gr, ch);
					//if (NULL != grPa)
					//{
					//	if (leftOrRightFlag)
					//	{
					//		grPa->setRight(ch);
					//	}
					//	else
					//	{
					//		grPa->setLeft(ch);
					//	}
					//}
					//set pa pointer
					if (NULL != oldChLeft)
						oldChLeft->pa = gr;
					if (NULL != oldChRight)
						oldChRight->pa = pa;
					pa->pa = ch;
					gr->pa = ch;
					ch->pa = grPa;
					//set balance value
					ch->balanceValue = 0;
					if (oldChBalanceValue == 0)
					{
						gr->balanceValue = 0;
						pa->balanceValue = 0;
					}
					else if (oldChBalanceValue == -1)
					{
						gr->balanceValue = 0;
						pa->balanceValue = 1;
					}
					else
					{
						gr->balanceValue = -1;
						pa->balanceValue = 0;
					}
					//Need go up, because the subtree height changed (-1)
					if (NULL != grPa)
					{
						if (ch == grPa->getLeft())
						{
							updateBalanceFactors4Delete(grPa, true);
						}
						else
						{
							updateBalanceFactors4Delete(grPa, false);
						}
					}
				}
			}
		}
		else                 //Right
		{
			if (0 == avlNode->balanceValue)
			{
				avlNode->balanceValue = -1;
			}
			else if (-1 == avlNode->balanceValue)
			{
				//avlNode->balanceValue = -2;
				//rotation
				//First case, single rotation right
				if (dynamic_cast<AVLNode<T>*>(avlNode->getLeft())->balanceValue == 0)
				{
					AVLNode<T>* gr = avlNode->pa;
					AVLNode<T>* ch = dynamic_cast<AVLNode<T>*>(avlNode->getLeft());
					AVLNode<T>* chRight = dynamic_cast<AVLNode<T>*>(ch->getRight());
					rotationRight(gr, avlNode, ch);
					avlNode->balanceValue = -1;
					ch->balanceValue = 1;
					//Set pa pointer
					if(NULL != chRight)
						chRight->pa = avlNode;
					avlNode->pa = ch;
					ch->pa = gr;
					//do not need Go up, because the subtree height not changed
				}
				//Second case, still single rotation right,need go up
				else if (dynamic_cast<AVLNode<T>*>(avlNode->getLeft())->balanceValue == -1)
				{
					AVLNode<T>* gr = avlNode->pa;
					AVLNode<T>* ch = dynamic_cast<AVLNode<T>*>(avlNode->getLeft());
					AVLNode<T>* chRight = dynamic_cast<AVLNode<T>*>(ch->getRight());
					rotationRight(gr, avlNode, ch);
					avlNode->balanceValue = 0;
					ch->balanceValue = 0;
					//Set pa pointer
					if (NULL != chRight)
						chRight->pa = avlNode;
					avlNode->pa = ch;
					ch->pa = gr;

					//Need Go up, becuase the subtree height changed (-1)
					if (NULL != gr)
					{
						if (ch == gr->getLeft())
						{
							updateBalanceFactors4Delete(gr, true);
						}
						else
						{
							updateBalanceFactors4Delete(gr, false);
						}
					}
				}
				//Double rotation
				else
				{
					AVLNode<T>* grPa = avlNode->pa;
					//bool leftOrRightFlag = false;
					//if (grPa != NULL)
					//{
					//	if (grPa->getLeft() == avlNode)
					//	{
					//		leftOrRightFlag = false;
					//	}
					//	else
					//	{
					//		leftOrRightFlag = true;
					//	}
					//}
					//AVLNode<T>* grPa = avlNode->pa;
					AVLNode<T>* gr = avlNode;
					AVLNode<T>* pa = dynamic_cast<AVLNode<T>*>(gr->getLeft());
					AVLNode<T>* ch = dynamic_cast<AVLNode<T>*>(pa->getRight());
					int oldChBalanceValue = ch->balanceValue;
					AVLNode<T>* oldChLeft = dynamic_cast<AVLNode<T>*>(ch->getLeft());
					AVLNode<T>* oldChRight = dynamic_cast<AVLNode<T>*>(ch->getRight());
					rotationLeft(gr, pa, ch);
					rotationRight(grPa, gr, ch);
					//if (NULL != grPa)
					//{
					//	if (leftOrRightFlag)
					//	{
					//		grPa->setRight(ch);
					//	}
					//	else
					//	{
					//		grPa->setLeft(ch);
					//	}
					//}
					//else
					//{
					//	setRoot(ch);
					//}
					//set pa pointer
					if(NULL != oldChLeft)
						oldChLeft->pa = pa;
					if (NULL != oldChRight)
						oldChRight->pa = gr;
					pa->pa = ch;
					gr->pa = ch;
					ch->pa = grPa;
					//set balance value
					ch->balanceValue = 0;
					if (oldChBalanceValue == 0)
					{
						gr->balanceValue = 0;
						pa->balanceValue = 0;
					}
					else if (oldChBalanceValue == -1)
					{
						gr->balanceValue = 1;
						pa->balanceValue = 0;
					}
					else
					{
						gr->balanceValue = 0;
						pa->balanceValue = -1;
					}
					//Need go up, because the subtree height changed (-1)
					if (NULL != grPa)
					{
						if (ch == grPa->getLeft())
						{
							updateBalanceFactors4Delete(grPa, true);
						}
						else
						{
							updateBalanceFactors4Delete(grPa, false);
						}
					}
				}
			}
			else
			{
				avlNode->balanceValue = 0;
				//Go up
				AVLNode<T>* pa = avlNode->pa;
				if (NULL != pa)
				{
					if (avlNode == pa->getLeft())
					{
						updateBalanceFactors4Delete(pa, true);
					}
					else
					{
						updateBalanceFactors4Delete(pa, false);
					}
				}
			}
		}
	}
	return;
}



template <class T, unsigned int capacity>
void BinSearchTreeAVL<T, capacity>::updateBalanceFactors(AVLNode<T>* avlNode, bool insertOrDelete, bool leftOrRight)
{
	//false means delete, true means insert
	if (insertOrDelete)
	{
		updateBalanceFactors4Insert(avlNode);
	}
	else
	{
		updateBalanceFactors4Delete(avlNode, leftOrRight);
	}
	return;
}



template <class T, unsigned int capacity>
bool BinSearchTreeAVL<T, capacity>::scopeOrder()
{
	bool result = false;
	if (isEmpty())
	{
		result = false;
	}
	else
	{
		queueHelper = new LinkQueue<AVLNode<T>*, capacity>();
		queueHelper->enQueue(root);
		while (!(queueHelper->isEmpty()))
		{
			AVLNode<T>* temp = NULL;
			queueHelper->deQueue(temp);
			cout << "ScopeOrder: The value is :" << temp->data << endl;
			if (NULL != temp->getLeft())
			{
				queueHelper->enQueue(dynamic_cast<AVLNode<T>*>(temp->getLeft()));
			}
			if (NULL != temp->getRight())
			{
				queueHelper->enQueue(dynamic_cast<AVLNode<T>*>(temp->getRight()));
			}
		}
		if (NULL != queueHelper)
		{
			delete queueHelper;
			queueHelper = NULL;
		}
		result = true;
	}
	return result;
}