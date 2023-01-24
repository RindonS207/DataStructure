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
/* ����һ��û���κγ�ʼֵ������ */
LinkTable* CreateLinkTable() {
	LinkTable* table = (LinkTable*)malloc(sizeof(LinkTable));
	if (table == NULL) {
		return NULL;
	}
	table->value = INFININTE;
	table->Next = NULL;
	return table;
}
/* ��������ָ����ʼֵ������ */
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
	table->value = NULL;
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
/* ��ӡһ������ */
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
/* ������β��������ݣ�����һ������״̬ */
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
/* ������ָ������������ݣ�����һ������״̬ */
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
/* ɾ������ĵ�һ��Ԫ�أ����Ǳ�ͷ�������ҷ���һ������״̬ */
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
/* ɾ������ָ��������Ԫ�أ����ҷ���һ������״̬ */
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
/* �����������Ƿ����ĳ��Ԫ�أ�δ�ҵ�ʱ����-1�����򷵻�����*/
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
/* ����ָ�������ϵ�Ԫ��ֵ��������һ������״̬ */
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