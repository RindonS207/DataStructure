#pragma once
#include<stdio.h>

#define DEFAULT_COUNT 30

#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif 

#define STATIC_STACK_INCLUDED 1

/*����*/
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

/* ��ӡһ������̬���� */
static void PrintStaticLinkTable(StaticLinkTable table[], int tableSize)
{
	int startIndex = table[tableSize - 1].NextIndex;
	if (!startIndex)
	{
		printf("��������Ԫ�ؿɴ�ӡ��\n");
		return;
	}
	/* ������ӡ */
	while (startIndex)
	{
		printf("%d\t",table[startIndex].data.value);
		startIndex = table[startIndex].NextIndex;
	}
	return;
}
/* ��ʼ��һ����̬���� */
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
/* ��̬���������ڴ棨��ȡ���пռ��һ�������� */
static int Malloc_address(StaticLinkTable table[])
{
	/* 1.���Ȼ�ȡ����λ������
	   2.�����ȡ����λ�ò�Ϊ0��Ҳ���ǻ��пɷ���ռ�
	   3.�ǾͰѻ�ȡ����λ�õ���һ��������ֵ��ͷ����nextindex���¿��������һ������
	   4.���ػ�ȡ���Ŀ���λ������������ɹ� */
	int address = table[0].NextIndex;
	if (address)
	{
		table[0].NextIndex = table[address].NextIndex;
	}
	return address;
}
/* ��̬����β��������� */
static BOOL AddElementToStaticLinkTable(StaticLinkTable table[], int tableSize,Element e)
{
	/* 1.�������¿ռ��ڴ棬��������ڴ�Ϊ0�����û���пռ䣬����ʧ��
	   2.��ȡ���ݲ��ֵ�һ������
	   3.����Ԫ�ز���������
	   4.��������ֱ��β������β������һ��Ԫ�ظ�ֵΪ������ */
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
/* ��ȡ��̬������Ԫ�صĸ��� */
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
/* ����Ԫ������̬���� */
static BOOL InsertElementToStaticLinkTable(StaticLinkTable table[], int tableSize, Element e, int index)
{
	int new_index,startIndex = table[tableSize -1].NextIndex,foreach_index = 0;
	/* ����λ�ò������������Ϊ�� */
	if (LengthOfStaticTable(table, tableSize) < index || table == NULL)
	{
		return false;
	}
	new_index = Malloc_address(table);
	if (!new_index)
	{
		return false;
	}
	/* ��Ϊforeachindex�����жϺ���+1�ģ��������indexҪ-1����ֹ����Ԥ��λ�� */
	while (foreach_index < index-1)
	{
		startIndex = table[startIndex].NextIndex;
		foreach_index += 1;
	}
	table[new_index].data = e;
	table[new_index].NextIndex = table[startIndex].NextIndex;
	table[startIndex].NextIndex = new_index;
	return true;
}
/* ����������ȡָ��λ���ϵ�ֵ */
static Element GetElementFromStaticLinkTable(StaticLinkTable table[], int tableSize, int index)
{
	int startIndex = table[tableSize - 1].NextIndex,foreach_index = 0;
	if (LengthOfStaticTable(table, tableSize) < index + 1 || table == NULL)
	{
		return (Element) { 0 };
	}
	while (foreach_index < index)
	{
		startIndex = table[startIndex].NextIndex;
		foreach_index += 1;
	}
	return table[startIndex].data;
}
/* ɾ��ָ��������Ԫ�� */
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
/* ����ָ��Ԫ���������� */
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