#include<stdio.h>
#include<stdlib.h>
#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif 

#define DEFAULT_SIZE 10
#define D_STACK_INCLUDED 1

typedef struct DoubleStack DoubleStack;
typedef struct Element Element;
static DoubleStack* CreateDoubleStack();
static BOOL AddElementToDoubleStack(DoubleStack* stack,int stack_id,Element value);
static BOOL RemoveElementFromDoubleStack(DoubleStack* stack, int stack_id,Element *value);
static BOOL GetTopElementFromDoubleStack(DoubleStack* stack, int stack_id, Element* value);

typedef struct Element
{
	int value;
}Element;

typedef struct DoubleStack
{
	Element values[DEFAULT_SIZE];
	int top_Index_1;
	int top_Index_2;
}DoubleStack;
/* ��ʼ��һ������ջ */
static DoubleStack* CreateDoubleStack()
{
	DoubleStack* table = (DoubleStack*)malloc(sizeof(DoubleStack));
	table->top_Index_1 = -1;
	table->top_Index_2 = DEFAULT_SIZE;
	return table;
}
/* ����ջ�����Ԫ�� */
static BOOL AddElementToDoubleStack(DoubleStack* stack, int stack_id, Element value)
{
	if ((stack_id != 1 && stack_id != 2) || stack->top_Index_1 +1 == stack->top_Index_2)
	{
		return false;
	}
	if (stack_id == 1)
	{
		stack->top_Index_1 += 1;
		stack->values[stack->top_Index_1].value = value.value;
	}
	else
	{
		stack->top_Index_2 -= 1;
		stack->values[stack->top_Index_2].value = value.value;
	}
	return true;
}
/* ��ջ�����ر�ɾ����Ԫ����ָ�� */
static BOOL RemoveElementFromDoubleStack(DoubleStack* stack, int stack_id, Element* value)
{
	if (stack_id != 1 && stack_id != 2)
	{
		return false;
	}
	if (stack_id == 1 && stack->top_Index_1 == -1)
	{
		return false;
	}
	else
	{
		value->value = stack->values[stack->top_Index_1].value;
		stack->top_Index_1 -= 1;
	}
	if (stack_id == 2 && stack->top_Index_2 == DEFAULT_SIZE)
	{
		return false;
	}
	else
	{
		value->value = stack->values[stack->top_Index_2].value;
		stack->top_Index_2 += 1;
	}
	return true;
}
/* ��ȡ����Ԫ�أ�������ָ���ֵ */
static BOOL GetTopElementFromDoubleStack(DoubleStack* stack, int stack_id, Element* value)
{
	if (stack_id != 1 && stack_id != 2)
	{
		return false;
	}
	if (stack_id == 1)
	{
		if (stack->top_Index_1 == -1) {
			return false;
		}
		value->value = stack->values[stack->top_Index_1].value;
	}
	if (stack_id == 2)
	{
		if (stack->top_Index_2 == DEFAULT_SIZE)
		{
			return false;
		}
		value->value = stack->values[stack->top_Index_2].value;
	}

	return true;
}