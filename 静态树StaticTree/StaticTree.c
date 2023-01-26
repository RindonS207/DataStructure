#include<stdio.h>
#include<stdlib.h>

#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif

#define S_TREE_INCLUDED 1
#define DEFAULT_SIZE 100
/* 静态多叉树 */
typedef enum ForeachMode ForeachMode;
typedef struct StaticTree StaticTree;
typedef struct ST_NODE ST_NODE;
typedef struct ChildLink ChildLink;
static StaticTree* CreateStaticTree();
static void PrintStaticTree(StaticTree* tree);
static void PrintStaticTreeNode(StaticTree* tree,int index,BOOL recursion);
static BOOL RemoveNodeFromStaticTree(StaticTree* tree , int index , BOOL recutsion);
static int AddNodeToStaticTree(StaticTree* tree, int Monindex, int CountOwned, int CountNeeded);
static int GetIndexByValue(StaticTree* tree, int start, int value );
static int MallocFromStaticTree(StaticTree* tree);
static void FreeFromStaticTree(StaticTree* tree,int index);
static int CreateStaticTreeNode(StaticTree* tree, int MonIndex, int CountOwned, int CountNeeded);

typedef struct ST_NODE
{
	int data;
	short int NextIndex;
	ChildLink *Children;
	short int Parent;
}ST_NODE;

typedef struct ChildLink {
	int index;
	ChildLink* Next;
}ChildLink;

typedef struct StaticTree
{
	/* 索引0总是根节点 */
	ST_NODE nodes[DEFAULT_SIZE];
	unsigned short int IdleSpaceIndex;
}StaticTree;

/* 创建静态多叉树 */
static StaticTree* CreateStaticTree() {
	char inputchar;
	int nodeCount=0,input,nowselectIndex=0,x,count,
		*firstChildren;
	ChildLink* link,*newlink;
	StaticTree* tree = (StaticTree*)malloc(sizeof(StaticTree));
	if (tree == NULL) {
		printf("\n内存申请失败了！\n");
		return NULL;
	}
	printf("请输入创建静态多叉树的节点总数量:\n");
	scanf("%d",&nodeCount);
	if (nodeCount < 1 || nodeCount > DEFAULT_SIZE) {
		free(tree);
		printf("请输入一个有效的值。\n");
		return NULL;
	}
	tree->IdleSpaceIndex = 1;
	for (x = 0; x < DEFAULT_SIZE-1; x++) {
		tree->nodes[x].NextIndex = x + 1;
		tree->nodes[x].Parent = -1;
	}
	tree->nodes[DEFAULT_SIZE - 1].NextIndex = -1;
	/* 创建根节点 */
	printf("请输入端节点的值:\n");
	scanf("%d", &input);
	tree->nodes[nowselectIndex].data = input;
	tree->nodes[0].Children = (ChildLink*)malloc(sizeof(ChildLink));
	tree->nodes[0].Children->index = -1;
	tree->nodes[0].Children->Next = NULL;
	if (nodeCount == 1) {
		
		printf("1个节点的树构建完成。\n");
		return tree;
	}
	else {
		count =  CreateStaticTreeNode(tree, 0, 1, nodeCount);
	}
	if (count == nodeCount) {
		printf("树创建完成。\n");
	}
	else {
		free(tree);
		printf("发生了预期之外的事情，树创建失败。\n");
	}
	return tree;
}
/* 打印多叉树 */
static void PrintStaticTree(StaticTree* tree)
{
	PrintStaticTreeNode(tree, 0, true);
}
/* 打印单个节点的信息 recursion决定是否打印该节点的子节点 */
static void PrintStaticTreeNode(StaticTree* tree, int index, BOOL recursion) {
	ChildLink* link;
	int childCount = 1,*arr,x;
	printf("\n");
	if (tree == NULL || index < 0 || index >= DEFAULT_SIZE) {
		printf("请输入有效的索引值。\n");
		return;
	}
	if (index == 0) {
		printf("节点下标 0 值为 %d ，这个节点是根节点。\n",tree->nodes[0].data);
	}
	if (tree->nodes[index].Children->index == -1) {
		printf("节点下标 %d 值为 %d ，这个节点是叶节点。\n",index,tree->nodes[index].data);
		if (index == 0) {
			printf("这个节点没有父母。\n");
		}
		else {
			printf("这个节点的父母是下标 %d 值为 %d\n", tree->nodes[index].Parent, tree->nodes[tree->nodes[index].Parent].data);
		}
	}
	else {
		link = tree->nodes[index].Children;
		while (link->Next != NULL) {
			childCount += 1;
			link = link->Next;
		}
		arr = (int*)calloc(childCount, sizeof(int));
		link = tree->nodes[index].Children;
		for (x = 0; x < childCount; x++) {
			
			arr[x] = link->index;
			link = link->Next;
		}
		printf("节点下标 %d 值为 %d ，这个节点拥有 %d 个孩子。\n", index, tree->nodes[index].data, childCount);
		if (index == 0) {
			printf("这个节点没有父母。\n");
		}
		else {
			printf("这个节点的父母是下标 %d 值为 %d\n", tree->nodes[index].Parent, tree->nodes[tree->nodes[index].Parent].data);
		}
		printf("他的孩子分别是：\n");
		for (x = 0; x < childCount; x++) {
			printf("下标:%d  值:%d\n",arr[x],tree->nodes[arr[x]].data);
		}
		printf("\n");
		if (recursion) {
			for (x = 0; x < childCount; x++) {
				PrintStaticTreeNode(tree, arr[x], recursion);
			}
		}
		free(arr);
	}
}
/* 在多叉树内申请“内存” */
static int MallocFromStaticTree(StaticTree* tree)
{
	int temp;
	if (tree == NULL || tree->IdleSpaceIndex == -1) {
		printf("树不存在或无空闲空间。\n");
		return -1;
	}
	temp = tree->IdleSpaceIndex;
	tree->IdleSpaceIndex = tree->nodes[temp].NextIndex;
	return temp;
}
/* 释放指定索引的“内存” */
static void FreeFromStaticTree(StaticTree* tree, int index)
{
	if (index < 1 || index > DEFAULT_SIZE) {
		printf("请传入有效值。\n");
		return;
	}
	else {
		tree->nodes[index].NextIndex = tree->IdleSpaceIndex;
		tree->IdleSpaceIndex = index;
	}
}
/* 自身当前索引，自身父母索引，
  目前已拥有节点总数，当前所需节点总数 */
