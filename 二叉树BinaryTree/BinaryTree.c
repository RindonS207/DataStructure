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

/* ����һ�ö����� */
static BinaryNode* CreateBinaryTree()
{
	BinaryNode* tree;
	int value,count,input;
	printf("������Ҫ�����������ܽڵ�����\n");
	scanf("%d",&value);
	if (value < 1) {
		printf("��������Чֵ��\n");
		return NULL;
	}
	else {
		printf("��������ڵ��ֵ��\n");
		scanf("%d",&input);
		tree = (BinaryNode*)malloc(sizeof(BinaryNode));
		if (tree == NULL) {
			printf("�ڴ�����ʧ�ܣ�\n");
			return NULL;
		}
		tree->Parent = NULL;
		tree->data = input;
		printf("������ڵ��id:\n");
		scanf("%d",&input);
		tree->id = input;
		tree->Lchild = NULL;
		tree->Rchild = NULL;
		if (value == 1) {
			printf("��������ɡ�\n");
			return tree;
		}
		count = CreateBinaryTreeNode(tree, 1, value);
	}
	if (count != value) {
		printf("������Ԥ��֮������⣡\n");
		return NULL;
	}
	return tree;
}
/* �������еĽڵ� */
static int CreateBinaryTreeNode(BinaryNode* parent, int CountOwned, int CountNeeded)
{
	int value,flag,x,input;
	printf("������ %d(ֵ) %d(id) ����Ҫ�ĺ�������(����2)��\n",parent->data,parent->id);
	scanf("%d",&value);
	if (value < 0 || value > 2 || CountOwned + value > CountNeeded) {
		printf("������һ����Ч��ֵ��\n");
		return CountOwned;
	}if (value == 0) {
		return CountOwned;
	}
	printf("�������һ��Ҫ��ӵ�λ�ã�0��ʾ��1��ʾ�ң�:\n");
	scanf("%d", & flag);
	CountOwned += value;
	for (x = 0; x < value; x++) {
		BinaryNode* newnode = (BinaryNode*)malloc(sizeof(BinaryNode));
		if (newnode == NULL) {
			printf("������Ԥ��֮������飡\n");
			return CountOwned;
		}
		printf("������ %d(ֵ) %d(id) ��%s���ӵ�ֵ:\n", parent->data, parent->id,(flag ? "��" : "��"));
		scanf("%d", &input);
		newnode->data = input;
		newnode->Parent = parent;
		printf("������ %d(ֵ) %d(id) ��%s���ӵ� id:\n", parent->data, parent->id, (flag ? "��" : "��"));
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
/* ��ӡ���������������Ƿ�ݹ��ӡ�Լ���ӡ������ģʽ:
    ǰ�����������������������*/
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
/* ��ӡ�����ڵ����Ϣ */
static void PrintBinaryNode(BinaryNode* node)
{
	if (node->Parent == NULL) {
		printf("%d(ֵ) %d(id) ����ڵ��Ǹ��ڵ㡣\n",node->data,node->id);
	}
	else {
		printf("%d(ֵ) %d(id) ����ڵ�ĸ�ĸ��:%d(ֵ) %d(id)\n", node->data, node->id,node->Parent->data,node->Parent->id);
	}
	if (node->Lchild == NULL && node->Rchild == NULL) {
		printf("%d(ֵ) %d(id) ����ڵ���Ҷ�ڵ㣬û�к��ӡ�\n", node->data, node->id);
	}
	else {
		printf("%d(ֵ) %d(id) ����ڵ�ӵ��%s�����ӣ�\n",node->data,node->id,((node->Lchild && node->Rchild ? 1 : 0) ? "��" : "һ"));
		if (node->Lchild) {
			printf("���ӣ�%d(ֵ) %d(id)\n",node->Lchild->data,node->Lchild->id);
		}
		if (node->Rchild) {
			printf("�Һ��ӣ�%d(ֵ) %d(id)\n",node->Rchild->data,node->Rchild->id);
		}
	} 
}
