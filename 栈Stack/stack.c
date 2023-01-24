#include<stdio.h>
#include<stdlib.h>

#ifndef BOOL_INCLUDED
#include "BOOL_DEF.c"
#endif 

#define DEFAULT_SIZE 10
#define STACK_INCLUDED 1

typedef struct Stack Stack;
typedef struct Element Element;
static Stack* CreateStack();
static BOOL StackPush(Stack* stack,Element value);
static BOOL StackPop(Stack* stack, Element* value);
static BOOL GetStackTop(Stack* stack, Element* value);

typedef struct Element
{
	int value;
}Element;

typedef struct Stack
{
	Element datas[DEFAULT_SIZE];
	int Top_Index;
}Stack;
/* ��ʼ��һ��ջ */
static Stack* CreateStack()
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->Top_Index = -1;
	return stack;
}
/* ���Ԫ����ջ�� */
static BOOL StackPush(Stack* stack, Element value)
{
	if ( stack->Top_Index == DEFAULT_SIZE - 1 || stack == NULL)
	{
	
		return false;
	}
	stack->Top_Index += 1;
	stack->datas[stack->Top_Index].value = value.value;
	return true;
}
/* ��ջ���ҷ��ر�ɾ����Ԫ�ص�ָ�룬���ز������Ϊ��������ֵ */
static BOOL StackPop(Stack* stack, Element* value)
{
	if (stack == NULL || stack->Top_Index == -1)
	{

		value = NULL;
		return false;
	}
	value->value = stack->datas[stack->Top_Index].value;
	stack->Top_Index -= 1;
	return true;
}
/* ��ȡջ��Ԫ�� */
static BOOL GetStackTop(Stack* stack, Element* value)
{
	if (stack->Top_Index == -1 || stack == NULL)
	{
		return false;
	}
	value->value = stack->datas[stack->Top_Index].value;
	return true;
}