static int CreateStaticTreeNode(StaticTree* tree, int MonIndex,int CountOwned, int CountNeeded) 
{
	if (tree == NULL) {
		printf("请输入有效值。\n");
		return CountOwned;
	}
	int value,x,newindex,input;
	ChildLink* link;
	printf("请输入 %d(值) %d(下标) 所需要的孩子节点数。\n",tree->nodes[MonIndex].data,MonIndex);
	scanf("%d",&value);
	if (CountOwned + value > CountNeeded) {
		printf("数值超过预期，构建取消。\n");
		free(tree);
		return CountOwned;
	}
	else if (value == 0) {
		return CountOwned;
	}
	else {
		CountOwned += value;
		for (x = 0; x < value; x++) {
			newindex = MallocFromStaticTree(tree);
			printf("请输入 %d(索引) 的第 %d 个孩子的值。\n",MonIndex,x+1);
			scanf("%d", &input);

			if (tree->nodes[MonIndex].Children->index == -1) {
				tree->nodes[MonIndex].Children->index = newindex;
			}
			else {
				link = tree->nodes[MonIndex].Children;
				while (link->Next != NULL) {
					link = link->Next;
				}
				ChildLink* newlink = (ChildLink*)malloc(sizeof(ChildLink));
				if (newlink == NULL) {
					printf("申请内存失败，销毁树。\n");
					free(tree);
					return CountOwned;
				}
				newlink->index = newindex;
				newlink->Next = NULL;
				link->Next = newlink;
			}

			tree->nodes[newindex].data = input;
			tree->nodes[newindex].Parent = MonIndex;

			tree->nodes[newindex].Children = (ChildLink*)malloc(sizeof(ChildLink));
			tree->nodes[newindex].Children->index = -1;
			tree->nodes[newindex].Children->Next = NULL;

			if (CountOwned < CountNeeded) {
				CountOwned = CreateStaticTreeNode(tree, newindex, CountOwned, CountNeeded);
			}
		}
	}
	return CountOwned;
}
/* 根据给出的元素值，开始位置，查找第一个符合条件元素所在索引(前序遍历) */
static int GetIndexByValue(StaticTree* tree , int start, int value)
{
	ChildLink* link;
	int x,data;
	if (tree == NULL) {
		printf("请传入一个有效的树对象。\n");
		return -1;
	}
	if (tree->nodes[start].data == value) {
		return start;
	}
	else if (tree->nodes[start].Children->index == -1) {
		return -1;
	}
	while (true) {
		if (tree->nodes[start].data == value) {
			return start;
		}
		for ( link = tree->nodes[start].Children; link != NULL; link = link->Next) {
			x = link->index;

			data = GetIndexByValue(tree, x, value);

			if (data != -1) {
				return data;
			}
		}
		return -1;
	}
}
/* 删除指定索引的节点，并决定是否连子节点一起删除 */
static BOOL RemoveNodeFromStaticTree(StaticTree* tree, int index, BOOL recutsion)
{
	ChildLink* link,*loopPointer;
	int monIndex,brotherIndex=0,x,childCount=1,*childrenIndex;
	if (tree == NULL || index < 0 || index > DEFAULT_SIZE) {
		printf("请输入有意义的数据。\n");
		return false;
	}
	if (index == 0 && !recutsion) {
		printf("清除根节点时请使用递归模式。\n");
		return false;
	}
	monIndex = tree->nodes[index].Parent;
	link = tree->nodes[monIndex].Children;
	while (link != NULL) {
		if (link->index == index) {
			if (!brotherIndex) {
				link->index = -1;
			}
			else {
				for (x = 0 , loopPointer = tree->nodes[monIndex].Children; x < brotherIndex; x++) {

					loopPointer->Next = link->Next;
					
					free(link);
				}
			}
			break;
		}
		link = link->Next;
		brotherIndex += 1;
	}
	FreeFromStaticTree(tree, index);
	if (tree->nodes[index].Children->index != -1) {
		link = tree->nodes[index].Children;
		while (link->Next != NULL) {
			childCount += 1;
			link = link->Next;
		}
		childrenIndex = (int*)calloc(childCount, sizeof(int));
		for (x = 0 , link = tree->nodes[index].Children; x < childCount; x++) {
			childrenIndex[x] = link->index;
			link = link->Next;
		}
		if (!recutsion) {
			link = tree->nodes[monIndex].Children;
			if (link->index != NULL) {
				link = link->Next;
			}
		}
		for (x = 0; x < childCount; x++) {
			int Cindex = childrenIndex[x];
			if (!recutsion) {
				tree->nodes[Cindex].Parent = monIndex;
				if (link->index == -1) {
					link->index = Cindex;
					continue;
				}
				else {
					ChildLink* newlink = (ChildLink*)malloc(sizeof(ChildLink));
					newlink->index = Cindex;
					newlink->Next = NULL;
					link->Next = newlink;
					link = newlink;
				}
			}
			else {
				if (tree->nodes[Cindex].Children->index != -1) {
					RemoveNodeFromStaticTree(tree, Cindex, recutsion);
				}
				else {
					FreeFromStaticTree(tree, Cindex);
				}
			}
		}
	}
	return true;
}
/* 向指定索引添加孩子节点 */
static int AddNodeToStaticTree(StaticTree* tree, int Monindex, int CountOwned, int CountNeeded)
{
	ChildLink* link;
	int value,childCount,x,input,newIndex;
	if (tree == NULL || Monindex < 0 || Monindex > DEFAULT_SIZE) {
		return CountOwned;
	}
	link = tree->nodes[Monindex].Children;
	if (tree->nodes[Monindex].Children->index == -1) {
		childCount = 0;
		printf("请输入 %d(值) %d(下标) 节点所需要的孩子数量：\n", tree->nodes[Monindex].data, Monindex);
	}
	else {
		childCount = 1;
		
		while (link->Next != NULL) {
			link = link->Next;
			childCount += 1;
		}
		printf("请输入 %d(值) %d(下标) 节点所需要添加的孩子数量：\n", tree->nodes[Monindex].data, Monindex);
	}
	scanf("%d",&value);
	if (CountOwned + value > CountNeeded || value < 0) {
		printf("数量超过预期，添加取消。\n");
		return CountOwned;
	}
	if (value == 0) {
		return CountOwned;
	}
	CountOwned += value;
	for (x = 0; x < value; x++) {
		newIndex = MallocFromStaticTree(tree);
		printf("请输入 %d(索引) 的第 %d 个孩子的值。\n", Monindex, x + 1);
		scanf("%d",&input);

		tree->nodes[newIndex].data = input;
		tree->nodes[newIndex].Children = (ChildLink*)malloc(sizeof(ChildLink));
		if (tree->nodes[newIndex].Children == NULL) {
			printf("内存申请失败\n");
			FreeFromStaticTree(tree, newIndex);
			return CountOwned;
		}
		tree->nodes[newIndex].Children->index = -1;
		tree->nodes[newIndex].Children->Next = NULL;

		if (!childCount) {
			childCount = 1;
			tree->nodes[Monindex].Children->index = newIndex;
		}
		else {
			ChildLink* newlink = (ChildLink*)malloc(sizeof(ChildLink));
			if (newlink == NULL) {
				printf("发生了预期之外的情况。\n");
				return CountOwned;
			}
			newlink->index = newIndex;
			newlink->Next = NULL;
			link->Next = newlink;
			link = link->Next;
		}

		if (CountNeeded != CountOwned) {
			CountOwned = AddNodeToStaticTree(tree, newIndex, CountOwned, CountNeeded);
		}
	}
	return CountOwned;
}
