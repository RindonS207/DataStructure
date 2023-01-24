#include<stdio.h>
#include<stdlib.h>

#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif

#define S_TREE_INCLUDED 1
#define DEFAULT_SIZE 100
/* ��̬����� */
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
	ChildLink *childs;
	short int Parent;
}ST_NODE;

typedef struct ChildLink {
	int index;
	ChildLink* Next;
}ChildLink;

typedef struct StaticTree
{
	/* ����0���Ǹ��ڵ� */
	ST_NODE nodes[DEFAULT_SIZE];
	unsigned short int IdleSpaceIndex;
}StaticTree;

/* ������̬����� */
static StaticTree* CreateStaticTree() {
	char inputchar;
	int nodeCount=0,input,nowselectIndex=0,x,count,
		*firstChilds;
	ChildLink* link,*newlink;
	StaticTree* tree = (StaticTree*)malloc(sizeof(StaticTree));
	if (tree == NULL) {
		printf("\n�ڴ�����ʧ���ˣ�\n");
		return NULL;
	}
	printf("�����봴����̬������Ľڵ�������:\n");
	scanf("%d",&nodeCount);
	if (nodeCount < 1 || nodeCount > DEFAULT_SIZE) {
		free(tree);
		printf("������һ����Ч��ֵ��\n");
		return NULL;
	}
	tree->IdleSpaceIndex = 1;
	for (x = 0; x < DEFAULT_SIZE-1; x++) {
		tree->nodes[x].NextIndex = x + 1;
		tree->nodes[x].Parent = -1;
	}
	tree->nodes[DEFAULT_SIZE - 1].NextIndex = -1;
	/* �������ڵ� */
	printf("������˽ڵ��ֵ:\n");
	scanf("%d", &input);
	tree->nodes[nowselectIndex].data = input;
	tree->nodes[0].childs = (ChildLink*)malloc(sizeof(ChildLink));
	tree->nodes[0].childs->index = -1;
	tree->nodes[0].childs->Next = NULL;
	if (nodeCount == 1) {
		
		printf("1���ڵ����������ɡ�\n");
		return tree;
	}
	else {
		count =  CreateStaticTreeNode(tree, 0, 1, nodeCount);
	}
	if (count == nodeCount) {
		printf("��������ɡ�\n");
	}
	else {
		free(tree);
		printf("������Ԥ��֮������飬������ʧ�ܡ�\n");
	}
	return tree;
}
/* ��ӡ����� */
static void PrintStaticTree(StaticTree* tree)
{
	PrintStaticTreeNode(tree, 0, true);
}
/* ��ӡ�����ڵ����Ϣ recursion�����Ƿ��ӡ�ýڵ���ӽڵ� */
static void PrintStaticTreeNode(StaticTree* tree, int index, BOOL recursion) {
	ChildLink* link;
	int childCount = 1,*arr,x;
	printf("\n");
	if (tree == NULL || index < 0 || index >= DEFAULT_SIZE) {
		printf("��������Ч������ֵ��\n");
		return;
	}
	if (index == 0) {
		printf("�ڵ��±� 0 ֵΪ %d ������ڵ��Ǹ��ڵ㡣\n",tree->nodes[0].data);
	}
	if (tree->nodes[index].childs->index == -1) {
		printf("�ڵ��±� %d ֵΪ %d ������ڵ���Ҷ�ڵ㡣\n",index,tree->nodes[index].data);
		if (index == 0) {
			printf("����ڵ�û�и�ĸ��\n");
		}
		else {
			printf("����ڵ�ĸ�ĸ���±� %d ֵΪ %d\n", tree->nodes[index].Parent, tree->nodes[tree->nodes[index].Parent].data);
		}
	}
	else {
		link = tree->nodes[index].childs;
		while (link->Next != NULL) {
			childCount += 1;
			link = link->Next;
		}
		arr = (int*)calloc(childCount, sizeof(int));
		link = tree->nodes[index].childs;
		for (x = 0; x < childCount; x++) {
			
			arr[x] = link->index;
			link = link->Next;
		}
		printf("�ڵ��±� %d ֵΪ %d ������ڵ�ӵ�� %d �����ӡ�\n", index, tree->nodes[index].data, childCount);
		if (index == 0) {
			printf("����ڵ�û�и�ĸ��\n");
		}
		else {
			printf("����ڵ�ĸ�ĸ���±� %d ֵΪ %d\n", tree->nodes[index].Parent, tree->nodes[tree->nodes[index].Parent].data);
		}
		printf("���ĺ��ӷֱ��ǣ�\n");
		for (x = 0; x < childCount; x++) {
			printf("�±�:%d  ֵ:%d\n",arr[x],tree->nodes[arr[x]].data);
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
/* �ڶ���������롰�ڴ桱 */
static int MallocFromStaticTree(StaticTree* tree)
{
	int temp;
	if (tree == NULL || tree->IdleSpaceIndex == -1) {
		printf("�������ڻ��޿��пռ䡣\n");
		return -1;
	}
	temp = tree->IdleSpaceIndex;
	tree->IdleSpaceIndex = tree->nodes[temp].NextIndex;
	return temp;
}
/* �ͷ�ָ�������ġ��ڴ桱 */
static void FreeFromStaticTree(StaticTree* tree, int index)
{
	if (index < 1 || index > DEFAULT_SIZE) {
		printf("�봫����Чֵ��\n");
		return;
	}
	else {
		tree->nodes[index].NextIndex = tree->IdleSpaceIndex;
		tree->IdleSpaceIndex = index;
	}
}
/* ����ǰ����������ĸ������
  Ŀǰ��ӵ�нڵ���������ǰ����ڵ����� */
static int CreateStaticTreeNode(StaticTree* tree, int MonIndex,int CountOwned, int CountNeeded) 
{
	if (tree == NULL) {
		printf("��������Чֵ��\n");
		return CountOwned;
	}
	int value,x,newindex,input;
	ChildLink* link;
	printf("������ %d(ֵ) %d(�±�) ����Ҫ�ĺ��ӽڵ�����\n",tree->nodes[MonIndex].data,MonIndex);
	scanf("%d",&value);
	if (CountOwned + value > CountNeeded) {
		printf("��ֵ����Ԥ�ڣ�����ȡ����\n");
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
			printf("������ %d(����) �ĵ� %d �����ӵ�ֵ��\n",MonIndex,x+1);
			scanf("%d", &input);

			if (tree->nodes[MonIndex].childs->index == -1) {
				tree->nodes[MonIndex].childs->index = newindex;
			}
			else {
				link = tree->nodes[MonIndex].childs;
				while (link->Next != NULL) {
					link = link->Next;
				}
				ChildLink* newlink = (ChildLink*)malloc(sizeof(ChildLink));
				if (newlink == NULL) {
					printf("�����ڴ�ʧ�ܣ���������\n");
					free(tree);
					return CountOwned;
				}
				newlink->index = newindex;
				newlink->Next = NULL;
				link->Next = newlink;
			}

			tree->nodes[newindex].data = input;
			tree->nodes[newindex].Parent = MonIndex;

			tree->nodes[newindex].childs = (ChildLink*)malloc(sizeof(ChildLink));
			tree->nodes[newindex].childs->index = -1;
			tree->nodes[newindex].childs->Next = NULL;

			if (CountOwned < CountNeeded) {
				CountOwned = CreateStaticTreeNode(tree, newindex, CountOwned, CountNeeded);
			}
		}
	}
	return CountOwned;
}
/* ���ݸ�����Ԫ��ֵ����ʼλ�ã����ҵ�һ����������Ԫ����������(ǰ�����) */
static int GetIndexByValue(StaticTree* tree , int start, int value)
{
	ChildLink* link;
	int x,data;
	if (tree == NULL) {
		printf("�봫��һ����Ч��������\n");
		return -1;
	}
	if (tree->nodes[start].data == value) {
		return start;
	}
	else if (tree->nodes[start].childs->index == -1) {
		return -1;
	}
	while (true) {
		if (tree->nodes[start].data == value) {
			return start;
		}
		for ( link = tree->nodes[start].childs; link != NULL; link = link->Next) {
			x = link->index;

			data = GetIndexByValue(tree, x, value);

			if (data != -1) {
				return data;
			}
		}
		return -1;
	}
}
/* ɾ��ָ�������Ľڵ㣬�������Ƿ����ӽڵ�һ��ɾ�� */
static BOOL RemoveNodeFromStaticTree(StaticTree* tree, int index, BOOL recutsion)
{
	ChildLink* link,*loopPointer;
	int monIndex,brotherIndex=0,x,childCount=1,*childrenIndex;
	if (tree == NULL || index < 0 || index > DEFAULT_SIZE) {
		printf("����������������ݡ�\n");
		return false;
	}
	if (index == 0 && !recutsion) {
		printf("������ڵ�ʱ��ʹ�õݹ�ģʽ��\n");
		return false;
	}
	monIndex = tree->nodes[index].Parent;
	link = tree->nodes[monIndex].childs;
	while (link != NULL) {
		if (link->index == index) {
			if (!brotherIndex) {
				link->index = -1;
			}
			else {
				for (x = 0 , loopPointer = tree->nodes[monIndex].childs; x < brotherIndex; x++) {

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
	if (tree->nodes[index].childs->index != -1) {
		link = tree->nodes[index].childs;
		while (link->Next != NULL) {
			childCount += 1;
			link = link->Next;
		}
		childrenIndex = (int*)calloc(childCount, sizeof(int));
		for (x = 0 , link = tree->nodes[index].childs; x < childCount; x++) {
			childrenIndex[x] = link->index;
			link = link->Next;
		}
		if (!recutsion) {
			link = tree->nodes[monIndex].childs;
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
				if (tree->nodes[Cindex].childs->index != -1) {
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
/* ��ָ��������Ӻ��ӽڵ� */
static int AddNodeToStaticTree(StaticTree* tree, int Monindex, int CountOwned, int CountNeeded)
{
	ChildLink* link;
	int value,childCount,x,input,newIndex;
	if (tree == NULL || Monindex < 0 || Monindex > DEFAULT_SIZE) {
		return CountOwned;
	}
	link = tree->nodes[Monindex].childs;
	if (tree->nodes[Monindex].childs->index == -1) {
		childCount = 0;
		printf("������ %d(ֵ) %d(�±�) �ڵ�����Ҫ�ĺ���������\n", tree->nodes[Monindex].data, Monindex);
	}
	else {
		childCount = 1;
		
		while (link->Next != NULL) {
			link = link->Next;
			childCount += 1;
		}
		printf("������ %d(ֵ) %d(�±�) �ڵ�����Ҫ��ӵĺ���������\n", tree->nodes[Monindex].data, Monindex);
	}
	scanf("%d",&value);
	if (CountOwned + value > CountNeeded || value < 0) {
		printf("��������Ԥ�ڣ����ȡ����\n");
		return CountOwned;
	}
	if (value == 0) {
		return CountOwned;
	}
	CountOwned += value;
	for (x = 0; x < value; x++) {
		newIndex = MallocFromStaticTree(tree);
		printf("������ %d(����) �ĵ� %d �����ӵ�ֵ��\n", Monindex, x + 1);
		scanf("%d",&input);

		tree->nodes[newIndex].data = input;
		tree->nodes[newIndex].childs = (ChildLink*)malloc(sizeof(ChildLink));
		if (tree->nodes[newIndex].childs == NULL) {
			printf("�ڴ�����ʧ��\n");
			FreeFromStaticTree(tree, newIndex);
			return CountOwned;
		}
		tree->nodes[newIndex].childs->index = -1;
		tree->nodes[newIndex].childs->Next = NULL;

		if (!childCount) {
			childCount = 1;
			tree->nodes[Monindex].childs->index = newIndex;
		}
		else {
			ChildLink* newlink = (ChildLink*)malloc(sizeof(ChildLink));
			if (newlink == NULL) {
				printf("������Ԥ��֮��������\n");
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
