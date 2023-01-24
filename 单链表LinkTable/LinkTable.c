#include<stdio.h>
#include<stdlib.h>
#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif

#ifndef INFINITE
#define INFININTE 32767
#endif

typedef struct LinkTable LinkTable;

static LinkTable* CreateLinkTable();
static LinkTable* CreateLinkTableWithDefault(int datas[],int dataLength);
void PrintLinkTable(LinkTable* table);
BOOL AppendElementToLinkTable(LinkTable* table,int value);
BOOL InsertElementToLinkTable(LinkTable* table, int index, int value);
BOOL RemoveElementFromLinkTable(LinkTable* table);
BOOL RemoveElementFromIndex(LinkTable* table, int index);
int FindElementFromLinkTable(LinkTable* table, int value);
BOOL SetLinkTableElement(LinkTable* table, int index, int value);

typedef struct LinkTable {
	int value;
	LinkTable* Next;
}LinkTable;
/* 创建一个没有任何初始值的链表 */
LinkTable* CreateLinkTable() {
	LinkTable* table = (LinkTable*)malloc(sizeof(LinkTable));
	if (table == NULL) {
		return NULL;
	}
	table->value = INFININTE;
	table->Next = NULL;
	return table;
}
/* 创建带有指定初始值的链表 */
LinkTable* CreateLinkTableWithDefault(int datas[], int dataLength) {
	LinkTable* table=NULL,*Pointer=NULL;
	int x;
	if (dataLength < 1) {
		return NULL;
	}
	table = (LinkTable*)malloc(sizeof(LinkTable));
	if (table == NULL) {
		return NULL;
	}
	Pointer = table;
	table->value = INFININTE;
	table->Next = NULL;
	for (x = 0; x < dataLength; x++) {
		LinkTable* Element = (LinkTable*)malloc(sizeof(LinkTable));
		Element->value = datas[x];
		Element->Next = NULL;
		Pointer->Next = Element;
		Pointer = Element;
	}
	return table;
}
/* 打印一个链表 */
void PrintLinkTable(LinkTable* table) {
	LinkTable* pointer;
	if (table == NULL) {
		return;
	}
	for (pointer = table->Next; pointer; pointer = pointer->Next) {
		printf("%d\t",pointer->value);
	}
	printf("\n");
}
/* 向链表尾部添加数据，返回一个操作状态 */
BOOL AppendElementToLinkTable(LinkTable* table, int value)
{
	LinkTable* Pointer = NULL;
	if (table == NULL || value == INFININTE) {
		return false;
	}
	for (Pointer = table; Pointer->Next; Pointer = Pointer->Next);
	LinkTable* Element = (LinkTable*)malloc(sizeof(LinkTable));
	if (Element == NULL) {
		return false;
	}
	Element->value = value;
	Element->Next = NULL;
	table->Next = Element;
	return true;
}
/* 向链表指定索引添加数据，返回一个操作状态 */
BOOL InsertElementToLinkTable(LinkTable* table, int index, int value) {
	int x;
	LinkTable* Previous=table, * Next=table->Next;
	if (table == NULL || index < 0) {
		return false;
	}
	for (x = 0; x < index && Previous; x++,Previous=Previous->Next,Next=Next->Next);
	if (x != index) {
		return false;
	}
	LinkTable* Element = (LinkTable*)malloc(sizeof(LinkTable));
	if (Element == NULL) {
		return false;
	}
	Element->value = value;
	Element->Next = Next;
	Previous->Next = Element;
	return true;
}
/* 删除链表的第一个元素（不是表头），并且返回一个操作状态 */
BOOL RemoveElementFromLinkTable(LinkTable* table) {
	LinkTable* Pointer;
	if (table == NULL || !table->Next) {
		return false;
	}
	Pointer = table->Next;
	table->Next = Pointer->Next;
	free(Pointer);
	return true;
}
/* 删除链表指定索引的元素，并且返回一个操作状态 */
BOOL RemoveElementFromIndex(LinkTable* table, int index) {
	LinkTable* Previous = table, *Current = table->Next;
	int x;
	if (table == NULL || index < 0) {
		return false;
	}
	for (x = 0; x < index && Previous; x++, Previous = Previous->Next, Current = Current->Next);
	if (x != index) {
		return false;
	}
	Previous->Next = Current->Next;
	free(Current);
	return true;
}
/* 查找链表中是否包含某个元素，未找到时返回-1，否则返回索引*/
int FindElementFromLinkTable(LinkTable* table, int value) {
	LinkTable* Pointer = table->Next;
	int x;
	if (table == NULL) {
		return -1;
	}
	for (x=0; Pointer; Pointer = Pointer->Next, x++) {
		if (Pointer->value == value) {
			return x;
		}
	}
	return -1;
}
/* 设置指定索引上的元素值，并返回一个操作状态 */
BOOL SetLinkTableElement(LinkTable* table, int index, int value) {
	LinkTable* Pointer = table->Next;
	int x;
	if (table == NULL || index < 0) {
		return false;
	}
	for (x = 0; Pointer; Pointer = Pointer->Next, x++) {
		if (x == index) {
			Pointer->value = value;
			return true;
		}
	}

	return false;
}
