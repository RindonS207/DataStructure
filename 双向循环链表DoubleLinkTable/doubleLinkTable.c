#include<stdio.h>
#include<stdlib.h>
#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif 

#define D_L_STACK_INCLUDED 1

typedef struct Element Element;
typedef struct DoubleTable DoubleTable;
static DoubleTable* CreateDoubleTable();
static void PrintDoubleTable(DoubleTable* head);
static int LengthOfDoubleTable(DoubleTable* head);
static BOOL AddElementToDoubleTable(DoubleTable* head,Element value);
static BOOL InsertElementToDoubleTable(DoubleTable* head, int index, Element value);
static BOOL RemoveElementFromDoubleTable(DoubleTable* head, int index);

typedef struct Element
{
	int value;
}Element;

typedef struct DoubleTable
{
	Element data;
	DoubleTable* PriorElement;
	DoubleTable* NextElement;
}DoubleTable;
/* 初始化一个双向链表 */
static DoubleTable* CreateDoubleTable()
{
	DoubleTable* table = malloc(sizeof(DoubleTable));
	if (table == NULL)
	{
		return NULL;
	}
	table->NextElement = table;
	table->PriorElement = table;
	return table;
}
/* 打印整个链表 */
static void PrintDoubleTable(DoubleTable* head)
{
	DoubleTable* pointer = head->NextElement;
	while (pointer != head)
	{
		printf("%d\t",pointer->data.value);
		pointer = pointer->NextElement;
	}
}
/* 获取双向链表的长度 */
static int LengthOfDoubleTable(DoubleTable* head)
{
	int count = 0; DoubleTable* pointer = head;
	if (head == NULL || pointer == head->NextElement)
	{
		return count;
	}
	while (pointer->NextElement != head)
	{
		count += 1;
		pointer = pointer->NextElement;
	}
	return count;
}
/* 向双向链表中添加元素，添加至尾部 */
static BOOL AddElementToDoubleTable(DoubleTable* head, Element value)
{
	DoubleTable* pointer = head;
	if (head == NULL || value.value == NULL)
	{
		return false;
	}
	while (pointer->NextElement != head)
	{
		pointer = pointer->NextElement;
	}
	DoubleTable* new_element = (DoubleTable*)malloc(sizeof(DoubleTable));
	if (new_element == NULL)
	{
		return false;
	}
	new_element->data.value = value.value;
	new_element->PriorElement = pointer;
	new_element->NextElement = head;
	pointer->NextElement = new_element;
	return true;
}
/* 向双向链表中指定索引插入元素 */
static BOOL InsertElementToDoubleTable(DoubleTable* head, int index, Element value)
{
	DoubleTable* loopPointer = head; int foreach_index = 0,length = LengthOfDoubleTable(head);
	if (head == NULL || value.value == NULL || index > length -1 || index < 0)
	{
		return false;
	}
	while (loopPointer->NextElement != head)
	{
		if (foreach_index == index)
		{
			DoubleTable* new_element = (DoubleTable*)malloc(sizeof(DoubleTable));
			if (new_element == NULL)
			{
				return false;
			}
			new_element->NextElement = loopPointer->NextElement;
			new_element->PriorElement = loopPointer;
			new_element->data.value = value.value;
			loopPointer->NextElement->PriorElement = new_element;
			loopPointer->NextElement = new_element;
			break;
		}
		else
		{
			foreach_index += 1;
			loopPointer = loopPointer->PriorElement;
		}
	}
	return true;
}
/* 删除双向链表中指定索引元素 */
static BOOL RemoveElementFromDoubleTable(DoubleTable* head, int index)
{
	DoubleTable* loopPointer = head; int foreach_index = 0, length = LengthOfDoubleTable(head);
	if (head == NULL || index < 0 || index > length-1)
	{
		return false;
	}
	while (loopPointer->NextElement != head)
	{
		if (foreach_index == index)
		{
			DoubleTable* delete_element = loopPointer->NextElement;
			loopPointer->NextElement->NextElement->PriorElement = loopPointer;
			loopPointer->NextElement = loopPointer->NextElement->NextElement;
			free(delete_element);
			break;
		}
		else
		{
			foreach_index += 1;
			loopPointer = loopPointer->NextElement;
		}
	}
	return true;
}