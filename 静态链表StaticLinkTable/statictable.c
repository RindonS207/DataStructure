#pragma once
#include<stdio.h>

#define DEFAULT_COUNT 30

#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif 

#define STATIC_STACK_INCLUDED 1

/*声明*/
typedef struct Element
{
	int value;
}Element;

typedef struct StaticLinkTable
{
	Element data;
	int NextIndex;
}StaticLinkTable;

static int Initlist(StaticLinkTable table[], int tableLength);
static int Malloc_address(StaticLinkTable table[]);
static BOOL AddElementToStaticLinkTable(StaticLinkTable table[], int tableSize, Element e);
static BOOL InsertElementToStaticLinkTable(StaticLinkTable table[], int tableSize, Element e, int index);
static Element GetElementFromStaticLinkTable(StaticLinkTable table[], int tableSize, int index);
static void PrintStaticLinkTable(StaticLinkTable table[],int tableSize);
static int LengthOfStaticTable(StaticLinkTable table[],int tableSize);
static BOOL RemoveElementFromStaticLinkTable(StaticLinkTable table[], int tableSize, int index);
static int FindIndexOfStaticTable(StaticLinkTable table[], int tableSize, Element e);

/* 打印一整个静态链表 */
static void PrintStaticLinkTable(StaticLinkTable table[], int tableSize)
{
	int startIndex = table[tableSize - 1].NextIndex;
	if (!startIndex)
	{
		printf("此链表无元素可打印。\n");
		return;
	}
	/* 遍历打印 */
	while (startIndex)
	{
		printf("%d\t",table[startIndex].data.value);
		startIndex = table[startIndex].NextIndex;
	}
	printf("\n");
	return;
}
/* 初始化一个静态链表 */
static BOOL Initlist(StaticLinkTable table[], int tableLength)
{
	int x;
	if (table == NULL || tableLength < 1)
	{
		return false;
	}
	for (x = 0; x < tableLength - 1; x++)
	{
		table[x].NextIndex = 1 + x;
	}
	table[tableLength - 1].NextIndex = 0;
	return true;
}
/* 向静态链表申请内存（获取空闲空间第一个索引） */
static int Malloc_address(StaticLinkTable table[])
{
	/* 1.首先获取空闲位置索引
	   2.如果获取空闲位置不为0，也就是还有可分配空间
	   3.那就把获取到的位置的下一个索引赋值给头部的nextindex更新空闲链表第一个索引
	   4.返回获取到的空闲位置索引，分配成功 */
	int address = table[0].NextIndex;
	if (address)
	{
		table[0].NextIndex = table[address].NextIndex;
	}
	return address;
}
/* 向静态链表尾部添加数据 */
static BOOL AddElementToStaticLinkTable(StaticLinkTable table[], int tableSize,Element e)
{
	/* 1.先申请新空间内存，如果申请内存为0则代表没空闲空间，申请失败
	   2.获取数据部分第一个索引
	   3.将新元素插入新索引
	   4.遍历链表，直到尾部，将尾部的下一个元素赋值为新索引 */
	int new_index,foreach_index;
	new_index = Malloc_address(table);
	foreach_index = table[tableSize - 1].NextIndex;
	if (new_index == 0)
	{
		return false;
	}
	table[new_index].NextIndex = 0;
	table[new_index].data = e;
	while (table[foreach_index].NextIndex)
	{
		foreach_index = table[foreach_index].NextIndex;
	}
	table[foreach_index].NextIndex = new_index;
	return true;
}
/* 获取静态链表中元素的个数 */
static int LengthOfStaticTable(StaticLinkTable table[],int tableSize)
{
	int length = 0,index;
	if (table == NULL)
	{
		return -1;
	}
	index = table[tableSize - 1].NextIndex;
	if (!index)
	{
		return index;
	}
	while (index)
	{
		length += 1;
		index = table[index].NextIndex;
	}
	return length;
}
/* 插入元素至静态链表 */
static BOOL InsertElementToStaticLinkTable(StaticLinkTable table[], int tableSize, Element e, int index)
{
	int new_index,startIndex = table[tableSize -1].NextIndex,foreach_index = 0;
	/* 插入位置不合理或是链表为空 */
	if (tableSize <= index || table == NULL)
	{
		return false;
	}
	/* 因为foreachindex是在判断后再+1的，所以这边index要-1，防止超过预期位置 */
	while (foreach_index < index-1)
	{
		startIndex = table[startIndex].NextIndex;
		if (startIndex == 0) {
			return false;
		}
		foreach_index += 1;
	}
	new_index = Malloc_address(table);
	if (!new_index)
	{
		return false;
	}
	table[new_index].data = e;
	table[new_index].NextIndex = table[startIndex].NextIndex;
	table[startIndex].NextIndex = new_index;
	return true;
}
/* 根据索引获取指定位置上的值 */
static Element GetElementFromStaticLinkTable(StaticLinkTable table[], int tableSize, int index)
{
	int startIndex = table[tableSize - 1].NextIndex,foreach_index = 0;
	if(tableSize  <= index || table == NULL)
	{
		return (Element) { 0 };
	}
	while (foreach_index < index)
	{
		startIndex = table[startIndex].NextIndex;
		if (!startIndex) {
			return (Element) { 0 };
		}
		foreach_index += 1;
	}
	return table[startIndex].data;
}
/* 删除指定索引的元素 */
static BOOL RemoveElementFromStaticLinkTable(StaticLinkTable table[], int tableSize, int index)
{
	int beforeIndex = tableSize - 1, startIndex = table[tableSize - 1].NextIndex, foreach_index = 0;
	if (table == NULL || index > tableSize-2 || startIndex == 0)
	{
		return false;
	}
	while (startIndex)
	{
		if (foreach_index == index)
		{
			table[startIndex].data = (Element) { 0 };
			table[beforeIndex].NextIndex = table[startIndex].NextIndex;
			table[startIndex].NextIndex = table[0].NextIndex;
			table[0].NextIndex = startIndex;

			return true;
		}
		startIndex = table[startIndex].NextIndex;
		beforeIndex = table[beforeIndex].NextIndex;
		foreach_index += 1;
	}
	return false;
}
/* 查找指定元素所在索引 */
static int FindIndexOfStaticTable(StaticLinkTable table[], int tableSize, Element e)
{
	int startIndex = table[tableSize - 1].NextIndex,foreach_index = 0;
	while (startIndex)
	{
		if (table[startIndex].data.value == e.value)
		{
			return foreach_index;
		}
		else { foreach_index += 1; startIndex = table[startIndex].NextIndex; }
	}
	return -1;
}
