#ifndef _BIN_SEQ_TREE_
#define _BIN_SEQ_TREE_

struct BiNode
{
	int data;                 //data
	BiNode* lNode;            //left node
	BiNode* rNode;            //right node
};

class BinSeqTree
{
public:
	BinSeqTree();
	void insertNode(int data);
	void deleteNode(int data);
	void deleteNodeViaCopy(int data);
	bool isEmpty();
	void preOrder();
	void midOrder();
	void midOrder(int*& pArray);
	void lastOrder();
	void breadthFirstOrder();
	void balanceTree(int* pArray, int first, int last);
	void destoryTree();
	void dswBalance(int nodeNum);
private:
	void insertLeft(BiNode* node, int data);
	void insertRight(BiNode* node, int data);
	void deleteTheNode(BiNode*& parent, BiNode*& node, int lOrR);
	void deleteRoot();
	void deleteTheNodeViaCopy(BiNode*& parent, BiNode*& node, int lOrR);
	void deleteRootViaCopy();
	void preOrder(BiNode* node);
	void midOrder(BiNode* node);
	void midOrder(BiNode* node, int*& pArray);
	void lastOrder(BiNode* node);
	void destroyNode(BiNode* node);
	void createBackbone();
	void createPerfectTree(int nodeNum);
	void rotateRight(BiNode*& grandParent, BiNode*& parent, BiNode*& child);
	void rotateLeft(BiNode*& grandParent, BiNode*& parent, BiNode*& child);
	BiNode* root;
};

#endif // !_BIN_SEQ_TREE_

