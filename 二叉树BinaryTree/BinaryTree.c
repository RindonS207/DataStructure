#include<stdio.h>
#include<stdlib.h>
#ifndef BOOL_INDLUDED
#include "BOOL_DEF.c"
#endif

#define BINARY_TREE_INCLUDED 1

typedef struct BinaryNode BinaryNode;
typedef enum ForeachMode ForeachMode;
static BinaryNode* CreateBinaryTree();
static int CreateBinaryTreeNode(BinaryNode* parent,int CountOwned,int CountNeeded);
static void PrintBinaryTree(BinaryNode* tree,BOOL recursion,ForeachMode mode);
static void PrintBinaryNode(BinaryNode* node);

typedef struct BinaryNode {
	int data;
	int id;
	BinaryNode* Lchild;
	BinaryNode* Rchild;
	BinaryNode* Parent;
}BinaryNode;

typedef enum ForeachMode {
	PreOrder = 0,
	InOrder = 1,
	PostOrder = 2
}ForeachMode;

/* 创建一棵二叉树 */
static BinaryNode* CreateBinaryTree()
{
	BinaryNode* tree;
	int value,count,input;
	printf("请输入要创建的树的总节点数：\n");
	scanf("%d",&value);
	if (value < 1) {
		printf("请输入有效值。\n");
		return NULL;
	}
	else {
		printf("请输入根节点的值：\n");
		scanf("%d",&input);
		tree = (BinaryNode*)malloc(sizeof(BinaryNode));
		if (tree == NULL) {
			printf("内存申请失败！\n");
			return NULL;
		}
		tree->Parent = NULL;
		tree->data = input;
		printf("输入根节点的id:\n");
		scanf("%d",&input);
		tree->id = input;
		tree->Lchild = NULL;
		tree->Rchild = NULL;
		if (value == 1) {
			printf("树创建完成。\n");
			return tree;
		}
		count = CreateBinaryTreeNode(tree, 1, value);
	}
	if (count != value) {
		printf("发生了预期之外的意外！\n");
		return NULL;
	}
	return tree;
}
/* 创建树中的节点 */
static int CreateBinaryTreeNode(BinaryNode* parent, int CountOwned, int CountNeeded)
{
	int value,flag,x,input;
	printf("请输入 %d(值) %d(id) 所需要的孩子数量(至多2)：\n",parent->data,parent->id);
	scanf("%d",&value);
	if (value < 0 || value > 2 || CountOwned + value > CountNeeded) {
		printf("请输入一个有效的值。\n");
		return CountOwned;
	}if (value == 0) {
		return CountOwned;
	}
	printf("请输入第一次要添加的位置（0表示左，1表示右）:\n");
	scanf("%d", & flag);
	CountOwned += value;
	for (x = 0; x < value; x++) {
		BinaryNode* newnode = (BinaryNode*)malloc(sizeof(BinaryNode));
		if (newnode == NULL) {
			printf("发生了预期之外的事情！\n");
			return CountOwned;
		}
		printf("请输入 %d(值) %d(id) 的%s孩子的值:\n", parent->data, parent->id,(flag ? "右" : "左"));
		scanf("%d", &input);
		newnode->data = input;
		newnode->Parent = parent;
		printf("请输入 %d(值) %d(id) 的%s孩子的 id:\n", parent->data, parent->id, (flag ? "右" : "左"));
		scanf("%d", &input);
		newnode->id = input;
		newnode->Rchild = NULL;
		newnode->Lchild = NULL;
		if (!flag) {
			flag = 1;
			parent->Lchild = newnode;
		}
		else {
			flag = 0;
			parent->Rchild = newnode;
		}
		if (CountNeeded != CountOwned) {
			CountOwned = CreateBinaryTreeNode(newnode, CountOwned, CountNeeded);
		}
	}
	return CountOwned;
}
/* 打印二叉树，并决定是否递归打印以及打印遍历的模式:
    前序遍历，中序遍历，后序遍历*/
static void PrintBinaryTree(BinaryNode* tree, BOOL recursion, ForeachMode mode)
{
	if (tree == NULL) {
		return;
	}
	if (recursion) {
		if (mode == PreOrder) {
			PrintBinaryNode(tree);
			PrintBinaryTree(tree->Lchild,true,PreOrder);
			PrintBinaryTree(tree->Rchild,true,PreOrder);
		}
		else if (mode == InOrder) {
			PrintBinaryTree(tree->Lchild, true, InOrder);
			PrintBinaryNode(tree);
			PrintBinaryTree(tree->Rchild, true, InOrder);
		}
		else {
			PrintBinaryTree(tree->Lchild, true, PostOrder);
			PrintBinaryTree(tree->Rchild, true, PostOrder);
			PrintBinaryNode(tree);
		}
	}
	else {
		PrintBinaryNode(tree);
	}
}
/* 打印单个节点的信息 */
static void PrintBinaryNode(BinaryNode* node)
{
	if (node->Parent == NULL) {
		printf("%d(值) %d(id) 这个节点是根节点。\n",node->data,node->id);
	}
	else {
		printf("%d(值) %d(id) 这个节点的父母是:%d(值) %d(id)\n", node->data, node->id,node->Parent->data,node->Parent->id);
	}
	if (node->Lchild == NULL && node->Rchild == NULL) {
		printf("%d(值) %d(id) 这个节点是叶节点，没有孩子。\n", node->data, node->id);
	}
	else {
		printf("%d(值) %d(id) 这个节点拥有%s个孩子：\n",node->data,node->id,((node->Lchild && node->Rchild ? 1 : 0) ? "两" : "一"));
		if (node->Lchild) {
			printf("左孩子：%d(值) %d(id)\n",node->Lchild->data,node->Lchild->id);
		}
		if (node->Rchild) {
			printf("右孩子：%d(值) %d(id)\n",node->Rchild->data,node->Rchild->id);
		}
	} 
}
